/*
 * Copyright (C) 2007-2016 Siemens AG
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction, 
 * including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do
 * so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all copies or 
 * substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR 
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION 
 * WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
/*#include <string.h>*/

#include "EXITypes.h"
#include "EXIforJSONQNameDefines.h"
#include "StringNameTable.h"
#include "EXIforJSONEXIDecoder.h"
#include "ErrorCodes.h"
#include "ByteStream.h"

#include "DynamicMemory.h"
#include "StringValueTable.h"

/** EXI Debug mode */
#define EXI_DEBUG 1

#define BUFFER_SIZE 8192
uint8_t bufferIn[BUFFER_SIZE];

/* String table memory setup */
uint16_t numberOfLocalStringsDecode[EXI_EXIforJSONMAX_NUMBER_OF_QNAMES];
uint16_t numberOfLocalStringsEncode[EXI_EXIforJSONMAX_NUMBER_OF_QNAMES];

exi_value_t val;

#if EXI_DEBUG == 1
# define DEBUG_PRINTF(x) printf x
#else
# define DEBUG_PRINTF(x) do {} while (0)
#endif


static void debugValue(exi_value_t* val, exi_value_table_t* valueTable, uint16_t qnameID);

int main_exiforjson_decode(int argc, char *argv[]) {
	int errn = 0;
	int noEndOfDocument;

	uint16_t posDecode;
	bitstream_t iStream;

	exi_state_t stateDecode;
	exi_event_t event;

	uint16_t qnameID = 0; /* qname */

	exi_name_table_runtime_t runtimeTableDecode;
	exi_value_table_t stringTableDecode = { 0, EXI_EXIforJSONMAX_NUMBER_OF_QNAMES, numberOfLocalStringsDecode, NULL };

	/** string values */
	exi_value_string_table_t stringTableValuesDecode;
	stringTableValuesDecode.size = 0;
	stringTableValuesDecode.len = 0;
	stringTableDecode.valueStringTable = &stringTableValuesDecode;

	if (argc < 3) {
		printf("Usage: %s exiforJsonInput \n", argv[0]);
		return -1;
	}

	/* BINARY memory setup */
	val.binary.len = 0;
	val.binary.size = 0;
	val.binary.data = NULL;

	/* STRING miss memory setup */
	val.str.type = EXI_STRING_VALUE_MISS;
	val.str.miss.len = 0;
	val.str.miss.size = 0;
	val.str.miss.characters = NULL;


	/* input pos */
	posDecode = 0;
	/* parse EXI stream to internal byte structures  */
	errn = readBytesFromFile(argv[1], bufferIn, BUFFER_SIZE, &posDecode);
	if (errn != 0) {
		printf("Problems while reading file into buffer\n");
		return errn;
	}
#if EXI_DEBUG == 1
	printf("Read %d bytes\n", posDecode);
#endif /*EXI_DEBUG*/
	posDecode = 0; /* reset position */

	/* setup input stream */
	iStream.size = BUFFER_SIZE;
	iStream.data = bufferIn;
	iStream.pos = &posDecode;
	iStream.file = fopen(argv[1], "rb");

	noEndOfDocument = 1; /* true */

	/* init decoder (read header, set initial state) */
	/* init runtime table */
	errn = exiInitNameTableRuntime(&runtimeTableDecode);
	if (errn==0) {
		errn = exiEXIforJSONInitDecoder(&iStream, &stateDecode, runtimeTableDecode, stringTableDecode);
	}
	if (errn) {
		DEBUG_PRINTF(("[Init-Decode-ERROR] %d \n", errn));
		return errn;
	}


	DEBUG_PRINTF(("[DECODE] >>> EXI  >>> [ENCODE] \n"));

	do {
		errn = exiEXIforJSONDecodeNextEvent(&iStream, &stateDecode,
				&event);
		if (errn) {
			DEBUG_PRINTF(("[Decode-ERROR] %d \n", errn));
			return errn;
		}

		switch (event) {
		case EXI_EVENT_START_DOCUMENT:
			errn = exiEXIforJSONDecodeStartDocument(&iStream,
					&stateDecode);
			if (errn) {
				DEBUG_PRINTF(("[Decode-ERROR-SD] %d \n", errn));
				return errn;
			}
			DEBUG_PRINTF((">> START_DOCUMENT \n"));
			break;
		case EXI_EVENT_END_DOCUMENT:
			errn = exiEXIforJSONDecodeEndDocument(&iStream,
					&stateDecode);
			if (errn) {
				DEBUG_PRINTF(("[Decode-ERROR-ED] %d \n", errn));
				return errn;
			}
			DEBUG_PRINTF((">> END_DOCUMENT \n"));
			/* signalize end of document */
			noEndOfDocument = 0; /* false */
			break;
		case EXI_EVENT_START_ELEMENT:
		case EXI_EVENT_START_ELEMENT_GENERIC:
		case EXI_EVENT_START_ELEMENT_GENERIC_UNDECLARED:
			errn = exiEXIforJSONDecodeStartElement(&iStream,
					&stateDecode, &qnameID);
			if (errn) {
				DEBUG_PRINTF(("[Decode-ERROR-SE] %d \n", errn));
				return errn;
			}
			DEBUG_PRINTF((">> SE (%d) \n", qnameID));
			break;
		case EXI_EVENT_END_ELEMENT:
		case EXI_EVENT_END_ELEMENT_UNDECLARED:
			errn = exiEXIforJSONDecodeEndElement(&iStream,
					&stateDecode, &qnameID);
			if (errn) {
				DEBUG_PRINTF(("[Decode-ERROR-EE] %d \n", errn));
				return errn;
			}
			DEBUG_PRINTF(("<< EE \n"));
			break;
		case EXI_EVENT_CHARACTERS:
		case EXI_EVENT_CHARACTERS_GENERIC:
		case EXI_EVENT_CHARACTERS_GENERIC_UNDECLARED:
			errn = exiEXIforJSONDecodeCharacters(&iStream,
					&stateDecode, &val);
			if (errn) {
				DEBUG_PRINTF(("[Decode-ERROR-CH] %d \n", errn));
				return errn;
			}
			DEBUG_PRINTF((" CH: "));
			debugValue(&val, &stringTableDecode, stateDecode.elementStack[stateDecode.stackIndex]);
			break;
		case EXI_EVENT_ATTRIBUTE:
		case EXI_EVENT_ATTRIBUTE_GENERIC:
		case EXI_EVENT_ATTRIBUTE_GENERIC_UNDECLARED:
		case EXI_EVENT_ATTRIBUTE_INVALID_VALUE:
			errn = exiEXIforJSONDecodeAttribute(&iStream, &stateDecode,
					&qnameID, &val);
			if (errn) {
				DEBUG_PRINTF(("[Decode-ERROR-AT] %d \n", errn));
				return errn;
			}
			DEBUG_PRINTF((" AT (%d): ", qnameID));
			debugValue(&val, &stringTableDecode, qnameID);
			break;
		case EXI_EVENT_ATTRIBUTE_XSI_NIL:
			errn = exiEXIforJSONDecodeAttributeXsiNil(&iStream,
					&stateDecode, &val);
			if (errn) {
				DEBUG_PRINTF(("[Decode-ERROR-AT-NIL] %d \n", errn));
				return errn;
			}
			DEBUG_PRINTF((" AT {xsi}nil == %i \n", val.boolean));
			break;
		case EXI_EVENT_ATTRIBUTE_XSI_TYPE:
			errn = exiEXIforJSONDecodeAttributeXsiType(&iStream,
					&stateDecode, &val);
			if (errn) {
				DEBUG_PRINTF(("[Decode-ERROR-AT-TYPE] %d \n", errn));
				return errn;
			}
			DEBUG_PRINTF((" AT {type}type == {%d}%d \n", val.eqname.namespaceURI, val.eqname.localPart));
			break;
		default:
			/* ERROR */
			DEBUG_PRINTF(("[Unknown-Event] %d \n", event));
			return EXI_ERROR_UNKOWN_EVENT;
		}

	} while (noEndOfDocument);


	/* free memory if any */
	exiFreeDynamicStringMemory(&val.str.miss);
	exiFreeDynamicBinaryMemory(&val.binary);


	return errn;
}




static void debugValueInteger(exi_integer_t* integer) {
	switch (integer->type) {
	/* Unsigned Integer */
	case EXI_UNSIGNED_INTEGER_8:
		printf("uint8 : %d \n", integer->val.uint8);
		break;
	case EXI_UNSIGNED_INTEGER_16:
		printf("uint16 : %d \n", integer->val.uint16);
		break;
	case EXI_UNSIGNED_INTEGER_32:
		printf("uint32 : %d \n", integer->val.uint32);
		break;
	case EXI_UNSIGNED_INTEGER_64:
		printf("uint64 : %ld \n",
				(long unsigned int) integer->val.uint64);
		break;
		/* (Signed) Integer */
	case EXI_INTEGER_8:
		printf("int8 : %d \n", integer->val.int8);
		break;
	case EXI_INTEGER_16:
		printf("int16 : %d \n", integer->val.int16);
		break;
	case EXI_INTEGER_32:
		printf("int32 : %d \n", integer->val.int32);
		break;
	case EXI_INTEGER_64:
		printf("int64 : %ld \n", (long int) integer->val.int64);
		break;
	}
}

static void debugValue(exi_value_t* val, exi_value_table_t* valueTable, uint16_t qnameID) {
	exi_string_t sv;

#if EXI_DEBUG == 1
	int i;
	switch (val->type) {
	case EXI_DATATYPE_NBIT_UNSIGNED_INTEGER:
	case EXI_DATATYPE_UNSIGNED_INTEGER:
	case EXI_DATATYPE_INTEGER:
		debugValueInteger(&(val->integer));
		break;
	case EXI_DATATYPE_BINARY_BASE64:
	case EXI_DATATYPE_BINARY_HEX:
		printf("Binary (len == %d) : ", val->binary.len);
		for (i = 0; i < val->binary.len; i++) {
			printf(" [%d]", val->binary.data[i]);
		}
		printf("\n");
		break;
	case EXI_DATATYPE_BOOLEAN:
		printf("Boolean : %d \n", val->boolean);
		break;
	case EXI_DATATYPE_DECIMAL:
		/* Note: reversed fractional part */
		printf("Decimal : negative: %d followed by integral and reversed fractional part \n", val->decimal.negative);
		debugValueInteger(&(val->decimal.integral));
		debugValueInteger(&(val->decimal.reverseFraction));
		break;
	case EXI_DATATYPE_FLOAT:
		if(val->float_me.exponent == FLOAT_EXPONENT_SPECIAL_VALUES) {
			if (val->float_me.mantissa == FLOAT_MANTISSA_INFINITY) {
				printf("Float Special: INF \n");
			} else if (val->float_me.mantissa == FLOAT_MANTISSA_MINUS_INFINITY) {
				printf("Float Special: -INF \n");
			} else {
				printf("Float Special: NaN \n");
			}
		} else {
			printf("Float : %ld E %d \n", (long int) val->float_me.mantissa, val->float_me.exponent);
		}
		break;
	case EXI_DATATYPE_STRING:
	case EXI_DATATYPE_RCS_STRING:
		switch(val->str.type) {
		case EXI_STRING_VALUE_MISS:
			printf("String Miss (len==%d) : '", val->str.miss.len);
			for (i = 0; i < val->str.miss.len; i++) {
				printf("%c", (char) val->str.miss.characters[i]);
			}
			printf("'\n");
			break;
		case EXI_STRING_VALUE_LOCAL_HIT:
			printf("String LocalHit: %d", val->str.localID);
			if( exiGetLocalStringValue(valueTable, qnameID, (uint16_t)(val->str.localID), &sv)) {
				printf("ERROR when retrieving localvalue hit \n");
			} else {
				printf(" --> '");
				for (i = 0; i < sv.len; i++) {
					printf("%c", (char) sv.characters[i]);
				}
				printf("'");
			}
			printf("\n");
			break;
		case EXI_STRING_VALUE_GLOBAL_HIT:
			printf("String GlobalHit: %d ", val->str.globalID);
			if( exiGetGlobalStringValue(valueTable, (uint16_t)(val->str.globalID), &sv)) {
				printf("ERROR when retrieving global value hit \n");
			} else {
				printf(" --> '");
				for (i = 0; i < sv.len; i++) {
					printf("%c", (char) sv.characters[i]);
				}
				printf("'");
			}
			printf("\n");
			break;
		}
		break;
	case EXI_DATATYPE_DATETIME:
		switch(val->datetime.type) {
		case EXI_DATETIME_GYEAR:
			printf("Datetime gYear: %d", val->datetime.year);
			break;
		case EXI_DATETIME_GYEARMONTH:
			printf("Datetime gYearMonth: Year=%d, MonthDay=%d", val->datetime.year, val->datetime.monthDay);
			break;
		case EXI_DATETIME_DATE:
			printf("Datetime date: Year=%d, MonthDay=%d", val->datetime.year, val->datetime.monthDay);
			break;
		case EXI_DATETIME_DATETIME:
			printf("Datetime dateTime: Year=%d, MonthDay=%d, Time=%d", val->datetime.year, val->datetime.monthDay, val->datetime.time);
			break;
		case EXI_DATETIME_GMONTH:
			printf("Datetime gMonth: MonthDay=%d", val->datetime.monthDay);
			break;
		case EXI_DATETIME_GMONTHDAY:
			printf("Datetime gMonthDay: MonthDay=%d", val->datetime.monthDay);
			break;
		case EXI_DATETIME_GDAY:
			printf("Datetime gDay: MonthDay=%d", val->datetime.monthDay);
			break;
		case EXI_DATETIME_TIME:
			printf("Datetime time: Time=%d", val->datetime.time);
			break;
		default:
			printf("Datetime ?Type?");
			break;
		}
		if(val->datetime.presenceFractionalSecs) {
			printf(", FractionalSecs=%d", val->datetime.fractionalSecs);
		}
		if(val->datetime.presenceTimezone) {
			printf(", TimeZone=%d", val->datetime.timezone);
		}
		printf("\n");
		break;
	case EXI_DATATYPE_ENUMERATION:
		printf("Enumeration (id==%d) \n", val->enumeration);
		break;
	case EXI_DATATYPE_LIST:
		printf("List (len==%d) \n", val->list.len);
		break;
	case EXI_DATATYPE_QNAME:
		printf("QName (uri==%d, localName=%d) \n", val->eqname.namespaceURI, val->eqname.localPart);
		break;
	default:
		printf(" ?Value-Type? \n");
		break;
	}
#endif /*EXI_DEBUG*/
}
