/*
 * test1.c
 * 
 * Copyright 2019 avishai <avishai@student-ThinkCentre-M58>
 * 
 * This Test includes:
 * 1. Parsing a line into Cdr structure;
 * 2. Sending Cdr into Operators Container
 * 3. Extracting Information From Operators Container 
 * 		and Printing It on Screen
 * 
 */

#include "cdr.h"
#include "operator.h"
#include "ops_container.h"
#include <stdio.h>
#include <string.h>

#define STDERR(STR) fprintf(stderr,STR)

int main(void)
{
	Cdr* c = NULL;
	OpCont* container = NULL;
	int status;
	char opData[1024];
	
	char cdrLine[1024] = "292929292922222|292929292922222|3333|Cellcom Israel|42502|MTC|DD/MM/YYYY|HH:MM:SS|3000|2.3|1.4|292929292922222|42503";
	
	c = Cdr_Create(cdrLine);
	container = OpCont_Create(2, 42504);
	if(container == NULL)
	{
		STDERR("OpCont_Create FAIL\n");
	}
	status = OpCont_Update(container, c);
	if(status != OPCONT_SUCCESS)
	{
		STDERR("OpCont_Update FAIL\n");
		printf("status %d\n",status);
	}
	status = OpCont_GetOperatorData(container, 42503, opData);
	if(status != OPCONT_SUCCESS)
	{
		STDERR("OpCont_GetOperatorData FAIL\n");
		printf("status %d\n",status);
	}
	
	printf("DATA IS ===== %s\n",opData);
	
	status = OpCont_PrintAll(container);
	printf("OpCont_PrintAll status %d\n",status);
	
	Cdr_Destroy(c);
	OpCont_Destroy(container);

	return 0;
}
