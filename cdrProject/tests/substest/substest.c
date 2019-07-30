/*
 * test1.c
 * 
 * Csubyright 2019 avishai <avishai@student-ThinkCentre-M58>
 * 
 * This Test includes:
 * 1. Parsing a line into Cdr structure;
 * 2. Sending Cdr into Subscribers Container
 * 3. Extracting Information From Subscribers Container 
 * 		and Printing It on Screen
 * 
 */

#include "cdr.h"
#include "sub.h"
#include "subs_container.h"
#include "macros.h"

#include <stdio.h>
#include <string.h>

int main(void)
{
	Cdr* c = NULL;
	SubCont* container = NULL;
	int status;
	char subData[1024];
	
	char cdrLine[1024] = "292929292922222|292929292922222|3333|Cellcom Israel|42502|MTC|DD/MM/YYYY|HH:MM:SS|3000|2.3|1.4|292929292922222|42503";
	char cdrLine1[1024] = "292929292922221|292929292922221|3333|Fellcom Israel|42502|MTC|DD/MM/YYYY|HH:MM:SS|3000|2.3|1.4|292929292922222|42503";

	c = Cdr_Create(cdrLine);
	container = SubCont_Create(15);
	if(container == NULL)
	{
		STDERR_PRINT("SubCont_Create FAIL\n");
	}
	status = SubCont_Update(container, c);
	if(status != SUBCONT_SUCCESS)
	{
		STDERR_PRINT("SubCont_Update FAIL\n");
		printf("status %d\n",status);
	}
	Cdr_Destroy(c);
	
	c = Cdr_Create(cdrLine1);
	status = SubCont_Update(container, c);
	if(status != SUBCONT_SUCCESS)
	{
		STDERR_PRINT("SubCont_Update FAIL\n");
		printf("status %d\n",status);
	}
	
	status = SubCont_GetSubscriberData(container, 292929292922222, subData);
	if(status != SUBCONT_SUCCESS)
	{
		STDERR_PRINT("SubCont_GetSubscriberData FAIL\n");
		printf("status %d\n",status);
	}
	
	printf("DATA IS ===== %s\n",subData);
	
	status = SubCont_GetSubscriberData(container, 292929292922221, subData);
	if(status != SUBCONT_SUCCESS)
	{
		STDERR_PRINT("SubCont_GetSubscriberData FAIL\n");
		printf("status %d\n",status);
	}
	
	printf("DATA IS ===== %s\n",subData);
	
	status = SubCont_PrintAll(container);
	printf("SubCont_PrintAll status %d\n",status);
	
	Cdr_Destroy(c);
	SubCont_Destroy(container);

	return 0;
}
