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

#ifndef _EVENT_DRIVEN_H_
#define _EVENT_DRIVEN_H_

namespace beatoThread
{
	//event call class
	class btAsyncEventMethod :
		public btRefObj
	{
	public:
		// Run the method
		virtual void invoke(void) = 0;
	};

	class btSynchronousEventDemultiplexer
	{
		typedef std::vector< btIntrusivePtr<btAsyncEventMethod> > eventQueue_t;
	public:
		btSynchronousEventDemultiplexer(void);
		~btSynchronousEventDemultiplexer(void);

		// Put the event into the events queue
		virtual void    enqueueCapsule(const btIntrusivePtr<btAsyncEventMethod>& Capsule);

	protected:
		// Events demultiplexer as described in Reactor pattern
		virtual void	demultiplexEvents(void);

	private:
		size_t						m_currentQueue;
		std::vector<eventQueue_t>	m_asyncQueues;
		eventQueue_t*				m_asyncQueue;
		btMutex*					m_queueMtx;
	};

	class btDemultiplexThread : 
		public btThreadBase,
		public btSynchronousEventDemultiplexer
	{
	public:
		btDemultiplexThread(void);
		~btDemultiplexThread(void);

	protected:
		// Worker routine
		virtual int run(void);
		virtual void notifyExit(void);

	};
};

#endif // !_EVENT_DRIVEN_H_
