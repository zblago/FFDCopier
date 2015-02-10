#include "DirCopier.h"
#include "StringUtil.h"

void DirCopier::Rollback()
{
	this->ShowMsg("Rollback in progress.\n", Color::Red, true);
			
	wchar_t *tempW = nullptr;
	size_t convertedChars = 0;			
	for (int i = items.size() - 1; i >= 0; i--)
	{
		bool x = items[i]._isFile;
		if(items[i]._isFile)
		{
			this->ShowMsg(items[i]._path, Color::Red, true);
			if(remove(items[i]._path) == 0)
			{
				this->ShowMsg("File deleted sucessfully.", Color::Red, true);
				--fileCount;
			}
			else
			{
				this->ShowMsg("Error when remove file.", Color::Red, true);
			}
		}
		else
		{
			this->ShowMsg(items[i]._path, Color::Red, true);
			tempW = new wchar_t[strlen(items[i]._path) + 1];
			mbstowcs_s(&convertedChars, tempW, strlen(items[i]._path) + 1, items[i]._path, _TRUNCATE);					
			if(RemoveDirectory(tempW) == 0) 
			{
				this->ShowMsg("Error when remove folder.", Color::Red, true);
			}
			else
			{
				this->ShowMsg("Folder deleted sucessfully.", Color::Red, true);
				--folderCount;
			}
			delete [] tempW;
		}
	}

	if(RemoveDirectory(rollbackFolder) == 0)
	{
		this->ShowMsg("Error when removing root destination folder.\n", Color::Red, true);
	}
	else
	{
		this->ShowMsg("Rollback is finished.\n", Color::Red, true);
	}			
}

DirCopier::~DirCopier(){
	delete [] dest;
};

DirCopier::DirCopier()
{
	dest = new char[1];
	firstIterate = true;
	folderCount = 0;
	fileCount = 0;
	ffcounter = 0;
}

char* DirCopier::CreateDestinationFolder(char *pDest){ 

	time_t timer;
	tm localTime;
	timer = time(nullptr);			
	localtime_s(&localTime, &timer);
			
	string sdest;
	string fullPath;

	//Destination root
	if(opendir(pDest) == nullptr)
	{
		if(_mkdir(pDest) == -1)
		{
			this->ShowMsg("Error when creating folder.\n", Color::Red, true);
			return "";
		}
	}

	//Folder with date format
	sdest = pDest;
	fullPath = sdest + "\\" + to_string(localTime.tm_mday) + "-" + to_string(localTime.tm_mon + 1) + "-" + to_string(localTime.tm_year + 1900);
						
	dest = new char[fullPath.length()+1];
	for (int i = 0; i < fullPath.length(); i++){
		dest[i] = fullPath[i];				
	}
	dest[fullPath.length()]= '\0';

	if(opendir(dest) == nullptr)
	{
		if(_mkdir(dest) == -1)
		{
			this->ShowMsg("Error when creating folder.\n", Color::Red, true);
			return "";
		}
	}
	else
	{
		fullPath = sdest + "\\" + to_string(localTime.tm_mday) + "-" + to_string(localTime.tm_mon + 1) + "-" + to_string(localTime.tm_year + 1900) + "-" 
			+ (localTime.tm_hour < 10 ? "0" : "") + to_string(localTime.tm_hour) 
			+ (localTime.tm_min < 10  ? "0": "") + to_string(localTime.tm_min);
		dest = new char[fullPath.length()+1];
		for (int i = 0; i < fullPath.length(); i++){
			dest[i] = fullPath[i];				
		}
		dest[fullPath.length()]= '\0';
		if(opendir(dest) == nullptr)
		{
			if(_mkdir(dest) == -1)
			{
				this->ShowMsg("Error when creating folder.\n", Color::Red, true);
				return "";
			}
		}
		else
		{					
			char *errMsg = StringUtil::Join(StringUtil::Join("Folder with name ", dest), " already exist.");
			this->ShowMsg(errMsg, Color::Red, true);

			return "";
		}
	}			
	return dest;
}

int DirCopier::CopyDirsAndFiles(char* sourceDir, char* destDir){
			
	if(firstIterate)
	{
		int len = strlen(destDir) + 1;
		int errorCode = 0;
		wchar_t *wtext = new wchar_t[len];
		size_t convertedChars = 0;

		errorCode = mbstowcs_s(&convertedChars, wtext, strlen(destDir) + 1, destDir, _TRUNCATE);
		if(errorCode != 0)
		{					
			this->ShowMsg("Error when creating rollback folder path.\n", Color::Red, true);
			cin.get();

			return -1;
		}
		else
		{
			LPWSTR ptr = wtext;

			rollbackFolder = wtext;
			firstIterate = false;					
		}
	}

	DIR *pDIR = nullptr;
	pDIR = opendir(sourceDir);

	if(pDIR != nullptr)			
	{
		dirent *currDir;				
		while(currDir = readdir(pDIR)){
			str:string d_name = currDir->d_name;
			if(d_name.compare(".") == 0 || d_name.compare("..")==0) continue;
														   
			//Folder
			if(currDir->d_type == 16384) {						
						
				int retF = 0;
				int size1 = 0;
				char* destPath = StringUtil::Join(destDir, '\\', currDir->d_name);													
											
				this->ShowMsg(destPath, Color::Green, true);

				retF = _mkdir(destPath);
				if(retF == -1)
				{
					closedir(pDIR);
					this->ShowMsg("Error when creating folder.\n", Color::Red, true);
					if(!firstIterate) this->Rollback();
					return -1;
				}

				++ffcounter;
				++folderCount;

				Item *it = new Item(destPath, false);						
				items.push_back(*it);						
				delete it;

				size1 = wcslen(pDIR->wdirp->patt);
				size1 = pDIR->wdirp->patt[wcslen(pDIR->wdirp->patt) - 1] == '*' ? size1 - 1 : size1;						
				char *castStr = new char[size1];
				for(int i = 0; i < size1; i++)
				{
					castStr[i] = pDIR->wdirp->patt[i];
				}
				castStr[size1] = '\0';

				char *newPath = StringUtil::Join(castStr, currDir->d_name);
						
				this->CopyDirsAndFiles(newPath, destPath);

				delete []newPath;
				delete []destPath;
			}
			//File
			else
			{
				char* sourceTempDir = new char [wcslen(pDIR->wdirp->patt)];
				sourceTempDir[wcslen(pDIR->wdirp->patt) - 1] = '\0';
				for(int i=0; i < wcslen(pDIR->wdirp->patt) - 1; i++)
				{
					sourceTempDir[i] = pDIR->wdirp->patt[i];
				}
						
				//Source
				char* source = StringUtil::Join(sourceTempDir, currDir->d_name);

				//Destination						
				char* destination = StringUtil::Join(destDir, '\\', currDir->d_name);
						
				wchar_t *s = new wchar_t[strlen(source) + 1];
				s[strlen(source)] = '\0';
				wchar_t *d = new wchar_t[strlen(destination) + 1];
				s[strlen(source)] = '\0';
				size_t convertedChars = 0;

				mbstowcs_s(&convertedChars, d, strlen(destination) + 1, destination, _TRUNCATE);  
				mbstowcs_s(&convertedChars, s, strlen(source) + 1, source, _TRUNCATE);  

				this->ShowMsg(destination, Color::Green, true);
				if(CopyFile(s, d, FALSE) == 0)
				{
					closedir(pDIR);
					this->ShowMsg("Error when copying files.\n", Color::Red, true);
					this->Rollback();

					return -1;
				}

				++ffcounter;
				++fileCount;

				Item *it = new Item(destination, true);
				items.push_back(*it);
				delete it;

				delete [] s;
				delete [] d;
				delete [] source;
				delete [] destination;
				delete [] sourceTempDir;
			}
		}
		closedir(pDIR);		
	}
	else
	{
		this->ShowMsg("Error when opening folder.\n", Color::Red, true);				
	}
};