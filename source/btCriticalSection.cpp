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

#include "btCriticalSection.hpp"

btMutex::btMutex(void)
{
	m_mtxHandle = SDL_CreateMutex();
	SDL_assert(m_mtxHandle);
}

btMutex::~btMutex(void)
{
	SDL_DestroyMutex(m_mtxHandle);
	m_mtxHandle = nullptr;
}

bool btMutex::tryLock(void) const
{
	return (SDL_TryLockMutex(m_mtxHandle) != -1);
}

void btMutex::lock(void) const
{
	SDL_assert(SDL_LockMutex(m_mtxHandle) != -1);
}

void btMutex::unlock(void) const
{
	SDL_assert(SDL_UnlockMutex(m_mtxHandle) != -1);
}

btMutexLock::btMutexLock(btMutex * mtx) : m_mutex(mtx)
{
	m_mutex->lock();
}

btMutexLock::~btMutexLock(void)
{
	m_mutex->unlock();
}
