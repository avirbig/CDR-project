/**
 *  Author :			Avishai Cohen
 *  Creation date :     13.02.2019
 *  Date last modified :
 * 						
 *  Description : 		file handling API Polling Method
 **/
 
#include <stdio.h> /* FILE */
#include <time.h> /* time_t */


FILE* File_WOpen(const char* _path)
{
	return fopen(_path, "a+");
}

int File_WClose(FILE* _fd)
{
	return fclose(_fd);
}

int FW_WriteSingleLine(const char* _line, FILE* _fd)
{
	return fputs(_line, _fd);
}

int FW_WriteHeader(FILE* _fd)
{
	time_t t;
	struct tm * tm;
	
	t = time(NULL);
	tm = gmtime(&t);
	
	return fprintf(_fd, "%d/%2d/%2d , %2d:%2d:%2d\n\n", tm->tm_year + 1900, tm->tm_mon, tm->tm_mday, tm->tm_hour, tm->tm_min, tm->tm_sec);
}
