#include "Item.h"
#include <string>

Item::Item(char *path, bool isFile)
{
	_path = new char[strlen(path) + 1];
	for (int i = 0; i < (strlen(path) + 1); i++)
	{
		_path[i] = path[i];
	}
	_path[(strlen(path))] = '\0';
			
	_isFile = isFile;
};