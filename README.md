# exificient-for-json.c
EXI for JSON in C programming language.

## Demo program

Sample program to illustrate how to write and read JSON to EXIforJSON

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "EXIforJSONEncoder.h"
#include "EXIforJSONDecoder.h"

#define BUFFER_SIZE 8192


int main(int argc, char *argv[]) {
	int errn = 0;

	char *JSON_STRING_IN = "{\"keyNumber\":   123, \"keyArrayStrings\": [ \"s1\", \"s2\" ] }";
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
```