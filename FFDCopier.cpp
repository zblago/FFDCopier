// BackupFolder.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include "dirent.h"
#include "direct.h"
#include <stdio.h>
#include <string.h>
#include <ctime>
#include <string>
#include "windows.h"

#include "StringUtil.h"
#include "DirCopier.h"
#include "Configuration.h"
#include "OutputMessage.h"

using namespace std;

int main(int argc, char** argv)
{
	OutputMessage *outMsg = new OutputMessage();

	Configuration *conf = new Configuration();
	conf->ShowMsg = outMsg->ShowMessage;
	SrcDest confText;	

	if (argc == 3)
	{	
		confText.source = argv[1];
		confText.destination = argv[2];		
		confText.isError = false;
	}
	else
	{		
		confText = conf->ReadConfiguration();		
	}
	
	if (!confText.isError)
	{	
		outMsg->ShowMessage("Configuration:", Color::None, true);
		outMsg->ShowMessage(confText.source, Color::None, true);
		outMsg->ShowMessage(confText.destination, Color::None, true);
		outMsg->ShowMessage("Do you want to proceed? (y/n)", Color::None, false);

		char inputProcced = 'y';
		cin >> inputProcced;

		if (inputProcced == 'y')
		{
			char *destFolder;
			DirCopier *dic = new DirCopier();
			dic->ShowMsg = outMsg->ShowMessage;
			destFolder = dic->CreateDestinationFolder(confText.destination);
			if (destFolder != nullptr && destFolder != "")
			{
				dic->CopyDirsAndFiles(confText.source, destFolder);
			}

			cout << "\n";
			outMsg->ShowMessage(to_string(dic->fileCount) + " files copied.", Color::Blue);
			outMsg->ShowMessage(to_string(dic->folderCount) + " folders copied.", Color::Blue);
		}
		else
		{
			outMsg->ShowMessage("Thanks for nothing!", Color::None);
		}
	}
		
	cin.sync();
	cin.get();
	outMsg->ShowMessage("", Color::None);
}