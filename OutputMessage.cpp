#include "OutputMessage.h"
#include <iostream>
#include <string>
#include "stdafx.h"

using namespace std;

///
/// Printing errors, warnings and information messages.
///

OutputMessage::~OutputMessage() {};
	
OutputMessage::OutputMessage() {};

void OutputMessage::ShowMessage(const char* message, const Color color, bool insertNewLine)
{
	int colorNo = 0;
	switch (color)
	{
		case Color::Red:				
			colorNo = FOREGROUND_RED;
			break;
		case Color::Blue:
			colorNo = 49;
			break;
		case Color::Green:
			colorNo = FOREGROUND_GREEN;
			break;
		default:
			colorNo = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}

	SetConsoleTextAttribute(hConsole, colorNo);
	char cNl = insertNewLine ? '\n' : '\0';
	std:cout << message << cNl;
}

void OutputMessage::ShowMessage(const string message, const Color color, bool insertNewLine)
{
	int colorNo = 0;
	switch (color)
	{
		case Color::Red:
			colorNo = FOREGROUND_RED;
			break;
		case Color::Blue:
			colorNo = 49;
			break;
		case Color::Green:
			colorNo = FOREGROUND_GREEN;
			break;
		default:
			colorNo = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
	}

	SetConsoleTextAttribute(hConsole, colorNo);
	char cNl = insertNewLine ? '\n' : '\0';
	std:cout << message << cNl;
}

HANDLE OutputMessage::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);