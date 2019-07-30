/**
 *  Author :			Avishai Cohen
 *  Creation date :     19.02.2019
 *  Date last modified :
 * 						
 *  Description : 		this is Dispatcher and Query-Manager Manager
 * 						dqm working-mode roles are:
 * 						1. generate aggregators
 * 						2. start and operate dispatcher thread
 * 						3. start and operate Query-Manager thread
 * 
 **/

#include "macros.h"
#include "subs_container.h"
#include "ops_container.h"
#include "dispatch.h"
#include "qm.h"

#include <pthread.h> /* pthread_create */

int main(void)
{	
	int status;
	OpCont* opcont = NULL;
	SubCont* subcont = NULL;
	QMItems* qm = NULL;
	DispItems* dsp = NULL;
	pthread_t dispatch, queryManager;
	char* outPutPath = "/home/avishai/work/ipc/cdrProject/output/report.txt";
	
	opcont = OpCont_Create(2, PELEPHONE);
	if(!IS_VALID(opcont))
	{
		STDERR_PRINT("OpCont_Create Fail\n");
		return 1;
	}
	
	subcont = SubCont_Create(13);
	if(!IS_VALID(subcont))
	{
		STDERR_PRINT("SubCont_Create Fail\n");
		return 1;
	}
	
	dsp = Disp_Create(opcont, subcont);
	if(!IS_VALID(dsp))
	{
		STDERR_PRINT("Disp_Create Fail\n");
		return 1;
	}
	
	qm = QM_Create(opcont, subcont, outPutPath);
	if(!IS_VALID(qm))
	{
		STDERR_PRINT("QM_Create Fail\n");
		return 1;
	}
	
	status = pthread_create(&dispatch, NULL, Disp_Operate, dsp);
	if(!IS_EQUAL(status, 0)) STDERR_PRINT("dsp pthread_create Fail\n");

	status = pthread_create(&queryManager, NULL, QM_Operate, qm);
	if(!IS_EQUAL(status, 0)) STDERR_PRINT("dsp pthread_create Fail\n");
	
	status = pthread_join(dispatch, NULL);
	if(!IS_EQUAL(status, 0)) STDERR_PRINT("dsp pthread_join Fail\n");
	
	status = pthread_join(queryManager, NULL);
	if(!IS_EQUAL(status, 0)) STDERR_PRINT("qm pthread_join Fail\n");
	
	return 0;
}
