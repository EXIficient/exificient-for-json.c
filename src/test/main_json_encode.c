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
#include <string.h>

#include "jsmn.h"

#include "EXITypes.h"
#include "EXIforJSONQNameDefines.h"
#include "StringNameTable.h"
#include "EXIforJSONEXIEncoder.h"

/** EXI Debug mode */
#define EXI_DEBUG 1


#define BUFFER_SIZE 8192
uint8_t bufferOut[BUFFER_SIZE];
/* String table memory setup */
uint16_t numberOfLocalStringsDecode[EXI_EXIforJSONMAX_NUMBER_OF_QNAMES];
uint16_t numberOfLocalStringsEncode[EXI_EXIforJSONMAX_NUMBER_OF_QNAMES];

exi_value_t val;

/* const char *JSON_STRING = "{\"keyNumber\":   123, \"k\":-12.34, \"keyArrayStrings\": [ \"s1\", \"s2\" ] , \"valid\": true, \"foo\": null}"; */
char *JSON_STRING = "{\"keyNumber\":   123, \"keyArrayStrings\": [ \"s1\", \"s2\" ] }"; /* test01.json */

typedef enum {MAP, ARRAY, STRING, NUMBER, TRUE, FALSE, NUL} json_values_t;

static int dumpFloat(const char *js, int start, int end, bitstream_t* stream, exi_state_t* state) {
	int errn;
	/* minus */
	/* dot */
	/* E/e */
	int pos = start;
	int negative = 0;
	int mantissa = 0;
	int exponent = 0;
	int afterDot = 0;

	while(pos < end) {
		if(js[pos] == '-') {
			negative = 1;
		} else if(js[pos] == '+') {
			/* */
		} else if(js[pos] == '.') {
			afterDot = 1;
		} else if ((js[pos] >= '0') && (js[pos] <= '9')) {
			mantissa = (mantissa * 10) + ((js[pos]) - '0');
			if(afterDot) {
				exponent -= 1;
			}
		}
		pos++;
	}

	if(negative) {
		mantissa = mantissa * -1;
	}

	/* print number */
	printf("float M:%d, E:%d ", mantissa, exponent);


	val.type = EXI_DATATYPE_FLOAT;
	val.float_me.mantissa = mantissa;
	val.float_me.exponent = exponent;
	errn = exiEXIforJSONEncodeCharacters(stream, state, &val);

	return errn;
}

static int pendingKeyStart;
static int pendingKeyEnd;

static int dumpKey(const char *js, jsmntok_t *t, size_t count, bitstream_t* stream, exi_state_t* state) {
	if (t->type == JSMN_STRING) {
		printf("#%.*s#", t->end - t->start, js+t->start);
		pendingKeyStart = t->start;
		pendingKeyEnd = t->end;
	} else {
		/* error */
		printf("Error: no key \n");
	}

	return 1;
}

static int checkPendingKey(char *js, json_values_t type, bitstream_t* stream, exi_state_t* state) {
	int errn = 0;

	if(type == MAP) {
		errn = exiEXIforJSONEncodeStartElement(stream, state, EXI_EXIforJSON_4_map);
	} else if(type == ARRAY) {
		errn = exiEXIforJSONEncodeStartElement(stream, state, EXI_EXIforJSON_4_array);
	} else if(type == STRING) {
		errn = exiEXIforJSONEncodeStartElement(stream, state, EXI_EXIforJSON_4_string);
	} else if(type == NUMBER) {
		errn = exiEXIforJSONEncodeStartElement(stream, state, EXI_EXIforJSON_4_number);
	} else if(type == TRUE) {
		errn = exiEXIforJSONEncodeStartElement(stream, state, EXI_EXIforJSON_4_boolean);
	} else if(type == FALSE) {
		errn = exiEXIforJSONEncodeStartElement(stream, state, EXI_EXIforJSON_4_boolean);
	} else if(type == NUL) {
		errn = exiEXIforJSONEncodeStartElement(stream, state, EXI_EXIforJSON_4_null);
	} else {
		errn = -1;
	}


	if( pendingKeyStart > 0) {
		/* TODO string table hit */
		val.type = EXI_DATATYPE_STRING;
		val.str.type = EXI_STRING_VALUE_MISS;
		val.str.miss.len = pendingKeyEnd - pendingKeyStart;
		val.str.miss.size = val.str.miss.len;
		val.str.miss.characters = &js[pendingKeyStart];

		errn = exiEXIforJSONEncodeAttribute(stream, state, EXI_EXIforJSON_0_key, &val);

		pendingKeyStart = 0; /* signals no pending key */
	}
	return errn;
}

/*
 * An example of reading JSON and printing its content
 */

static int dump(char *js, jsmntok_t *t, size_t count, bitstream_t* stream, exi_state_t* state) {
	int i, j;
	int errn = 0;
	if (count == 0) {
		return errn;
	}
	if (t->type == JSMN_PRIMITIVE) {
		/* number, true, false, or null */
		if(js[t->start] == 't') {
			checkPendingKey(js, TRUE, stream, state);
			printf("booleanTrue \n");
			val.type = EXI_DATATYPE_BOOLEAN;
			val.boolean = 1;
			errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
			errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(boolean) */
		} else if(js[t->start] == 'f') {
			checkPendingKey(js, FALSE, stream, state);
			printf("booleanFalse \n");
			val.type = EXI_DATATYPE_BOOLEAN;
			val.boolean = 0;
			errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
			errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(boolean) */
		} else if(js[t->start] == 'n') {
			checkPendingKey(js, NUL, stream, state);
			printf("NULL \n");
			errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(null) */
		} else {
			checkPendingKey(js, NUMBER, stream, state);
			/* printf("NUMBER %d %d \n", t->start, t->end); */
			/* printf("%.*s", t->end - t->start, js+t->start); */
			dumpFloat(js, t->start, t->end, stream, state);
			errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(number) */
		}

		/* printf("%.*s", t->end - t->start, js+t->start); */
		return 1;
	} else if (t->type == JSMN_STRING) {
		checkPendingKey(js, STRING, stream, state);
		printf("'%.*s'", t->end - t->start, js+t->start);
		/* TODO string table hit */
		val.type = EXI_DATATYPE_STRING;
		val.str.type = EXI_STRING_VALUE_MISS;
		val.str.miss.len = t->end - t->start;
		val.str.miss.size = val.str.miss.len;
		val.str.miss.characters = &js[t->start];
		errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
		errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(string) */
		return 1;
	} else if (t->type == JSMN_OBJECT) {
		checkPendingKey(js, MAP, stream, state);
		printf("{\n");


		if (errn == 0) {
			j = 0;
			for (i = 0; i < t->size; i++) {
				j += dumpKey(js, t+1+j, count-j, stream, state);
				printf(": ");
				j += dump(js, t+1+j, count-j, stream, state);
				printf("\n");
			}

			printf("}\n");
			errn = exiEXIforJSONEncodeEndElement(stream, state);  /* EE(map) */
			if(errn != 0) {
				printf("EXI Error: end object\n");
			}
		} else {
			printf("EXI Error: start object\n");
		}
		return j+1;
	} else if (t->type == JSMN_ARRAY) {
		checkPendingKey(js, ARRAY, stream, state);
		j = 0;
		printf("[\n");
		for (i = 0; i < t->size; i++) {
			printf("   - ");
			j += dump(js, t+1+j, count-j, stream, state);
			printf("\n");
		}
		printf("]\n");
		errn = exiEXIforJSONEncodeEndElement(stream, state);  /* EE(array) */

		return j+1;
	}
	return 0;
}

int main_json_encode() {
	int r;
	int errn = 0;
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 tokens */

	pendingKeyStart = 0;

	/* EXI encoder setup*/
	bitstream_t oStream;
	uint8_t bufferOut[BUFFER_SIZE];
	exi_name_table_runtime_t runtimeTableEncode;
	exi_state_t stateEncode;
	exi_value_table_t stringTableEncode = { 0, EXI_EXIforJSONMAX_NUMBER_OF_QNAMES, numberOfLocalStringsEncode, NULL };
	/** string values */
	exi_value_string_table_t stringTableValuesEncode;
	stringTableValuesEncode.size = 0;
	stringTableValuesEncode.len = 0;
	stringTableEncode.valueStringTable = &stringTableValuesEncode;

	/* setup output stream */
	uint16_t posEncode = 0;
	oStream.size = BUFFER_SIZE;
	oStream.data = bufferOut;
	oStream.pos = &posEncode;
	oStream.file = fopen("jsonTest.exi4json", "wb");
	/* init encoder (write header, set initial state) */
	errn = exiInitNameTableRuntime(&runtimeTableEncode);
	if (errn==0) {
		errn = exiEXIforJSONInitEncoder(&oStream, &stateEncode, runtimeTableEncode, stringTableEncode);
	}

	jsmn_init(&p);
	r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t, sizeof(t)/sizeof(t[0]));
	if (r < 0) {
		printf("Failed to parse JSON: %d\n", r);
		errn = 1;
	} else {
		errn = exiEXIforJSONEncodeStartDocument(&oStream, &stateEncode);
		if(errn == 0) {
			dump(JSON_STRING, t, p.toknext, &oStream, &stateEncode);
			errn = exiEXIforJSONEncodeEndDocument(&oStream, &stateEncode);
		}

		if (errn) {
			printf("[Encode-ERROR] %d \n", errn);
		}
	}

	return errn;
}

