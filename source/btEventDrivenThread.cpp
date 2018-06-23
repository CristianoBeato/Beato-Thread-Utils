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

#include "precompiled.h"
#pragma hdrstop

#include "btEventDrivenThread.hpp"

beatoThread::btSynchronousEventDemultiplexer::btSynchronousEventDemultiplexer(void):
	m_currentQueue(0),
	m_asyncQueues(2),
	m_asyncQueue(&m_asyncQueues[0])
{
	m_queueMtx = new btMutex;
}

beatoThread::btSynchronousEventDemultiplexer::~btSynchronousEventDemultiplexer(void)
{
	delete m_queueMtx;
}

void beatoThread::btSynchronousEventDemultiplexer::enqueueCapsule(const btIntrusivePtr<btAsyncEventMethod>& Capsule)
{
	btMutexLock mutex(m_queueMtx);
	m_asyncQueue->push_back(Capsule);
}

void beatoThread::btSynchronousEventDemultiplexer::demultiplexEvents(void)
{
	eventQueue_t* localQueue = &m_asyncQueues[m_currentQueue];

	// switch current queue
	{
		btMutexLock mutex(m_queueMtx);

		m_currentQueue = (m_currentQueue + 1) % 2;
		m_asyncQueue = &m_asyncQueues[m_currentQueue];
	}

	// invoke callbacks
	for (eventQueue_t::iterator envent = localQueue->begin(); envent != localQueue->end(); ++envent)
	{
		(*envent)->invoke();
	}

	localQueue->clear();
}

beatoThread::btDemultiplexThread::btDemultiplexThread(void) : 
	btThreadBase(),
	btSynchronousEventDemultiplexer()
{
}

beatoThread::btDemultiplexThread::~btDemultiplexThread(void)
{
}

int beatoThread::btDemultiplexThread::run(void)
{
	//wait for quit comand
	while (!isPendingExit())
		demultiplexEvents();

	return 0;
}

void beatoThread::btDemultiplexThread::notifyExit(void)
{
}
