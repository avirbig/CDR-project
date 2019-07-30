/*
 * test1.c
 * 
 * Copyright 2019 avishai <avishai@student-ThinkCentre-M58>
 * 
 * This Test includes:
 * 1. Parsing a line into Cdr structure;
 * 2. Sending Cdr into a single Operator
 * 3. Extracting Information From Operator as a line of text 
 * 		
 */

#include "cdr.h"
#include "operator.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
	Cdr* c = NULL;
	Op* op = NULL;
	
	char cdrLine[1024] = "292929292922222|292929292922222|3333|Cellcom Israel|42502|MTC|DD/MM/YYYY|HH:MM:SS|3000|2.3|1.4|292929292922222|42503";
	
	c = Cdr_Create(cdrLine);
	op = Op_Create(42504, "Orange");
	
	Op_PrintValues(op);
	Op_Update(op, c);
	Op_PrintValues(op);
	
	Cdr_Destroy(c);
	Op_Destroy(op);
	return 0;
}
