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
#ifndef _THREAD_BASE_H_
#define _THREAD_BASE_H_

#include "btTypes.hpp"

namespace beatoThread
{
	using namespace btTypes;
	//Thread Base Class
	class btThreadBase
	{
	public:

		btThreadBase(void);
		btThreadBase(const char name);
		virtual ~btThreadBase(void);

		//start up the thread, 
		//Priority, set the thread running priority
		//detach, detach the thread, util for long time running thread, 
		//thath you don't need chath the return, or dont need be wayted 
		void	start(btUint32 Priority = 0, bool detach = false);

		//wait thread end
		int		wait(void);

		//send a exit signal, set true on wait to wait for thread
		int		exit(bool Wait);

		//check if thread is quiting 
		bool	isPendingExit(void) const;

		//get the id of the thread
		const btNativeThrHandle	getThreadID(void) const;

		//check if are the same thread thast make a call 
		bool	isCurretThread(void);

	protected:
		// Worker routine
		virtual int run(void) = 0;
		virtual void notifyExit(void) {};

	private:
		void	applyThreadPriority(void);
		static int threadStaticEntryPoint(void* Ptr);
		
		volatile bool	m_pendingExit;
		btThrHandle		m_threadHandle;
		const char		m_threadName;
		btUint32		m_threadpriority;
	};
};

#endif // !_THREAD_BASE_H_
