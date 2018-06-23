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

#ifndef _ERROR_HANDLER_H_
#define _ERROR_HANDLER_H_

#include "btCommon.hpp"

namespace beatoThread
{
	using namespace btTypes;
	namespace btErrorHandler
	{
		//this set a cont string error
		BT_THREAD_API void	BT_THREAD_CALL				btSetError(const char * fmt, ...);
		//get the last err
		BT_THREAD_API const char* BT_THREAD_CALL		btGetErr(void);
		//clear the last error
		BT_THREAD_API void	BT_THREAD_CALL				btClearError(void);
		//get the number of sistem errors
		BT_THREAD_API btUint32	BT_THREAD_CALL			btGetNumErrors(void);

	};
};
#endif // !_ERROR_HANDLER_H_
