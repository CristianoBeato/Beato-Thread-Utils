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

#include "btCriticalSection.hpp"

beatoThread::btMutex::btMutex(void)
{
	m_mtxHandle = SDL_CreateMutex();
	SDL_assert(m_mtxHandle);
}

beatoThread::btMutex::~btMutex(void)
{
	SDL_DestroyMutex(static_cast<SDL_mutex*>(m_mtxHandle));
	m_mtxHandle = nullptr;
}

bool beatoThread::btMutex::tryLock(void) const
{
	return (SDL_TryLockMutex(static_cast<SDL_mutex*>(m_mtxHandle)) != -1);
}

void beatoThread::btMutex::lock(void) const
{
	SDL_assert(SDL_LockMutex(static_cast<SDL_mutex*>(m_mtxHandle)) != -1);
}

void beatoThread::btMutex::unlock(void) const
{
	SDL_assert(SDL_UnlockMutex(static_cast<SDL_mutex*>(m_mtxHandle)) != -1);
}

beatoThread::btMutexLock::btMutexLock(btMutex * mtx) : m_mutex(mtx)
{
	m_mutex->lock();
}

beatoThread::btMutexLock::~btMutexLock(void)
{
	m_mutex->unlock();
}
