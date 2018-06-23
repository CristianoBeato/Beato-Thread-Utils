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
#ifndef _ATOMIC_H_
#define _ATOMIC_H_

#include "btCommon.hpp"
namespace beatoThread
{
	//reference-countable class structure
	class btReferenceCounter
	{
	public:
		btReferenceCounter(void);
		virtual ~btReferenceCounter(void);

		virtual void	IncRefCount(void);
		virtual void    DecRefCount(void);
		virtual void	SetRefCount(int val);
		virtual int		GetRefCount(void);

	private:
		btTypes::btCountHandle	m_counter;
	};

	// Intrusive reference-countable object for garbage collection
	class btRefObj : public btReferenceCounter
	{
	public:
		btRefObj(void) : btReferenceCounter() {};
		virtual ~btRefObj(void) {};

		virtual void	IncRefCount(void);
		virtual void    DecRefCount(void);

		//utils for reference counter
		static void IncRef(void* p);
		static void DecRef(void* p);
	private:

	};
};
#endif // !_ATOMIC_H_
