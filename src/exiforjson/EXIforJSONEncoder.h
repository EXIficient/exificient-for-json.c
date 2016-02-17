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
 * \file 	EXIforJSONEncoder.h
 * \brief 	EXIforJSON Encoder
 *
 */

#ifndef EXI_FOR_JSON_ENCODER_H
#define EXI_FOR_JSON_ENCODER_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief 		Encode JSON to EXIforJSON
 *
 * \param       json   			JSON string
 * \param       jlen   			JSON string length
 * \param       buffer   		EXIforJSON buffer
 * \param       blen   			EXIforJSON buffer length
 * \param       posEncode		EXIforJSON start (and end after encoding)
 *
 * \return                  	Error-Code <> 0
 *
 */
int encodeEXIforJSON(const char *json, size_t jlen, uint8_t* buffer, size_t blen, size_t* posEncode);

/**
 * \brief 		Encode JSON to EXIforJSON with shared strings
 *
 * \param       json   			JSON string
 * \param       jlen   			JSON string length
 * \param       buffer   		EXIforJSON buffer
 * \param       blen   			EXIforJSON buffer length
 * \param       posEncode   	EXIforJSON start (and end after encoding)
 * \param       sharedStrings   Shared EXI strings
 * \param       stlen   		Shared EXI strings length
 *
 * \return                  	Error-Code <> 0
 *
 */
int encodeEXIforJSONsharedStrings(const char *json, size_t jlen, uint8_t* buffer, size_t blen, size_t* posEncode, const char ** sharedStrings, size_t stlen);


#ifdef __cplusplus
}
#endif

#endif
