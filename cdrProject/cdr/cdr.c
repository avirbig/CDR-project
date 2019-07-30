
#include "cdr.h"
#include <string.h> /* strtok_r() */
#include <stdlib.h> /* malloc() */
#include <stdio.h> /* FILE */

#define MAX_OP_NAME_SIZE 65
#define	DATE_SIZE 11
#define TIME_SIZE 9
#define NUM_OF_CALL_TYPES 5

const char* CallTypes[] = {"MOC", "MTC", "SMSMO", "SMSMT", "GPRS"};

struct Cdr{
	Ulong 			m_IMSI;
	Ulong 			m_MSISDN;
	Ulong 			m_IMEI;
	char 			m_OpName[MAX_OP_NAME_SIZE];
	size_t 			m_OpId;
	Call_Type 		m_CallType;
	char 			m_Date[DATE_SIZE];
	char 			m_Time[TIME_SIZE];
	Ulong 			m_Duration;
	float 			m_Download;
	float 			m_Upload;
	Ulong 			m_PartyMSISDN;
	size_t 			m_PartyOperator;
};

void Cdr_Print(FILE* _fd, Cdr* _c)
{
	fprintf(_fd, "%ld|%ld|%ld|%s|%ld|%d|%s|%s|%ld|%f|%f|%ld|%ld",
			_c->m_IMSI,_c->m_MSISDN,_c->m_IMEI,_c->m_OpName,_c->m_OpId,_c->m_CallType,_c->m_Date,_c->m_Time,_c->m_Duration,_c->m_Download,_c->m_Upload,_c->m_PartyMSISDN,_c->m_PartyOperator);
}

static void ParseLine(Cdr* _c, char* _line)
{
	int i = 0;
	char* delim = "|";
	char* token = NULL;
	char* savePtr = _line;
	
	token = strtok_r(_line, delim, &savePtr);
	_c->m_IMSI = atol(token);
	token = strtok_r(NULL, delim, &savePtr);
	_c->m_MSISDN = atol(token);
	token = strtok_r(NULL, delim, &savePtr);
	_c->m_IMEI = atol(token);
	token = strtok_r(NULL, delim, &savePtr);
	strcpy(_c->m_OpName,token);
	token = strtok_r(NULL, delim, &savePtr);
	_c->m_OpId = atoi(token);
	
	token = strtok_r(NULL, delim, &savePtr);
	for(i = 0; i < NUM_OF_CALL_TYPES; ++i)
	{
		if(!strcmp(token, CallTypes[i]))
		{
			_c->m_CallType = i;
		}
	}
	
	token = strtok_r(NULL, delim, &savePtr);
	strcpy(_c->m_Date, token);
	token = strtok_r(NULL, delim, &savePtr);
	strcpy(_c->m_Time, token);
	token = strtok_r(NULL, delim, &savePtr);
	_c->m_Duration = atol(token);
	token = strtok_r(NULL, delim, &savePtr);
	_c->m_Download = atof(token);
	token = strtok_r(NULL, delim, &savePtr);
	_c->m_Upload = atof(token);
	token = strtok_r(NULL, delim, &savePtr);
	_c->m_PartyMSISDN = atol(token);
	token = strtok_r(NULL, delim, &savePtr);
	_c->m_PartyOperator = atoi(token);
}

Cdr* Cdr_Create(char* _line)
{
	Cdr* c = NULL;
	
	c = malloc(sizeof(Cdr));
	if(!c)
	{
		return NULL;
	}
	
	ParseLine(c, _line);
	
	return c;
}

void Cdr_Destroy(Cdr* _c)
{
	if(NULL == _c)
	{
		return;
	}
	
	free(_c);
}
/*****************************************************************************/
					/* GET VALUES FUNCS */
/*****************************************************************************/
Ulong Cdr_GetIMSI(Cdr* _c)
{
	return _c->m_IMSI;
}

Ulong Cdr_GetMSISDN(Cdr* _c)
{
	return _c->m_MSISDN;
}

Ulong Cdr_GetIMEI(Cdr* _c)
{
	return _c->m_IMEI;
}

char* Cdr_GetOpName(Cdr* _c)
{
	return _c->m_OpName;
}

size_t Cdr_GetOpId(Cdr* _c)
{
	return _c->m_OpId;
}

Call_Type Cdr_GetCallType(Cdr* _c)
{
	return _c->m_CallType;
}

char* Cdr_GetDate(Cdr* _c)
{
	return _c->m_Date;
}

char* Cdr_GetTime(Cdr* _c)
{
	return _c->m_Time;
}

Ulong Cdr_GetDuration(Cdr* _c)
{
	return _c->m_Duration;
}

float Cdr_GetDownload(Cdr* _c)
{
	return _c->m_Download;
}

float Cdr_GetUpload(Cdr* _c)
{
	return _c->m_Upload;
}

Ulong Cdr_GetPartyMSISDN(Cdr* _c)
{
	return _c->m_PartyMSISDN;
}

size_t Cdr_GetPartyOperator(Cdr* _c)
{
	return _c->m_PartyOperator;
}
