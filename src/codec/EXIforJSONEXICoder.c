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
 * @version 2016-02-03 
 * @contact Joerg.Heuer@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: schema-for-json.xsd</p>
 *
 *
 ********************************************************************/



#ifndef EXI_EXIforJSON_CODER_C
#define EXI_EXIforJSON_CODER_C

#include "EXIforJSONEXICoder.h"

#include "EXIConfig.h"
#include "EXITypes.h"
#include "EXIOptions.h"
#include "BitInputStream.h"
#include "DecoderChannel.h"
#include "ErrorCodes.h"

#if MEMORY_ALLOCATION == DYNAMIC_ALLOCATION
#include "StringValueTable.h"
#endif /* DYNAMIC_ALLOCATION */


/* ==================================== */
/* Name Table Population */

/* localName entries for URI '', id = 0 */
/*
  "key"
 */

/* localName entries for URI 'http://www.w3.org/XML/1998/namespace', id = 1 */
/*
  "base",  "id",  "lang",  "space"
 */

/* localName entries for URI 'http://www.w3.org/2001/XMLSchema-instance', id = 2 */
/*
  "nil",  "type"
 */

/* localName entries for URI 'http://www.w3.org/2001/XMLSchema', id = 3 */
/*
  "ENTITIES",  "ENTITY",  "ID",  "IDREF",  "IDREFS",
  "NCName",  "NMTOKEN",  "NMTOKENS",  "NOTATION",  "Name",
  "QName",  "anySimpleType",  "anyType",  "anyURI",  "base64Binary",
  "boolean",  "byte",  "date",  "dateTime",  "decimal",
  "double",  "duration",  "float",  "gDay",  "gMonth",
  "gMonthDay",  "gYear",  "gYearMonth",  "hexBinary",  "int",
  "integer",  "language",  "long",  "negativeInteger",  "nonNegativeInteger",
  "nonPositiveInteger",  "normalizedString",  "positiveInteger",  "short",  "string",
  "time",  "token",  "unsignedByte",  "unsignedInt",  "unsignedLong",
  "unsignedShort"
 */

/* localName entries for URI 'http://www.w3.org/2015/EXI/json', id = 4 */
/*
  "array",  "arrayType",  "base64Binary",  "boolean",  "booleanType",
  "date",  "dateTime",  "decimal",  "integer",  "map",
  "mapType",  "null",  "nullType",  "number",  "numberType",
  "other",  "otherType",  "string",  "stringType",  "time"

 */


/* number of local-name entries per URI */
static uint16_t localNames[5] = {
	/* '' */
	1,
	/* 'http://www.w3.org/XML/1998/namespace' */
	4,
	/* 'http://www.w3.org/2001/XMLSchema-instance' */
	2,
	/* 'http://www.w3.org/2001/XMLSchema' */
	46,
	/* 'http://www.w3.org/2015/EXI/json' */
	20
};


exi_name_table_prepopulated_t exiEXIforJSONNameTablePrepopulated = { 5, localNames };


int exi_EXIforJSON_PushStack(exi_state_t* state, int16_t newState, uint16_t qnameID) {
	int errn = 0;
	/* eqname_t* eqn*/
	if ((state->stackIndex + 1) < EXI_ELEMENT_STACK_SIZE) {
		state->grammarStack[++state->stackIndex] = newState;
		/* qname */
		state->elementStack[state->stackIndex] = qnameID;
	} else {
		errn = EXI_ERROR_OUT_OF_GRAMMAR_STACK;
	}

	return errn;
}

int exi_EXIforJSON_PopStack(exi_state_t* state) {
	int errn = 0;
	if (state->stackIndex >= 1) {
		state->stackIndex--;
	} else {
		errn = EXI_ERROR_OUT_OF_BOUNDS;
	}
	return errn;
}

int exi_EXIforJSON_HandleXsiNilTrue(exi_state_t* state) {
	switch (state->grammarStack[state->stackIndex]) {
	case 46:
		state->grammarStack[state->stackIndex] = 48;
		return 0;

	}

	return EXI_ERROR_UNEXPECTED_ATTRIBUTE_XSI_NIL;
}

int exi_EXIforJSON_HandleXsiType(exi_state_t* state, exi_eqname_t* xsiType) {
	switch(xsiType->namespaceURI) {
	case 0:
		switch(xsiType->localPart) {
		}
		break;
	case 1:
		switch(xsiType->localPart) {
		}
		break;
	case 2:
		switch(xsiType->localPart) {
		}
		break;
	case 3:
		switch(xsiType->localPart) {
		case 0:
			/* {3}0,ENTITIES */
			state->grammarStack[state->stackIndex] = 49;
			break;
		case 1:
			/* {3}1,ENTITY */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 2:
			/* {3}2,ID */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 3:
			/* {3}3,IDREF */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 4:
			/* {3}4,IDREFS */
			state->grammarStack[state->stackIndex] = 49;
			break;
		case 5:
			/* {3}5,NCName */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 6:
			/* {3}6,NMTOKEN */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 7:
			/* {3}7,NMTOKENS */
			state->grammarStack[state->stackIndex] = 49;
			break;
		case 8:
			/* {3}8,NOTATION */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 9:
			/* {3}9,Name */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 10:
			/* {3}10,QName */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 11:
			/* {3}11,anySimpleType */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 12:
			/* {3}12,anyType */
			state->grammarStack[state->stackIndex] = 51;
			break;
		case 13:
			/* {3}13,anyURI */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 14:
			/* {3}14,base64Binary */
			state->grammarStack[state->stackIndex] = 20;
			break;
		case 15:
			/* {3}15,boolean */
			state->grammarStack[state->stackIndex] = 16;
			break;
		case 16:
			/* {3}16,byte */
			state->grammarStack[state->stackIndex] = 53;
			break;
		case 17:
			/* {3}17,date */
			state->grammarStack[state->stackIndex] = 26;
			break;
		case 18:
			/* {3}18,dateTime */
			state->grammarStack[state->stackIndex] = 22;
			break;
		case 19:
			/* {3}19,decimal */
			state->grammarStack[state->stackIndex] = 30;
			break;
		case 20:
			/* {3}20,double */
			state->grammarStack[state->stackIndex] = 14;
			break;
		case 21:
			/* {3}21,duration */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 22:
			/* {3}22,float */
			state->grammarStack[state->stackIndex] = 14;
			break;
		case 23:
			/* {3}23,gDay */
			state->grammarStack[state->stackIndex] = 55;
			break;
		case 24:
			/* {3}24,gMonth */
			state->grammarStack[state->stackIndex] = 57;
			break;
		case 25:
			/* {3}25,gMonthDay */
			state->grammarStack[state->stackIndex] = 59;
			break;
		case 26:
			/* {3}26,gYear */
			state->grammarStack[state->stackIndex] = 61;
			break;
		case 27:
			/* {3}27,gYearMonth */
			state->grammarStack[state->stackIndex] = 63;
			break;
		case 28:
			/* {3}28,hexBinary */
			state->grammarStack[state->stackIndex] = 65;
			break;
		case 29:
			/* {3}29,int */
			state->grammarStack[state->stackIndex] = 28;
			break;
		case 30:
			/* {3}30,integer */
			state->grammarStack[state->stackIndex] = 28;
			break;
		case 31:
			/* {3}31,language */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 32:
			/* {3}32,long */
			state->grammarStack[state->stackIndex] = 28;
			break;
		case 33:
			/* {3}33,negativeInteger */
			state->grammarStack[state->stackIndex] = 28;
			break;
		case 34:
			/* {3}34,nonNegativeInteger */
			state->grammarStack[state->stackIndex] = 67;
			break;
		case 35:
			/* {3}35,nonPositiveInteger */
			state->grammarStack[state->stackIndex] = 28;
			break;
		case 36:
			/* {3}36,normalizedString */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 37:
			/* {3}37,positiveInteger */
			state->grammarStack[state->stackIndex] = 67;
			break;
		case 38:
			/* {3}38,short */
			state->grammarStack[state->stackIndex] = 28;
			break;
		case 39:
			/* {3}39,string */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 40:
			/* {3}40,time */
			state->grammarStack[state->stackIndex] = 24;
			break;
		case 41:
			/* {3}41,token */
			state->grammarStack[state->stackIndex] = 10;
			break;
		case 42:
			/* {3}42,unsignedByte */
			state->grammarStack[state->stackIndex] = 69;
			break;
		case 43:
			/* {3}43,unsignedInt */
			state->grammarStack[state->stackIndex] = 67;
			break;
		case 44:
			/* {3}44,unsignedLong */
			state->grammarStack[state->stackIndex] = 67;
			break;
		case 45:
			/* {3}45,unsignedShort */
			state->grammarStack[state->stackIndex] = 67;
			break;
		}
		break;
	case 4:
		switch(xsiType->localPart) {
		case 1:
			/* {4}1,arrayType */
			state->grammarStack[state->stackIndex] = 2;
			break;
		case 4:
			/* {4}4,booleanType */
			state->grammarStack[state->stackIndex] = 16;
			break;
		case 10:
			/* {4}10,mapType */
			state->grammarStack[state->stackIndex] = 3;
			break;
		case 12:
			/* {4}12,nullType */
			state->grammarStack[state->stackIndex] = 18;
			break;
		case 14:
			/* {4}14,numberType */
			state->grammarStack[state->stackIndex] = 14;
			break;
		case 16:
			/* {4}16,otherType */
			state->grammarStack[state->stackIndex] = 19;
			break;
		case 18:
			/* {4}18,stringType */
			state->grammarStack[state->stackIndex] = 10;
			break;
		}
		break;
	}


	return 0;
}


int exi_EXIforJSON_RetrieveAndPushGlobalGrammar(exi_state_t* state, uint16_t qnameID) {
	int errn = EXI_ERROR_OUT_OF_RUNTIME_GRAMMAR_STACK;
	int i;
	int found = 1;

	/* schema-informed global element --> Stack ID */
	switch(qnameID) {
	case 53:
		errn = exi_EXIforJSON_PushStack(state, 2, 53);
		break;
	case 56:
		errn = exi_EXIforJSON_PushStack(state, 16, 56);
		break;
	case 62:
		errn = exi_EXIforJSON_PushStack(state, 3, 62);
		break;
	case 64:
		errn = exi_EXIforJSON_PushStack(state, 18, 64);
		break;
	case 66:
		errn = exi_EXIforJSON_PushStack(state, 14, 66);
		break;
	case 68:
		errn = exi_EXIforJSON_PushStack(state, 19, 68);
		break;
	case 70:
		errn = exi_EXIforJSON_PushStack(state, 10, 70);
		break;

	default:
		found = 0;
		break;
	}

	if (!found) {
		/* retrieve existing grammar for qname if any available */
		for(i=0; i<state->numberOfRuntimeGrammars && !found; i+=2) {
			if( state->runtimeGrammars[i].qnameID == qnameID ) {
				/* runtime grammar exists already */

				/* push element stack */
				errn = exi_EXIforJSON_PushStack(state, (int16_t)((i+1) * (-1)), qnameID);
				found = 1;
			}
		}

		/* create new runtime grammars if possible and not found already */
		if(!found && (state->numberOfRuntimeGrammars + 2) < (MAX_NUMBER_OF_RUNTIME_ELEMENTS * 2) ) {
			/* StartTagContent StackIds: -1, -3, -5, ... */
			state->runtimeGrammars[state->numberOfRuntimeGrammars].qnameID = qnameID;
			state->runtimeGrammars[state->numberOfRuntimeGrammars].numberOfProductions = 0;
			state->runtimeGrammars[state->numberOfRuntimeGrammars].hasXsiType = 0;
			state->runtimeGrammars[state->numberOfRuntimeGrammars].hasEE = 0;
			/* ElementContent StackIds: -2, -4, -6, ... */
			state->runtimeGrammars[state->numberOfRuntimeGrammars+1].qnameID = qnameID;
			state->runtimeGrammars[state->numberOfRuntimeGrammars+1].numberOfProductions = 1;
			state->runtimeGrammars[state->numberOfRuntimeGrammars+1].hasXsiType = 0;
			state->runtimeGrammars[state->numberOfRuntimeGrammars+1].hasEE = 1;

			/* push element stack */
			errn = exi_EXIforJSON_PushStack(state, (int16_t)((state->numberOfRuntimeGrammars+1) * (-1)), qnameID);

			state->numberOfRuntimeGrammars = (uint16_t)(state->numberOfRuntimeGrammars + 2);
		}
	}

	return errn;
}

#ifndef __GNUC__
#pragma warning( disable : 4100 ) /* warning unreferenced parameter 'qnameID' */
#endif /* __GNUC__ */
int exi_EXIforJSON_LearnAttribute(exi_state_t* state, uint16_t uriID, uint16_t localID) {
	int errn = 0;
	int16_t currentID = state->grammarStack[state->stackIndex];
	int16_t runtimeID;

	if (currentID < 0) {
		runtimeID = (int16_t)((currentID+1)*(-1));

		if (uriID == 2 && localID == 1 ) {
			/* xsi:type: learned just once */
			if(!state->runtimeGrammars[runtimeID].hasXsiType) {
				/* hasXsiType stores production position PLUS 1 (one) */
				state->runtimeGrammars[runtimeID].hasXsiType = ++state->runtimeGrammars[runtimeID].numberOfProductions;
			}
		} else {
			/* increment production count */
			++state->runtimeGrammars[runtimeID].numberOfProductions;
			/* TODO store production information. Note: not necessary in restricted profile */
		}
	} else {
		/* schema-informed grammar do no evolve */
	}

	return errn;
}
#ifndef __GNUC__
#pragma warning( default : 4100 ) /* warning unreferenced parameter 'qnameID' */
#endif /* __GNUC__ */

int exi_EXIforJSON_LearnEndElement(exi_state_t* state) {
	int errn = 0;
	int16_t currentID = state->grammarStack[state->stackIndex];
	int16_t runtimeID;

	if (currentID < 0) {
		if( exi_EXIforJSON_IsStartContent(currentID) ) {
			/* check whether EE with an event code of length 1 does not exist in the current element grammar already */
			runtimeID = (int16_t)((currentID+1)*(-1));

			if(!state->runtimeGrammars[runtimeID].hasEE) {
				/* hasXsiType stores production position PLUS 1 (one) */
				state->runtimeGrammars[runtimeID].hasEE = ++state->runtimeGrammars[runtimeID].numberOfProductions;
			}
		} else {
			/* ElementContent disposes already of an EE event */
		}
	} else {
		/* schema-informed grammar do no evolve */
	}

	return errn;
}


/*
 * RUNTIME RULES
 * each rule has 2 ids and counts backwards from -1, -2, ...
 * 1) StartTagContent (e.g., -1, -3, -5, ...)
 * 2) ElementContent (e.g., -2, -4, -6)
 *
 */

int exi_EXIforJSON_IsStartContent(int16_t ruleID) {
	/* Note: only for built-in element grammars */
	return (ruleID % 2 != 0);
}

int exi_EXIforJSON_MoveToElementContentRule(exi_state_t* state) {
	int errn = 0;
	int16_t currentID = state->grammarStack[state->stackIndex];
	int found = 1;


	switch (currentID) {
	case 35:
		/* FirstStartTag[ATTRIBUTE[STRING](key), CHARACTERS[FLOAT]] --> FirstStartTag[CHARACTERS[FLOAT]] */
	case 36:
		/* StartTag[CHARACTERS[FLOAT]] --> FirstStartTag[CHARACTERS[FLOAT]] */
		state->grammarStack[state->stackIndex] = 14;
		break;
	case 59:
		/* FirstStartTag[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
		state->grammarStack[state->stackIndex] = 60;
		break;
	case 46:
		/* First(xsi:type)(xsi:nil)StartTag[ATTRIBUTE[STRING](key), ATTRIBUTE_GENERIC, START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
		state->grammarStack[state->stackIndex] = 47;
		break;
	case 49:
		/* FirstStartTag[CHARACTERS[LIST]] --> Element[CHARACTERS[LIST]] */
		state->grammarStack[state->stackIndex] = 50;
		break;
	case 69:
		/* FirstStartTag[CHARACTERS[NBIT_UNSIGNED_INTEGER]] --> Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		state->grammarStack[state->stackIndex] = 70;
		break;
	case 16:
		/* FirstStartTag[CHARACTERS[BOOLEAN]] --> Element[CHARACTERS[BOOLEAN]] */
		state->grammarStack[state->stackIndex] = 17;
		break;
	case 53:
		/* FirstStartTag[CHARACTERS[NBIT_UNSIGNED_INTEGER]] --> Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		state->grammarStack[state->stackIndex] = 54;
		break;
	case 18:
		/* FirstStartTag[END_ELEMENT] --> Element[END_ELEMENT] */
	case 39:
		/* FirstStartTag[ATTRIBUTE[STRING](key), END_ELEMENT] --> Element[END_ELEMENT] */
	case 40:
		/* StartTag[END_ELEMENT] --> Element[END_ELEMENT] */
	case 48:
		/* FirstStartTag[ATTRIBUTE[STRING](key), ATTRIBUTE_GENERIC, END_ELEMENT] --> Element[END_ELEMENT] */
		state->grammarStack[state->stackIndex] = 11;
		break;
	case 30:
		/* FirstStartTag[CHARACTERS[DECIMAL]] --> Element[CHARACTERS[DECIMAL]] */
		state->grammarStack[state->stackIndex] = 31;
		break;
	case 14:
		/* FirstStartTag[CHARACTERS[FLOAT]] --> Element[CHARACTERS[FLOAT]] */
		state->grammarStack[state->stackIndex] = 15;
		break;
	case 24:
		/* FirstStartTag[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
		state->grammarStack[state->stackIndex] = 25;
		break;
	case 63:
		/* FirstStartTag[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
		state->grammarStack[state->stackIndex] = 64;
		break;
	case 20:
		/* FirstStartTag[CHARACTERS[BINARY_BASE64]] --> Element[CHARACTERS[BINARY_BASE64]] */
		state->grammarStack[state->stackIndex] = 21;
		break;
	case 57:
		/* FirstStartTag[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
		state->grammarStack[state->stackIndex] = 58;
		break;
	case 67:
		/* FirstStartTag[CHARACTERS[UNSIGNED_INTEGER]] --> Element[CHARACTERS[UNSIGNED_INTEGER]] */
		state->grammarStack[state->stackIndex] = 68;
		break;
	case 2:
		/* FirstStartTag[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] */
	case 7:
		/* FirstStartTag[ATTRIBUTE[STRING](key), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] */
	case 8:
		/* StartTag[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] */
		state->grammarStack[state->stackIndex] = 9;
		break;
	case 28:
		/* FirstStartTag[CHARACTERS[INTEGER]] --> Element[CHARACTERS[INTEGER]] */
		state->grammarStack[state->stackIndex] = 29;
		break;
	case 19:
		/* FirstStartTag[START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal)] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal)] */
	case 41:
		/* FirstStartTag[ATTRIBUTE[STRING](key), START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal)] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal)] */
	case 42:
		/* StartTag[START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal)] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal)] */
		state->grammarStack[state->stackIndex] = 32;
		break;
	case 51:
		/* FirstStartTag[ATTRIBUTE_GENERIC, START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] --> Element[START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
		state->grammarStack[state->stackIndex] = 52;
		break;
	case 37:
		/* FirstStartTag[ATTRIBUTE[STRING](key), CHARACTERS[BOOLEAN]] --> FirstStartTag[CHARACTERS[BOOLEAN]] */
	case 38:
		/* StartTag[CHARACTERS[BOOLEAN]] --> FirstStartTag[CHARACTERS[BOOLEAN]] */
		state->grammarStack[state->stackIndex] = 16;
		break;
	case 61:
		/* FirstStartTag[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
		state->grammarStack[state->stackIndex] = 62;
		break;
	case 3:
		/* FirstStartTag[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] */
	case 4:
		/* FirstStartTag[ATTRIBUTE[STRING](key), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] */
	case 5:
		/* StartTag[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] */
		state->grammarStack[state->stackIndex] = 6;
		break;
	case 22:
		/* FirstStartTag[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
		state->grammarStack[state->stackIndex] = 23;
		break;
	case 65:
		/* FirstStartTag[CHARACTERS[BINARY_HEX]] --> Element[CHARACTERS[BINARY_HEX]] */
		state->grammarStack[state->stackIndex] = 66;
		break;
	case 10:
		/* FirstStartTag[CHARACTERS[STRING]] --> Element[CHARACTERS[STRING]] */
		state->grammarStack[state->stackIndex] = 13;
		break;
	case 0:
		/* Document[START_DOCUMENT] --> Document[START_DOCUMENT] */
	case 1:
		/* DocContent[START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT_GENERIC] --> DocContent[START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT_GENERIC] */
	case 6:
		/* Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] */
	case 9:
		/* Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), END_ELEMENT] */
	case 11:
		/* Element[END_ELEMENT] --> Element[END_ELEMENT] */
	case 12:
		/* Element[] --> Element[] */
	case 13:
		/* Element[CHARACTERS[STRING]] --> Element[CHARACTERS[STRING]] */
	case 15:
		/* Element[CHARACTERS[FLOAT]] --> Element[CHARACTERS[FLOAT]] */
	case 17:
		/* Element[CHARACTERS[BOOLEAN]] --> Element[CHARACTERS[BOOLEAN]] */
	case 21:
		/* Element[CHARACTERS[BINARY_BASE64]] --> Element[CHARACTERS[BINARY_BASE64]] */
	case 23:
		/* Element[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
	case 25:
		/* Element[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
	case 27:
		/* Element[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
	case 29:
		/* Element[CHARACTERS[INTEGER]] --> Element[CHARACTERS[INTEGER]] */
	case 31:
		/* Element[CHARACTERS[DECIMAL]] --> Element[CHARACTERS[DECIMAL]] */
	case 32:
		/* Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal)] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal)] */
	case 43:
		/* DocEnd[END_DOCUMENT] --> DocEnd[END_DOCUMENT] */
	case 44:
		/* Fragment[START_DOCUMENT] --> Fragment[START_DOCUMENT] */
	case 45:
		/* FragmentContent[START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT_GENERIC, END_DOCUMENT] --> FragmentContent[START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT_GENERIC, END_DOCUMENT] */
	case 47:
		/* Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] --> Element[START_ELEMENT({http://www.w3.org/2015/EXI/json}array), START_ELEMENT({http://www.w3.org/2015/EXI/json}base64Binary), START_ELEMENT({http://www.w3.org/2015/EXI/json}boolean), START_ELEMENT({http://www.w3.org/2015/EXI/json}date), START_ELEMENT({http://www.w3.org/2015/EXI/json}dateTime), START_ELEMENT({http://www.w3.org/2015/EXI/json}decimal), START_ELEMENT({http://www.w3.org/2015/EXI/json}integer), START_ELEMENT({http://www.w3.org/2015/EXI/json}map), START_ELEMENT({http://www.w3.org/2015/EXI/json}null), START_ELEMENT({http://www.w3.org/2015/EXI/json}number), START_ELEMENT({http://www.w3.org/2015/EXI/json}other), START_ELEMENT({http://www.w3.org/2015/EXI/json}string), START_ELEMENT({http://www.w3.org/2015/EXI/json}time), START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
	case 50:
		/* Element[CHARACTERS[LIST]] --> Element[CHARACTERS[LIST]] */
	case 52:
		/* Element[START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] --> Element[START_ELEMENT_GENERIC, END_ELEMENT, CHARACTERS_GENERIC[STRING]] */
	case 54:
		/* Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] --> Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
	case 56:
		/* Element[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
	case 58:
		/* Element[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
	case 60:
		/* Element[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
	case 62:
		/* Element[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
	case 64:
		/* Element[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
	case 66:
		/* Element[CHARACTERS[BINARY_HEX]] --> Element[CHARACTERS[BINARY_HEX]] */
	case 68:
		/* Element[CHARACTERS[UNSIGNED_INTEGER]] --> Element[CHARACTERS[UNSIGNED_INTEGER]] */
	case 70:
		/* Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] --> Element[CHARACTERS[NBIT_UNSIGNED_INTEGER]] */
		break;
	case 55:
		/* FirstStartTag[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
		state->grammarStack[state->stackIndex] = 56;
		break;
	case 26:
		/* FirstStartTag[CHARACTERS[DATETIME]] --> Element[CHARACTERS[DATETIME]] */
		state->grammarStack[state->stackIndex] = 27;
		break;
	case 33:
		/* FirstStartTag[ATTRIBUTE[STRING](key), CHARACTERS[STRING]] --> FirstStartTag[CHARACTERS[STRING]] */
	case 34:
		/* StartTag[CHARACTERS[STRING]] --> FirstStartTag[CHARACTERS[STRING]] */
		state->grammarStack[state->stackIndex] = 10;
		break;

	default:
		found = 0;
		break;
	}

	if(!found) {
		if (currentID < 0) {
			if(exi_EXIforJSON_IsStartContent(currentID)) {
				state->grammarStack[state->stackIndex] = (int16_t)(currentID - 1);
			}
		} else {
			errn = EXI_ERROR_UNEXPECTED_ATTRIBUTE_MOVE_TO_CONTENT_RULE;
		}
	}

	return errn;
}


#endif

