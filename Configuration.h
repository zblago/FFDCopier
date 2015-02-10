#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "OutputColor.h"
#include "dirent.h"
#include "SrcDest.h"

///
/// Reads the configuration file.
///
class Configuration
{
	private:
		char *path;		
		FILE *confFile;
		DIR *pDIR;
		~Configuration();		
	public:
		void(*ShowMsg)(const char* message, const Color color, bool insertNewLine);
		Configuration();
		SrcDest ReadConfiguration();
};