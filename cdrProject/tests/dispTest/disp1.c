
#include "macros.h"
#include "dispatch.h"
#include "ops_container.h"
#include "subs_container.h"

int main(void)
{	
	OpCont* opcont = NULL;
	SubCont* subcont = NULL;
	
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
	
	Dispatcher(opcont, subcont);
	
	return 0;
}
