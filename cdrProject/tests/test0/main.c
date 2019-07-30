
#include "cdr.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
	Cdr* c = NULL;
	char cdr[1024] = "292929292922222|292929292922222|3333|Cellcom Israel|42502|MTC|DD/MM/YYYY|HH:MM:SS|3000|2.3|1.4|292929292922222|42503";
	
	
	c = Cdr_Create(cdr);
	
	printf("IMSI: %ld\n",Cdr_GetIMSI(c));
	printf("MSISDN: %ld\n",Cdr_GetMSISDN(c));
	printf("IMEI: %ld\n",Cdr_GetIMEI(c));
	printf("OpName: %s\n",Cdr_GetOpName(c));
	printf("OpId: %ld\n",Cdr_GetOpId(c));
	printf("Call_Type: %d\n",Cdr_GetCallType(c));
	printf("Date: %s\n",Cdr_GetDate(c));
	printf("Time: %s\n",Cdr_GetTime(c));
	printf("Duration: %ld\n",Cdr_GetDuration(c));
	printf("Download: %0.3f\n",Cdr_GetDownload(c));
	printf("Upload: %0.3f\n",Cdr_GetUpload(c));
	printf("PartyMSISDN: %ld\n",Cdr_GetPartyMSISDN(c));
	printf("PartyOperator: %ld\n",Cdr_GetPartyOperator(c));
	
	return 0;
}

