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

#include "EXIforJSONEncoder.h"

#include "jsmn.h"
#include "EXITypes.h"
#include "EXIforJSONQNameDefines.h"
#include "StringNameTable.h"
#include "EXIforJSONEXIEncoder.h"

#include "StringValueTable.h"
#include "DynamicMemory.h"

#ifndef EXI_FOR_JSON_ENCODER_C
#define EXI_FOR_JSON_ENCODER_C

/** EXI Debug mode */
#define EXI_ENCODE_DEBUG 0

#if EXI_ENCODE_DEBUG == 1
# define DEBUG_PRINTF(x) printf x
#else
# define DEBUG_PRINTF(x) do {} while (0)
#endif

static uint16_t numberOfLocalStringsEncode[EXI_EXIforJSONMAX_NUMBER_OF_QNAMES];

static exi_value_t val;

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
	DEBUG_PRINTF(("float M:%d, E:%d ", mantissa, exponent));


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
		DEBUG_PRINTF(("#%.*s#", t->end - t->start, js+t->start));
		pendingKeyStart = t->start;
		pendingKeyEnd = t->end;
	} else {
		/* error */
		DEBUG_PRINTF(("Error: no key \n"));
	}

	return 1;
}


static int updateStringValue(const char *s, uint16_t start, uint16_t end, exi_value_table_t* valueTable, uint16_t qnameID) {
	int errn = 0;
	uint16_t slen = end - start;
	int i, k;
	exi_value_string_table_entry_t* strHit = NULL;
	uint32_t globalID;

	if (valueTable->numberOfGlobalStrings > 0) {
		for(i=0;i<valueTable->valueStringTable->len && strHit == NULL; i++) {
			if(valueTable->valueStringTable->strs[i].str.len == slen) {
				/* compare characters first by length */
				int match = 1;
				for(k=0; k<slen && match; k++) {
					if(valueTable->valueStringTable->strs[i].str.characters[k] != s[start+k]) {
						/* mis-match */
						match = 0;
					}
				}
				if(match) {
					strHit = &valueTable->valueStringTable->strs[i];
					globalID = i;
				}
			}
		}
	}

	val.type = EXI_DATATYPE_STRING;
	if(strHit == NULL) {
		/* Miss */
		val.str.type = EXI_STRING_VALUE_MISS;
		val.str.miss.len = slen;
		val.str.miss.size = val.str.miss.len;
		val.str.miss.characters = (exi_string_character_t*)&s[start];
	} else {
		/* Hit */
		if(qnameID == strHit->qnameID) {
			/* local hit */
			val.str.type = EXI_STRING_VALUE_LOCAL_HIT;
			val.str.localID = strHit->localValueID;
		} else {
			/* global hit */
			val.str.type = EXI_STRING_VALUE_GLOBAL_HIT;
			val.str.globalID = globalID;
		}
		val.str.miss.len = slen;
		val.str.miss.size = val.str.miss.len;
		val.str.miss.characters = (exi_string_character_t*)&s[start];
	}




	return errn;
}


static int checkPendingKey(const char *js, json_values_t type, bitstream_t* stream, exi_state_t* state) {
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
		errn = updateStringValue(js, pendingKeyStart, pendingKeyEnd, &state->stringTable, EXI_EXIforJSON_0_key);
		errn = exiEXIforJSONEncodeAttribute(stream, state, EXI_EXIforJSON_0_key, &val);

		pendingKeyStart = 0; /* signals no pending key */
	}
	return errn;
}

/*
 * An example of reading JSON and printing its content
 */

static int dump(const char *js, jsmntok_t *t, size_t count, bitstream_t* stream, exi_state_t* state) {
	int i, j;
	int errn = 0;
	if (count == 0) {
		return errn;
	}
	if (t->type == JSMN_PRIMITIVE) {
		/* number, true, false, or null */
		if(js[t->start] == 't') {
			checkPendingKey(js, TRUE, stream, state);
			DEBUG_PRINTF(("booleanTrue \n"));
			val.type = EXI_DATATYPE_BOOLEAN;
			val.boolean = 1;
			errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
			errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(boolean) */
		} else if(js[t->start] == 'f') {
			checkPendingKey(js, FALSE, stream, state);
			DEBUG_PRINTF(("booleanFalse \n"));
			val.type = EXI_DATATYPE_BOOLEAN;
			val.boolean = 0;
			errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
			errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(boolean) */
		} else if(js[t->start] == 'n') {
			checkPendingKey(js, NUL, stream, state);
			DEBUG_PRINTF(("NULL \n"));
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
		DEBUG_PRINTF(("'%.*s'", t->end - t->start, js+t->start));

		errn = updateStringValue(js, t->start, t->end, &state->stringTable, EXI_EXIforJSON_4_string);
		errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
		errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(string) */
		return 1;
	} else if (t->type == JSMN_OBJECT) {
		checkPendingKey(js, MAP, stream, state);
		DEBUG_PRINTF(("{\n"));


		if (errn == 0) {
			j = 0;
			for (i = 0; i < t->size; i++) {
				j += dumpKey(js, t+1+j, count-j, stream, state);
				DEBUG_PRINTF((": "));
				j += dump(js, t+1+j, count-j, stream, state);
				DEBUG_PRINTF(("\n"));
			}

			DEBUG_PRINTF(("}\n"));
			errn = exiEXIforJSONEncodeEndElement(stream, state);  /* EE(map) */
			if(errn != 0) {
				DEBUG_PRINTF(("EXI Error: end object\n"));
			}
		} else {
			DEBUG_PRINTF(("EXI Error: start object\n"));
		}
		return j+1;
	} else if (t->type == JSMN_ARRAY) {
		checkPendingKey(js, ARRAY, stream, state);
		j = 0;
		DEBUG_PRINTF(("[\n"));
		for (i = 0; i < t->size; i++) {
			DEBUG_PRINTF(("   - "));
			j += dump(js, t+1+j, count-j, stream, state);
			DEBUG_PRINTF(("\n"));
		}
		DEBUG_PRINTF(("]\n"));
		errn = exiEXIforJSONEncodeEndElement(stream, state);  /* EE(array) */

		return j+1;
	}
	return 0;
}

int encodeEXIforJSONsharedStrings(const char *json, size_t jlen, uint8_t* buffer, size_t blen, size_t* posEncode, const char ** sharedStrings, size_t stlen) {
	int r, i;
	int errn = 0;
	jsmn_parser p;
	jsmntok_t t[128]; /* We expect no more than 128 tokens */

	pendingKeyStart = 0;

	/* EXI encoder setup*/
	bitstream_t oStream;
	exi_name_table_runtime_t runtimeTableEncode;
	exi_state_t stateEncode;
	exi_value_table_t stringTableEncode = { 0, EXI_EXIforJSONMAX_NUMBER_OF_QNAMES, numberOfLocalStringsEncode, NULL };

	/** string values */
	exi_value_string_table_t stringTableValuesEncode;
	stringTableValuesEncode.size = 0;
	stringTableValuesEncode.len = 0;
	stringTableEncode.valueStringTable = &stringTableValuesEncode;

	/* BINARY memory setup */
	/* val.binary.len = 0;
	val.binary.size = 0;
	val.binary.data = NULL;*/

	/* STRING miss memory setup */
	/* val.str.type = EXI_STRING_VALUE_MISS;
	val.str.miss.len = 0;
	val.str.miss.size = 0;
	val.str.miss.characters = NULL; */

	/* setup output stream */
	oStream.size = blen;
	oStream.data = buffer;
	oStream.pos = (uint16_t*)posEncode;

	/* init encoder (write header, set initial state) */
	errn = exiInitNameTableRuntime(&runtimeTableEncode);
	if (errn==0) {
		errn = exiEXIforJSONInitEncoder(&oStream, &stateEncode, &runtimeTableEncode, &stringTableEncode);

		if(errn == 0 && stlen > 0 && sharedStrings != NULL) {
			exi_string_t sv;
			for(i=0; i<stlen; i++) {
				sv.characters = (exi_string_character_t*)sharedStrings[i];
				sv.len = sv.size = strlen(sharedStrings[i]);
				errn = exiAddStringValue(&stateEncode.stringTable, &sv, EXI_EXIforJSON_2_nil);
			}
		}
	}

	jsmn_init(&p);
	r = jsmn_parse(&p, json, strlen(json), t, sizeof(t)/sizeof(t[0]));
	if (r < 0) {
		DEBUG_PRINTF(("Failed to parse JSON: %d\n", r));
		errn = 1;
	} else {
		errn = exiEXIforJSONEncodeStartDocument(&oStream, &stateEncode);
		if(errn == 0) {
			dump(json, t, p.toknext, &oStream, &stateEncode);
			errn = exiEXIforJSONEncodeEndDocument(&oStream, &stateEncode);
		}

		if (errn) {
			DEBUG_PRINTF(("[Encode-ERROR] %d \n", errn));
		}
	}

	/* free memory if any */
	/* exiFreeDynamicStringMemory(&val.str.miss);*/ /* val.str.miss points to passed JSON string */
	/* exiFreeDynamicBinaryMemory(&val.binary);*/ /* binary not used */
	for(i=stlen; i<stringTableValuesEncode.len; i++) {
		exiFreeDynamicStringMemory(&stringTableValuesEncode.strs[i].str);
	}
	free(stringTableValuesEncode.strs);
	stringTableValuesEncode.strs = 0;


	return errn;
}


int encodeEXIforJSON(const char *json, size_t jlen, uint8_t* buffer, size_t blen, size_t* posEncode) {
	return encodeEXIforJSONsharedStrings(json, jlen, buffer, blen, posEncode, NULL, 0);
}



#endif
