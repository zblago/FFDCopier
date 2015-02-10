#include "Configuration.h"
#include "OutputColor.h"
#include <stdio.h>

///
/// Reads the configuration file.
///

Configuration::Configuration(){			
	pDIR = opendir(".");
	if (pDIR == nullptr)
	{
		this->ShowMsg("Error when opening conf.txt\n", Color::Red, true);
	}
	else
	{
		char confFileName [9] =  { 'c', 'o', 'n', 'f', '.', 't', 'x', 't', '\0' };
		dirent *currDir = readdir(pDIR);				

		path = new char[wcslen(pDIR->wdirp->patt) + strlen(confFileName)];
		path[wcslen(pDIR->wdirp->patt) + strlen(confFileName) - 1] = '\0';
		for (int i = 0; i < wcslen(pDIR->wdirp->patt) - 1; i++)
		{
			path[i] = pDIR->wdirp->patt[i];
		}
		for (int i = (wcslen(pDIR->wdirp->patt)) - 1, j = 0; i < (wcslen(pDIR->wdirp->patt) - 1 + strlen(confFileName)); i++, j++)
		{
			path[i] = confFileName[j];
		}
	}			
}

SrcDest Configuration::ReadConfiguration()
{
	char *line = new char[10000];
	SrcDest srcDest;
	srcDest.destination = new char[500];
	srcDest.source = new char[500];
	srcDest.isError = false;

	bool isNewLine = false;
	fopen_s(&confFile, path, "r");
	if(confFile == NULL)
	{
		this->ShowMsg("Error when opening conf.txt\n", Color::Red, true);
		srcDest.isError = true;

		return srcDest;
	}
	else
	{
		int c, counter = 0;		
		size_t n = 0;
		int newLineCount = 0;
		while ((c = fgetc(confFile)) != EOF)
		{					
			line[n++] = (char) c;				

			if (!isNewLine)
			{						
				srcDest.source[counter] = (char)c != '\n' ? char(c) : '\0';
			}					
			else
				srcDest.destination[counter] = (char)c != '\n' ? char(c) : '\0';

			if(c == '\n')
			{
				if (isNewLine) break;
				isNewLine = true;
				counter = 0;
			}
			else
			{
				++counter;
			}
		}
					
		fclose(confFile);
	}			
	return srcDest;	
}

Configuration::~Configuration()
{
	delete[] path;
}
