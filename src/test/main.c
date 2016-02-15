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
 * <p>Switch for sample programs</p>
 *
 ********************************************************************/

#include <stdio.h>
#include <stdlib.h>


#define RUN_EXI_CODEC 1
#define RUN_JSON_ENCODE 2
#define RUN_EXIforJSON_DECODE 3

#define MAIN_RUN RUN_EXIforJSON_DECODE



#if MAIN_RUN == RUN_EXI_CODEC
int main_codec();
#endif /* RUN_EXI_CODEC */
#if MAIN_RUN == RUN_JSON_ENCODE
int main_json_encode();
#endif /* RUN_JSON_ENCODE */
#if MAIN_RUN == RUN_EXIforJSON_DECODE
int main_exiforjson_decode();
#endif /* RUN_EXIforJSON_DECODE */



int main(int argc, char *argv[]) {
#if MAIN_RUN == RUN_EXI_CODEC
	/* EXI codec only */
	return main_codec(argc, argv);
#endif /* RUN_EXI_CODEC */
#if MAIN_RUN == RUN_JSON_ENCODE
	/* JSON encode example  */
	return main_json_encode(argc, argv);
#endif /* RUN_JSON_ENCODE */
#if MAIN_RUN == RUN_EXIforJSON_DECODE
	/* JSON decode example  */
	return main_exiforjson_decode(argc, argv);
#endif /* RUN_EXIforJSON_DECODE */
}

