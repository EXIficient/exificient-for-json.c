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
#include "EXIforJSONQNames.h"
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

static int dumpFloat(const char *js, int start, int end, bitstream_t* stream,
		exi_state_t* state) {
	int errn;
	/* minus */
	/* dot */
	/* E/e */
	int pos = start;
	int negative = 0;
	int mantissa = 0;
	int exponent = 0;
	int afterDot = 0;

	while (pos < end) {
		if (js[pos] == '-') {
			negative = 1;
		} else if (js[pos] == '+') {
			/* */
		} else if (js[pos] == '.') {
			afterDot = 1;
		} else if ((js[pos] >= '0') && (js[pos] <= '9')) {
			mantissa = (mantissa * 10) + ((js[pos]) - '0');
			if (afterDot) {
				exponent -= 1;
			}
		}
		pos++;
	}

	if (negative) {
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

static int dumpKey(const char *js, jsmntok_t *t, bitstream_t* stream,
		exi_state_t* state) {
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

static int updateStringValue(const char *s, uint16_t start, uint16_t end,
		exi_value_table_t* valueTable, uint16_t qnameID) {
	int errn = 0;
	uint16_t slen = end - start;
	int i, k;
	exi_value_string_table_entry_t* strHit = NULL;
	uint32_t globalID;

	if (valueTable->numberOfGlobalStrings > 0) {
		for (i = 0; i < valueTable->valueStringTable->len && strHit == NULL;
				i++) {
			if (valueTable->valueStringTable->strs[i].str.len == slen) {
				/* compare characters first by length */
				int match = 1;
				for (k = 0; k < slen && match; k++) {
					if (valueTable->valueStringTable->strs[i].str.characters[k]
							!= s[start + k]) {
						/* mis-match */
						match = 0;
					}
				}
				if (match) {
					strHit = &valueTable->valueStringTable->strs[i];
					globalID = i;
				}
			}
		}
	}

	val.type = EXI_DATATYPE_STRING;
	if (strHit == NULL) {
		/* Miss */
		val.str.type = EXI_STRING_VALUE_MISS;
		val.str.miss.len = slen;
		val.str.miss.size = val.str.miss.len;
		val.str.miss.characters = (exi_string_character_t*) &s[start];
	} else {
		/* Hit */
		if (qnameID == strHit->qnameID) {
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
		val.str.miss.characters = (exi_string_character_t*) &s[start];
	}

	return errn;
}

static int checkPendingKey(const char *js, bitstream_t* stream,
		exi_state_t* state) {
	int errn = 0;

	if (pendingKeyStart > 0) {
		errn = updateStringValue(js, pendingKeyStart, pendingKeyEnd,
				state->stringTable, EXI_EXIforJSON_0_key);
		errn = exiEXIforJSONEncodeAttribute(stream, state, EXI_EXIforJSON_0_key,
				&val);

		pendingKeyStart = 0; /* signals no pending key */
	}
	return errn;
}

/*
 * An example of reading JSON and printing its content
 */

static int dump_loop(const char *js, jsmntok_t *t_, bitstream_t* stream,
		exi_state_t* state) {

	typedef struct jsmn_stack {
		jsmntok_t * token;
		int loop_index;
		struct jsmn_stack * parent;
	} jsmn_stack_t;

	jsmn_stack_t root = { 0 };
	root.parent = 0;
	root.loop_index = 0;
	root.token = &t_[0];

	jsmn_stack_t * stack = &root;

	int errn = 0;
	int j = 0;

	while (1) {

		/* If we have an empty object or array at root we need special handling */
		if (stack->parent == 0 && stack->token->size == 0) {

			switch (stack->token->type) {
			case JSMN_ARRAY:
				errn = exiEXIforJSONEncodeStartElement(stream, state,
						EXI_EXIforJSON_4_array);
				break;
			case JSMN_OBJECT:
				errn = exiEXIforJSONEncodeStartElement(stream, state,
						EXI_EXIforJSON_4_map);
				break;
			default:
				/* avoid warnings enumeration value 'FOO' not handled in switch */
				break;
			}

			errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(???) */
		}

		for (; stack->loop_index < stack->token->size;
				stack->loop_index++, j++) {

			/* Root Object has no key */
			if (stack->parent && stack->token->type == JSMN_OBJECT) {
				j += dumpKey(js, &t_[j], stream, state);
			}

			jsmntok_t * t = &t_[j];

			switch (t->type) {
			case JSMN_PRIMITIVE:
				/* number, true, false, or null */
				if (js[t->start] == 't') {
					errn = exiEXIforJSONEncodeStartElement(stream, state,
							EXI_EXIforJSON_4_boolean);

					checkPendingKey(js, stream, state);
					DEBUG_PRINTF(("booleanTrue \n"));
					val.type = EXI_DATATYPE_BOOLEAN;
					val.boolean = 1;
					errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
					errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(boolean) */
				} else if (js[t->start] == 'f') {
					errn = exiEXIforJSONEncodeStartElement(stream, state,
							EXI_EXIforJSON_4_boolean);

					checkPendingKey(js, stream, state);
					DEBUG_PRINTF(("booleanFalse \n"));
					val.type = EXI_DATATYPE_BOOLEAN;
					val.boolean = 0;
					errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
					errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(boolean) */
				} else if (js[t->start] == 'n') {
					errn = exiEXIforJSONEncodeStartElement(stream, state,
							EXI_EXIforJSON_4_null);

					checkPendingKey(js, stream, state);
					DEBUG_PRINTF(("NULL \n"));
					errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(null) */
				} else {
					errn = exiEXIforJSONEncodeStartElement(stream, state,
							EXI_EXIforJSON_4_number);

					checkPendingKey(js, stream, state);
					/* printf("NUMBER %d %d \n", t->start, t->end); */
					/* printf("%.*s", t->end - t->start, js+t->start); */
					dumpFloat(js, t->start, t->end, stream, state);
					errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(number) */
				}
				/* printf("%.*s", t->end - t->start, js+t->start); */
				break;
			case JSMN_STRING:
				errn = exiEXIforJSONEncodeStartElement(stream, state,
						EXI_EXIforJSON_4_string);

				checkPendingKey(js, stream, state);
				DEBUG_PRINTF(("'%.*s'", t->end - t->start, js + t->start));

				errn = updateStringValue(js, t->start, t->end,
						state->stringTable, EXI_EXIforJSON_4_string);
				errn = exiEXIforJSONEncodeCharacters(stream, state, &val);
				errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(string) */
				break;
			case JSMN_OBJECT:
				errn = exiEXIforJSONEncodeStartElement(stream, state,
						EXI_EXIforJSON_4_map);

				checkPendingKey(js, stream, state);
				DEBUG_PRINTF(("{\n"));

				if (errn == 0) {

					jsmn_stack_t * descend = (jsmn_stack_t*) malloc(
							sizeof(jsmn_stack_t));
					/* TODO NULL check */
					descend->parent = stack;
					descend->loop_index = -1; /* will be increased before use by the for-loop */
					descend->token = t;

					if (descend->token->type == JSMN_PRIMITIVE) {
						descend->token->size = 1;
					}

					stack->loop_index++; /* make sure to advance the parent element before descendin*/
					stack = descend;

					/* end element will be encoded later on when we leave the lower stack level */
					if (errn != 0) {
						DEBUG_PRINTF(("EXI Error: end object\n"));
					}
				} else {
					DEBUG_PRINTF(("EXI Error: start object\n"));
				}
				break;
			case JSMN_ARRAY:
				errn = exiEXIforJSONEncodeStartElement(stream, state,
						EXI_EXIforJSON_4_array);

				checkPendingKey(js, stream, state);

				jsmn_stack_t * descend = (jsmn_stack_t*) malloc(
						sizeof(jsmn_stack_t));
				/* TODO NULL check */
				descend->parent = stack;
				descend->loop_index = -1; /* will be increased before use by the for-loop */
				descend->token = t;

				if (descend->token->type == JSMN_PRIMITIVE) {
					descend->token->size = 1;
				}

				stack->loop_index++; /* make sure to advance the parent element before descending */
				stack = descend;

				DEBUG_PRINTF(("[\n"));
				break;
			default:
				/* avoid warnings enumeration value 'FOO' not handled in switch */
				break;
			}
		} /* for */

		/* if we did not complete this object / array do not delete, yet */
		if (stack->loop_index < stack->token->size) {
			continue;
		}

		/* If we went down a level go up again and delete our helper struct from the heap */
		if (stack->parent) {
			switch (stack->token->type) {
			case JSMN_ARRAY:
			case JSMN_OBJECT:
				errn = exiEXIforJSONEncodeEndElement(stream, state); /* EE(???) */
				DEBUG_PRINTF(("(]})\n"));
				break;
			default:
				/* avoid warnings enumeration value 'FOO' not handled in switch */
				break;
			}

			jsmn_stack_t * temp = stack->parent;

			free(stack);

			stack = temp;
		} else {
			/* We are back the root element and done */
			break;
		}
	} /* while(1) */

	return errn;
}

int encodeEXIforJSONsharedStrings(const char *json, size_t jlen,
		uint8_t* buffer, size_t blen, size_t* posEncode,
		const char ** sharedStrings, size_t stlen) {
	int r, i;
	int errn = 0;
	jsmn_parser p;

	pendingKeyStart = 0;

	/* EXI encoder setup*/
	bitstream_t oStream;
	exi_name_table_runtime_t runtimeTableEncode;
	exi_state_t stateEncode;
	exi_value_table_t stringTableEncode =
			{ 0, EXI_EXIforJSONMAX_NUMBER_OF_QNAMES, numberOfLocalStringsEncode,
					NULL };

	/** string values */
	exi_value_string_table_t stringTableValuesEncode;
	stringTableValuesEncode.size = 0;
	stringTableValuesEncode.len = 0;
	stringTableValuesEncode.strs = 0;
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
	oStream.pos = (uint16_t*) posEncode;

	/* init encoder (write header, set initial state) */
	errn = exiInitNameTableRuntime(&runtimeTableEncode);
	if (errn == 0) {
		errn = exiEXIforJSONInitEncoder(&oStream, &stateEncode,
				&runtimeTableEncode, &stringTableEncode);

		if (errn == 0 && stlen > 0 && sharedStrings != NULL) {
			exi_string_t sv;
			for (i = 0; i < stlen; i++) {
				sv.characters = (exi_string_character_t*) sharedStrings[i];
				sv.len = sv.size = strlen(sharedStrings[i]);
				errn = exiAddStringValue(stateEncode.stringTable, &sv,
						EXI_EXIforJSON_2_nil);
			}
		}
	}

	const int jsmnTokens = 128;
	jsmntok_t * t = (jsmntok_t*) malloc(jsmnTokens * sizeof(jsmntok_t));

	jsmn_init(&p);
	r = jsmn_parse(&p, json, strlen(json), t, jsmnTokens);

	if (r < 0) {
		DEBUG_PRINTF(("Failed to parse JSON: %d\n", r));
		errn = 1;
	} else {
		errn = exiEXIforJSONEncodeStartDocument(&oStream, &stateEncode);
		if (errn == 0) {
			dump_loop(json, t, &oStream, &stateEncode);
			errn = exiEXIforJSONEncodeEndDocument(&oStream, &stateEncode);
		}

		if (errn) {
			DEBUG_PRINTF(("[Encode-ERROR] %d \n", errn));
		}
	}

	free(t);
	t = 0;

	/* free memory if any */
	/* exiFreeDynamicStringMemory(&val.str.miss);*//* val.str.miss points to passed JSON string */
	/* exiFreeDynamicBinaryMemory(&val.binary);*//* binary not used */
	for (i = stlen; i < stringTableValuesEncode.len; i++) {
		exiFreeDynamicStringMemory(&stringTableValuesEncode.strs[i].str);
	}
	if (stringTableValuesEncode.strs) {
		free(stringTableValuesEncode.strs);
		stringTableValuesEncode.strs = 0;
	}

	return errn;
}

int encodeEXIforJSON(const char *json, size_t jlen, uint8_t* buffer,
		size_t blen, size_t* posEncode) {
	return encodeEXIforJSONsharedStrings(json, jlen, buffer, blen, posEncode,
			NULL, 0);
}

#endif
