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

#define BUFFER_SIZE 8192


int main(int argc, char *argv[]) {
	int errn = 0;

	/* JSON encode example  */
	/* char *JSON_STRING_IN = "{\"keyNumber\":   123, \"k\":-12.34, \"keyArrayStrings\": [ \"s1\", \"s2\" ] , \"valid\": true, \"foo\": null}"; */
	/* test01.json */
	/* char *JSON_STRING_IN = "{\"keyNumber\":   123, \"keyArrayStrings\": [ \"s1\", \"s2\" ] }"; */
	/* http://json.org/example.html #1 */
	/* char *JSON_STRING_IN = "{\n    \"glossary\": {\n        \"title\": \"example glossary\",\n\t\t\"GlossDiv\": {\n            \"title\": \"S\",\n\t\t\t\"GlossList\": {\n                \"GlossEntry\": {\n                    \"ID\": \"SGML\",\n\t\t\t\t\t\"SortAs\": \"SGML\",\n\t\t\t\t\t\"GlossTerm\": \"Standard Generalized Markup Language\",\n\t\t\t\t\t\"Acronym\": \"SGML\",\n\t\t\t\t\t\"Abbrev\": \"ISO 8879:1986\",\n\t\t\t\t\t\"GlossDef\": {\n                        \"para\": \"A meta-markup language, used to create markup languages such as DocBook.\",\n\t\t\t\t\t\t\"GlossSeeAlso\": [\"GML\", \"XML\"]\n                    },\n\t\t\t\t\t\"GlossSee\": \"markup\"\n                }\n            }\n        }\n    }\n}"; */
	/* http://json.org/example.html #2 */
	/* char *JSON_STRING_IN = "{\"menu\": {\n  \"id\": \"file\",\n  \"value\": \"File\",\n  \"popup\": {\n    \"menuitem\": [\n      {\"value\": \"New\", \"onclick\": \"CreateNewDoc()\"},\n      {\"value\": \"Open\", \"onclick\": \"OpenDoc()\"},\n      {\"value\": \"Close\", \"onclick\": \"CloseDoc()\"}\n    ]\n  }\n}}"; */
	/* http://json.org/example.html #3 */
	char *JSON_STRING_IN = "{\"widget\": {\n    \"debug\": \"on\",\n    \"window\": {\n        \"title\": \"Sample Konfabulator Widget\",\n        \"name\": \"main_window\",\n        \"width\": 500,\n        \"height\": 500\n    },\n    \"image\": { \n        \"src\": \"Images/Sun.png\",\n        \"name\": \"sun1\",\n        \"hOffset\": 250,\n        \"vOffset\": 250,\n        \"alignment\": \"center\"\n    },\n    \"text\": {\n        \"data\": \"Click Here\",\n        \"size\": 36,\n        \"style\": \"bold\",\n        \"name\": \"text1\",\n        \"hOffset\": 250,\n        \"vOffset\": 100,\n        \"alignment\": \"center\",\n        \"onMouseUp\": \"sun1.opacity = (sun1.opacity / 100) * 90;\"\n    }\n}}";
	const size_t lenOut = strlen(JSON_STRING_IN) + 100; /* some extra space for decoding differences e.g, number 1 -> 1E0 etc */
	char JSON_STRING_OUT[lenOut];


	uint8_t buffer[BUFFER_SIZE];
	size_t posEncode = 0;
	size_t posDecode = 0;

	printf("FROM: \n%s \n", JSON_STRING_IN);

	errn = encodeEXIforJSON(JSON_STRING_IN, strlen(JSON_STRING_IN), buffer, BUFFER_SIZE, &posEncode);
	if( errn == 0 ) {
		/* OK so far */
		printf("Encoding JSON (len=%d) to EXIforJSON (len=%d) was successful \n", strlen(JSON_STRING_IN), posEncode);

		/* Try to transform it back to JSON again */
		errn = decodeEXIforJSON(buffer, BUFFER_SIZE, &posDecode, JSON_STRING_OUT, lenOut);

		if( errn == 0 ) {
			/* OK */
			printf("Decoding EXIforJSON (len=%d) to JSON (len=%d) to was successful \n", posEncode, strlen(JSON_STRING_OUT));
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

