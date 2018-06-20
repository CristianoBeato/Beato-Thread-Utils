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

#include "btThreadBase.hpp"

typedef SDL_Thread btThrHandle;

beatoThread::btThreadBase::btThreadBase(void) : 
	m_pendingExit(false),
	m_threadHandle(nullptr),
	m_threadName(NULL)
{

}

beatoThread::btThreadBase::btThreadBase(const char name):
	m_pendingExit(false),
	m_threadHandle(nullptr),
	m_threadName(name)
{
}

beatoThread::btThreadBase::~btThreadBase(void)
{
	if (m_threadHandle != nullptr)
	{
		delete m_threadHandle;
		m_threadHandle = nullptr;
	}
}

void beatoThread::btThreadBase::start(beatoThread::btUint32 Priority, bool detach)
{
	void* thrParam = reinterpret_cast<void*>(this);
	m_threadHandle = SDL_CreateThread(threadStaticEntryPoint, (char*)m_threadName, thrParam);

	if (!m_threadHandle)
	{
		btErrorHandler::btSetError("btThreadBase::start() Error on create Thread %s", SDL_GetError());
		return;
	}

	if (detach)
		SDL_DetachThread((SDL_Thread*)m_threadHandle);
}

int beatoThread::btThreadBase::wait(void)
{
	int status = -1;
	SDL_WaitThread((SDL_Thread*)m_threadHandle, &status);
	return status;
}

int beatoThread::btThreadBase::exit(bool _wait)
{
	int returnStatus = 0;
	m_pendingExit = true;

	//notify the worker that thread is exiting
	notifyExit();

	//quit and don't wait for thread end
	if (!_wait)
		return returnStatus;

	//wait thread end the job
	if (!isCurretThread())
		returnStatus = this->wait();

	return returnStatus;
}

bool beatoThread::btThreadBase::isPendingExit(void) const
{
	return m_pendingExit;
}

const beatoThread::btTypes::btNativeThrHandle beatoThread::btThreadBase::getThreadID(void) const
{
	return SDL_GetThreadID((SDL_Thread*)m_threadHandle);
}

bool beatoThread::btThreadBase::isCurretThread(void)
{
	return SDL_ThreadID() == SDL_GetThreadID((SDL_Thread*)m_threadHandle);;
}

void beatoThread::btThreadBase::applyThreadPriority(void)
{
	SDL_ThreadPriority prior[3];
	if (m_threadpriority > 2)
	{
		SDL_SetThreadPriority(SDL_THREAD_PRIORITY_HIGH);
		return;
	}

	SDL_SetThreadPriority(prior[m_threadpriority]);
}

int beatoThread::btThreadBase::threadStaticEntryPoint(void * ptr)
{
	int retunRes = -1;
	// get thread handler
	btThreadBase *thrHand = reinterpret_cast<btThreadBase*>(ptr);
	if (thrHand)
	{
		thrHand->applyThreadPriority();
		retunRes = thrHand->run();
	}

	return retunRes;

}
