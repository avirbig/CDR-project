/*
 * subtest.c
 * 
 * Csubyright 2019 avishai <avishai@student-ThinkCentre-M58>
 * 
 * This Test includes:
 * 1. Parsing a line into Cdr structure;
 * 2. Sending Cdr into a single Subscriber
 * 3. Extracting Information From Subscriber as a line of text 
 * 		
 */

#include "cdr.h"
#include "sub.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
	Cdr* c = NULL;
	Sub* sub = NULL;
	
	char cdrLine[1024] = "292929292922222|292929292922222|3333|Cellcom Israel|42502|MOC|DD/MM/YYYY|HH:MM:SS|3000|2.3|1.4|292929292922222|42503";
	
	c = Cdr_Create(cdrLine);
	sub = Sub_Create(Cdr_GetMSISDN(c));
	
	Sub_PrintValues(sub);
	Sub_Update(sub, c);
	Sub_PrintValues(sub);
	
	Cdr_Destroy(c);
	Sub_Destroy(sub);
	return 0;
}
