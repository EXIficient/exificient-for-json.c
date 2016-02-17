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


/**
 * \file 	EXIforJSONDecoder.h
 * \brief 	EXIforJSON Decoder
 *
 */

#ifndef EXI_FOR_JSON_DECODER_H
#define EXI_FOR_JSON_DECODER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


#define EXIforJSON_ERROR_NOT_SUPPORTED 21
#define EXIforJSON_ERROR_OUT_OF_STRING 22

#define EXIforJSON_ERROR_UNEXPECTED_JSON_EVENT 30
#define EXIforJSON_ERROR_UNEXPECTED_NUMBER_TYPE 31
#define EXIforJSON_ERROR_UNEXPECTED_BOOLEAN_TYPE 32
#define EXIforJSON_ERROR_UNEXPECTED_STRING_TYPE 33

/**
 * \brief 		Decode EXIforJSON to JSON
 *
 * \param       buffer   		EXIforJSON buffer
 * \param       blen   			EXIforJSON buffer length
 * \param       posDecode   	EXIforJSON start (and end after decoding)
 * \param       json   			JSON string
 * \param       jlen   			JSON string length
 *
 * \return                  	Error-Code <> 0
 *
 */
int decodeEXIforJSON(uint8_t* buffer, size_t blen, size_t* posDecode, char *json, size_t jlen);

/**
 * \brief 		Decode EXIforJSON to JSON with shared strings
 *
 * \param       buffer   		EXIforJSON buffer
 * \param       blen   			EXIforJSON buffer length
 * \param       posDecode   	EXIforJSON start (and end after decoding)
 * \param       json   			JSON string
 * \param       jlen   			JSON string length
 * \param       sharedStrings   Shared EXI strings
 * \param       stlen   		Shared EXI strings length
 *
 * \return                  	Error-Code <> 0
 *
 */
int decodeEXIforJSONsharedStrings(uint8_t* buffer, size_t blen, size_t* posDecode, char *json, size_t jlen, const char ** sharedStrings, size_t stlen);


#ifdef __cplusplus
}
#endif

#endif
