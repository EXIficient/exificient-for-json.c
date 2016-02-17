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

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Sample program</p>
 *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EXIforJSONEncoder.h"
#include "EXIforJSONDecoder.h"

#define BUFFER_SIZE 2048

/* ========== JSON SAMPLES */
#define SAMPLE1 "{\"keyNumber\":   123, \"k\":-12.34, \"keyArrayStrings\": [ \"s1\", \"s2\" ] , \"valid\": true, \"foo\": null}"
/* test01.json */
#define SAMPLE2 "{\"keyNumber\":123,\"keyArrayStrings\":[\"s1\",\"s2\"]}"
/* String Hits (local/global) */
#define SAMPLE3 "{\"key1\":\"s1\",\"keyArrayStrings\":[\"s1\",\"s2\"],\"s1\":null} "
/* http://json.org/example.html #1 */
#define SAMPLE4 "{\"glossary\":{\"title\":\"example glossary\",\"GlossDiv\":{\"title\":\"S\",\"GlossList\":{\"GlossEntry\":{\"ID\":\"SGML\",\"SortAs\":\"SGML\",\"GlossTerm\":\"Standard Generalized Markup Language\",\"Acronym\":\"SGML\",\"Abbrev\":\"ISO 8879:1986\",\"GlossDef\":{\"para\":\"A meta-markup language, used to create markup languages such as DocBook.\",\"GlossSeeAlso\":[\"GML\",\"XML\"]},\"GlossSee\":\"markup\"}}}}} "
/* http://json.org/example.html #2 */
#define SAMPLE5 "{\"menu\":{\"id\":\"file\",\"value\":\"File\",\"popup\":{\"menuitem\":[{\"value\":\"New\",\"onclick\":\"CreateNewDoc()\"},{\"value\":\"Open\",\"onclick\":\"OpenDoc()\"},{\"value\":\"Close\",\"onclick\":\"CloseDoc()\"}]}}} "
/* http://json.org/example.html #3 */
#define SAMPLE6 "{\"widget\":{\"debug\":\"on\",\"window\":{\"title\":\"Sample Konfabulator Widget\",\"name\":\"main_window\",\"width\":500,\"height\":500},\"image\":{\"src\":\"Images/Sun.png\",\"name\":\"sun1\",\"hOffset\":250,\"vOffset\":250,\"alignment\":\"center\"},\"text\":{\"data\":\"Click Here\",\"size\":36,\"style\":\"bold\",\"name\":\"text1\",\"hOffset\":250,\"vOffset\":100,\"alignment\":\"center\",\"onMouseUp\":\"sun1.opacity = (sun1.opacity / 100) * 90;\"}}} "
/* https://github.com/w3c/wot/blob/master/TF-TD/TD%20Samples/led.jsonld */
#define SAMPLE7 "{\"@context\":\"http://w3c.github.io/wot/w3c-wot-td-context.jsonld\",\"metadata\":{\"name\":\"MyLED\",\"protocols\":{\"CoAP\":{\"uri\":\"coap://www.example.com:5683/ledlamp\",\"priority\":1},\"HTTP\":{\"uri\":\"http://www.example.com:80/ledlamp\",\"priority\":2}},\"encodings\":[\"JSON\"]},\"interactions\":[{\"@type\":\"Property\",\"name\":\"colorTemperature\",\"outputData\":\"xsd:unsignedShort\",\"writable\":true},{\"@type\":\"Property\",\"name\":\"rgbValueRed\",\"outputData\":\"xsd:unsignedByte\",\"writable\":false},{\"@type\":\"Property\",\"name\":\"rgbValueGreen\",\"outputData\":\"xsd:unsignedByte\",\"writable\":false},{\"@type\":\"Property\",\"name\":\"rgbValueBlue\",\"outputData\":\"xsd:unsignedByte\",\"writable\":false},{\"@type\":\"Action\",\"name\":\"ledOnOff\",\"inputData\":\"xsd:boolean\",\"outputData\":\"\"},{\"@type\":\"Action\",\"name\":\"fadeIn\",\"inputData\":\"xsd:unsignedByte\",\"outputData\":\"\"},{\"@type\":\"Action\",\"name\":\"fadeOut\",\"inputData\":\"xsd:unsignedByte\",\"outputData\":\"\"},{\"@type\":\"Event\",\"outputData\":\"xsd:unsignedShort\",\"name\":\"colorTemperatureChanged\"}]}"
/* ==========  */

/* ========== SHARED STRINGS may be used to establish a shared context between encoder & decoder
 * ========== and allows for increased processing and smaller stream size */
const char *SHARED_STRINGS[] = {"@context","@id","@value","@type","xsd:string","xsd:boolean","xsd:unsignedShort","xsd:unsignedByte", "xsd:float","http://w3c.github.io/wot/w3c-wot-td-context.jsonld","metadata","name","protocols","uri","priority","encodings","interactions","outputData","inputData","writable","Property","Action","Event","CoAP","HTTP","JSON","EXI", "WS"};
const int NUMBER_OF_SHARED_STRINGS = sizeof(SHARED_STRINGS)/sizeof(SHARED_STRINGS[0]);
/* ==========  */


int main(int argc, char *argv[]) {
	int errn = 0;
	const int useSharedStrings = 0; /* make use of shared strings */

	char *JSON_STRING_IN = SAMPLE3;

	const size_t lenOut = strlen(JSON_STRING_IN) + 100; /* some extra space for decoding differences e.g, number 1 -> 1E0 etc */
	char JSON_STRING_OUT[lenOut];

	uint8_t buffer[BUFFER_SIZE];
	size_t posEncode = 0;
	size_t posDecode = 0;

	printf("FROM: \n%s \n", JSON_STRING_IN);

	if(useSharedStrings) {
		errn = encodeEXIforJSONsharedStrings(JSON_STRING_IN, strlen(JSON_STRING_IN), buffer, BUFFER_SIZE, &posEncode, SHARED_STRINGS, NUMBER_OF_SHARED_STRINGS);
	} else {
		errn = encodeEXIforJSON(JSON_STRING_IN, strlen(JSON_STRING_IN), buffer, BUFFER_SIZE, &posEncode);
	}

	if( errn == 0 ) {
		/* OK so far */
		printf("Encoding JSON (len=%d) to EXIforJSON (len=%d) was successful \n", strlen(JSON_STRING_IN), posEncode);

		/* Try to transform it back to JSON again */
		if(useSharedStrings) {
			errn = decodeEXIforJSONsharedStrings(buffer, BUFFER_SIZE, &posDecode, JSON_STRING_OUT, lenOut, SHARED_STRINGS, NUMBER_OF_SHARED_STRINGS);
		} else {
			errn = decodeEXIforJSON(buffer, BUFFER_SIZE, &posDecode, JSON_STRING_OUT, lenOut);
		}

		if( errn == 0 ) {
			/* OK */
			printf("Decoding EXIforJSON (len=%d) to JSON (len=%d) was successful \n", posEncode, strlen(JSON_STRING_OUT));
			printf("TO: \n%s \n", JSON_STRING_OUT);
		} else {
			/* ERROR */
			printf("Decoding EXIforJSON to JSON failed due to error %d \n", errn);
		}
	} else {
		/* ERROR */
		printf("Encoding JSON to EXIforJSON failed due to error %d \n", errn);
	}

	return errn;
}

