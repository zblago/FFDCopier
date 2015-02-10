#include "StringUtil.h"
#include <string.h>

///
/// Use for join two char arrays.
///

char *StringUtil::Join(const char *string1, const char *string2)
{
	int sizeSource = strlen(string1);
	int sizeDestination = strlen(string2);
	int sumSize = sizeSource + sizeDestination;

	char* retString = new char [sumSize+1];
	retString[sumSize] = '\0';

	for(int i = 0; i < sizeSource; i++)
	{
		*(retString+i) = string1[i];														
	}						
			
	for(int i = sizeSource, j = 0;  j < strlen(string2); i++, j++)
	{
		retString[i] = string2[j];
	}
	return retString;
}
char *StringUtil::Join(const char *string1, const char delimiter, const char *string2)
{
	int sizeSource = strlen(string1);
	int sizeDestination = strlen(string2);
	int sumSize = sizeSource + sizeDestination + 1;

	char* retString = new char [sumSize + 1];
	retString[sumSize] = '\0';

	for(int i = 0; i < sizeSource; i++)
	{
		*(retString+i) = string1[i];														
	}						

	*(retString+strlen(string1)) = delimiter;
	for(int i = sizeSource + 1, j = 0;  j < strlen(string2); i++, j++)
	{
		retString[i] = string2[j];
	}

	return retString;
}
