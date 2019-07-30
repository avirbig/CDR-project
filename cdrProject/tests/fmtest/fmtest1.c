/*
 * fmtest1.c
 * 
 * Copyright 2019 avishai <avishai@student-ThinkCentre-M58>
 * 
 * This is Test for fm.c module 
 * 
 */
 
#include "fm.h"
#include "macros.h"

#include <stdio.h>
#include <string.h>

int main(void)
{
	int res;
		
	res = File_ScanExecMove("start/", "working/", "done/");
	
	printf("res %d\n", res);
	
	return 0;
}





