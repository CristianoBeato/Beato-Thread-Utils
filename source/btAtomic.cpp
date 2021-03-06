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

#include "btAtomic.hpp"

beatoThread::btReferenceCounter::btReferenceCounter(void)
{
	m_counter = new SDL_atomic_t;
	SetRefCount(1);
}

beatoThread::btReferenceCounter::~btReferenceCounter(void)
{
	if (m_counter != nullptr)
	{
		delete m_counter;
		m_counter = nullptr;
	}
}

void beatoThread::btReferenceCounter::IncRefCount(void)
{
	SDL_AtomicIncRef(static_cast<SDL_atomic_t*>(m_counter));
}

void beatoThread::btReferenceCounter::DecRefCount(void)
{
	SDL_AtomicDecRef(static_cast<SDL_atomic_t*>(m_counter));
}

void beatoThread::btReferenceCounter::SetRefCount(int val)
{
	SDL_AtomicSet(static_cast<SDL_atomic_t*>(m_counter), val);
}

int beatoThread::btReferenceCounter::GetRefCount(void)
{
	return SDL_AtomicGet(static_cast<SDL_atomic_t*>(m_counter));
}

void beatoThread::btRefObj::IncRefCount(void)
{
	btReferenceCounter::IncRefCount();
}

void beatoThread::btRefObj::DecRefCount(void)
{
	btReferenceCounter::DecRefCount();

	//clear pointer
	int count = GetRefCount();
	if (count < 1)
	{
		delete this;
	}
}

void beatoThread::btRefObj::IncRef(void * p)
{
	if (p)
		reinterpret_cast<btRefObj*>(p)->IncRefCount();
}

void beatoThread::btRefObj::DecRef(void * p)
{
	if (p)
		reinterpret_cast<btRefObj*>(p)->DecRefCount();
}
