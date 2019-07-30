/** 
 *  @file subs.c
 *  @brief Single Subscriber
 *			
 *  @details  
 *	@Time Created: 13.02.2019
 *  @author Avishai Cohen
 * 
 *  @bug 
 */
#include "sub.h"
#include "macros.h"
#include <stdlib.h> 	/* malloc() */
#include <string.h>		/* strcpy() */
#include <stdio.h>		/* printf() */

#define MAX_SUB_NAME_SIZE 65
#define	DATE_SIZE 11
#define TIME_SIZE 9
#define NUM_OF_CALL_TYPES 5

typedef struct SubData{
	Ulong m_InDur;
	Ulong m_OutDur;
	Ulong m_InSms;
	Ulong m_OutSms;
}SubData;

typedef struct MB{
	float m_Download;
	float m_Upload;
}MB;
	
struct Sub{
	Ulong m_MSISDN;
	SubData m_withinOperator;
	SubData m_outsideOperator;
	MB m_mb;
};
/*************************************************************************************/
							/* PRIMARY FUNCTIONS */
/*************************************************************************************/
Sub* Sub_Create(Ulong _MSISDN)
{
	Sub* sub = NULL;
	
	sub = calloc(1 ,sizeof(Sub));
	if(!sub)
	{
		STDERR_PRINT("sub_Create Fail\n");
		return NULL;
	}
	
	sub->m_MSISDN = _MSISDN;
	
	return sub;
}

void Sub_Destroy(void* _sub)
{
	free((Sub*)_sub);
}

int Sub_Update(void* _sub, void* _c)
{
	Sub* sub = _sub;
	Cdr* c = _c;
	
	switch(Cdr_GetCallType(c))
	{
		case MOC:
			if(IS_EQUAL(Cdr_GetOpId(c), Cdr_GetPartyOperator(c))) sub->m_withinOperator.m_OutDur += Cdr_GetDuration(c);
			else sub->m_outsideOperator.m_OutDur += Cdr_GetDuration(c);
		break;

		case MTC:
			if(IS_EQUAL(Cdr_GetOpId(c), Cdr_GetPartyOperator(c))) sub->m_withinOperator.m_InDur += Cdr_GetDuration(c);
			else sub->m_outsideOperator.m_InDur += Cdr_GetDuration(c);
		break;
		
		case SMSMO:
			if(IS_EQUAL(Cdr_GetOpId(c), Cdr_GetPartyOperator(c))) ++sub->m_withinOperator.m_OutSms;
			else ++sub->m_outsideOperator.m_OutSms;
			break;
			
		case SMSMT:
			if(IS_EQUAL(Cdr_GetOpId(c), Cdr_GetPartyOperator(c))) ++sub->m_withinOperator.m_InSms;
			else ++sub->m_outsideOperator.m_InSms;		
			break;
			
		case GPRS:
			sub->m_mb.m_Download += Cdr_GetDownload(c);
			sub->m_mb.m_Upload += Cdr_GetUpload(c);
		break;	
	}
	
	return 0;
}

int Sub_GetData(void* _sub, void* _line)
{
	Sub* sub = _sub;
	char* line = _line;
	int res = 0;
	
	res = sprintf(line, "ID: %ld, Within:%ld|%ld|%ld|%ld, Outside:%ld|%ld|%ld|%ld MB: %f|%f \n",sub->m_MSISDN, 
		sub->m_withinOperator.m_OutDur, sub->m_withinOperator.m_InDur, sub->m_withinOperator.m_OutSms, sub->m_withinOperator.m_InSms,
		sub->m_outsideOperator.m_OutDur, sub->m_outsideOperator.m_InDur, sub->m_outsideOperator.m_OutSms, sub->m_outsideOperator.m_InSms,
		sub->m_mb.m_Download, sub->m_mb.m_Upload);
	return res;
}

void Sub_Reset(Sub* _sub)
{
	_sub->m_withinOperator.m_OutDur = 0;
	_sub->m_withinOperator.m_InDur = 0;
	_sub->m_withinOperator.m_OutSms = 0;
	_sub->m_withinOperator.m_InSms = 0;
	
	_sub->m_outsideOperator.m_OutDur = 0;
	_sub->m_outsideOperator.m_InDur = 0;
	_sub->m_outsideOperator.m_OutSms = 0;
	_sub->m_outsideOperator.m_InSms = 0;
	
	_sub->m_mb.m_Download = 0;
	_sub->m_mb.m_Upload = 0;
}
/*****************************************************************************/
					/* GET VALUES FUNCS */
/*****************************************************************************/
Ulong* Sub_GetIdAddres(Sub* _sub)
{
	return &_sub->m_MSISDN;
}
/*****************************************************************************/
					/* PRINTING / DEBUG FUNCS */
/*****************************************************************************/
void Sub_PrintValues(Sub* _sub)
{
	printf("ID: %ld, Within:%ld|%ld|%ld|%ld, Outside:%ld|%ld|%ld|%ld MB: %f|%f\n",_sub->m_MSISDN, 
		_sub->m_withinOperator.m_OutDur, _sub->m_withinOperator.m_InDur, _sub->m_withinOperator.m_OutSms, _sub->m_withinOperator.m_InSms,
		_sub->m_outsideOperator.m_OutDur, _sub->m_outsideOperator.m_InDur, _sub->m_outsideOperator.m_OutSms, _sub->m_outsideOperator.m_InSms,
		_sub->m_mb.m_Download, _sub->m_mb.m_Upload);
}
