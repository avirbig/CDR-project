
#include "operator.h"
#include <stdlib.h> 	/* malloc() */
#include <string.h>		/* strcpy() */
#include <stdio.h>		/* printf() */

#define MAX_OP_NAME_SIZE 65
#define	DATE_SIZE 11
#define TIME_SIZE 9
#define NUM_OF_CALL_TYPES 5

#define STDERR_NOT_EQUAL_STATUS(VAR, VAL,STR) if((VAR) != (VAL)) fprintf(stderr,STR)
#define STDERR(STR) fprintf(stderr,STR)


struct Op{
	char m_OpName[MAX_OP_NAME_SIZE];
	size_t m_OpId;
	Ulong m_InDuration;
	Ulong m_OutDuration;
	Ulong m_InSMS;
	Ulong m_OutSMS;
};
/*************************************************************************************/
							/* PRIMARY FUNCTIONS */
/*************************************************************************************/
Op* Op_Create(size_t _id, char* _name)
{
	Op* op = NULL;
	
	op = malloc(sizeof(Op));
	if(!op)
	{
		STDERR("operator  Create Fail\n");
		return NULL;
	}
	
	strcpy(op->m_OpName, _name);
	op->m_OpId = _id;
	op->m_InDuration = 0;
	op->m_OutDuration = 0;
	op->m_InSMS = 0;
	op->m_OutSMS = 0;
	
	return op;
}

void Op_Destroy(void* _op)
{
	free((Op*)_op);
}

int Op_Update(void* _op, void* _c)
{
	Op* op = _op;
	Cdr* c = _c;
	
	switch(Cdr_GetCallType(c))
	{
		case MOC:
			op->m_OutDuration += Cdr_GetDuration(c);
		break;

		case MTC:
			op->m_InDuration += Cdr_GetDuration(c);
		break;
		
		case SMSMO:
			++op->m_OutSMS;
		break;		
		
		case SMSMT:
			++op->m_InSMS;
		break;	
		
		case GPRS:
		break;	
	}
	
	return 0;
}

int Op_GetData(void* _op, void* _line)
{
	Op* op = _op;
	char* line = _line;
	
	sprintf(line, "NAME: %s , ID: %ld, InDur: %ld, OutDur: %ld, InSMS: %ld, OutSMS: %ld\n",op->m_OpName, op->m_OpId, op->m_InDuration, op->m_OutDuration, op->m_InSMS, op->m_OutSMS);
	
	return 0;
}

void Op_Reset(Op* _op)
{
	_op->m_InDuration = 0;
	_op->m_OutDuration = 0;
	_op->m_InSMS = 0;
	_op->m_OutSMS = 0;
}
/*****************************************************************************/
					/* GET VALUES FUNCS */
/*****************************************************************************/
char* Op_GetOpName(Op* _op)
{
	return _op->m_OpName;
}

size_t Op_GetID(Op* _op)
{
	return _op->m_OpId;
}

Ulong Op_GetInDuration(Op* _op)
{
	return _op->m_InDuration;
}

Ulong Op_GetOutDuration(Op* _op)
{
	return _op->m_OutDuration;
}

Ulong Op_GetInSMS(Op* _op)
{
	return _op->m_InSMS;
}

Ulong Op_GetOutSMS(Op* _op)
{
	return _op->m_OutSMS;
}
/*****************************************************************************/
					/* PRINTING VALUES FUNCS */
/*****************************************************************************/
void Op_PrintValues(Op* _op)
{
	printf("NAME: %s , ID: %ld, InDur: %ld, OutDur: %ld, InSMS: %ld, OutSMS: %ld\n",_op->m_OpName, _op->m_OpId, _op->m_InDuration, _op->m_OutDuration, _op->m_InSMS, _op->m_OutSMS);

}
