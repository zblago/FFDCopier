#include "OutputColor.h"
#include <iostream>
#include <string>
#include <windows.h>

using namespace std;

///
/// Printing errors, warnings and information messages.
///
class OutputMessage
{
	private:		
		~OutputMessage();
	public: 
		static HANDLE hConsole;
		OutputMessage();
		static void ShowMessage(const char* message, const Color color, bool insertNewLine = true);
		static void ShowMessage(const string message, const Color color, bool insertNewLine = true);
};