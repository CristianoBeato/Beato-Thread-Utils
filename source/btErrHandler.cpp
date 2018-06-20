/*
===========================================================================
btThread Source Code
Copyright (C) 2016-2018 Cristiano Beato dos Santos.
cristianobeato_dm@hotmail.com

This file is part of the btThread Source Code ("btThread a Beato SDL2 thread helper library").

btThread Source Code is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

btThread Source Code is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with btThread Source Code.  If not, see <http://www.gnu.org/licenses/>.

In addition, the btThread Source Code is also subject to certain additional terms.
You should have received a copy of these additional terms immediately following the terms and conditions
of the GNU General Public License which accompanied the btThread Source Code.
If not, please request a copy in writing from Cristiano B. S. at the email address below.

If you have questions concerning this license or the applicable additional terms,
you may contact in writing Cristiano "Beato", cristianobeato_dm@hotmail.com.
===========================================================================
*/

#include "btPrecompiledHeader.h"
#pragma hdrstop

#include "btErrHandler.hpp"

static std::vector<std::string> m_errorList = std::vector<std::string>();


#define	MAX_PRINT_MSG_SIZE	4096

static void VprintfStr(std::string & str, const char * fmt, va_list args)
{
	char msg[MAX_PRINT_MSG_SIZE];
	SDL_vsnprintf(msg, MAX_PRINT_MSG_SIZE, fmt, args);

	//append to the string
	str += msg;

	//print the msg in system console (if is build on console mode on windows)
	//std::cout << str;
}


void beatoThread::btErrorHandler::btSetError(const char * fmt, ...)
{
	std::string str;
	va_list argptr;
	va_start(argptr, fmt);
	VprintfStr(str, fmt, argptr);
	va_end(argptr);

	//append mesage to the console log 
	m_errorList.push_back(str);
}

const char * beatoThread::btErrorHandler::btGetErr(void)
{

	btUint32 numErr = 0;
	if (m_errorList.size())
		numErr = m_errorList.size() -1;

	return m_errorList.at(numErr).c_str();
}

void beatoThread::btErrorHandler::btClearError(void)
{
	m_errorList.pop_back();
}

beatoThread::btUint32 beatoThread::btErrorHandler::btGetNumErrors(void)
{
	return m_errorList.size();
}
