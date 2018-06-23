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

#ifndef _INSTRUSIVE_PTR_H_
#define _INSTRUSIVE_PTR_H_

#include "btCommon.hpp"
namespace beatoThread
{
	template <typename T>
	class btIntrusivePtr
	{
	public:
		//default constructor
		btIntrusivePtr(void);
		// copy constructor
		btIntrusivePtr(const btIntrusivePtr& Ptr);
		template <typename U>
		btIntrusivePtr(const btIntrusivePtr<U>& Ptr);
		//type constructor
		btIntrusivePtr(T* const Object);

		~btIntrusivePtr(void);

		// check if the pointer is valid
		bool	validade(void) const;

		//manualy clear the ptr
		void	clear(void);

		//acess operators
		BT_THREAD_INLINE T &operator*(void);
		BT_THREAD_INLINE const T &operator*(void) const;
		BT_THREAD_INLINE T *operator->(void);
		BT_THREAD_INLINE const T *operator->(void) const;

		// assignment of clPtr
		BT_THREAD_INLINE btIntrusivePtr& operator = (const btIntrusivePtr& Ptr);

		// helper
		BT_THREAD_INLINE T* getInternalPtr(void) const;

		//casting
		template <typename U> BT_THREAD_INLINE btIntrusivePtr<U> dynamicCast(void) const;
		template <typename U> BT_THREAD_INLINE const U* dynamicCastType(void) const;
		template <typename U> BT_THREAD_INLINE const btIntrusivePtr<U> staticCast(void) const;
		template <typename U> BT_THREAD_INLINE btIntrusivePtr<U> staticCast(void);
		template <typename U> BT_THREAD_INLINE const U* staticCastType(void) const;

	private:
		T * m_ptr;
	};

	template<typename T>
	BT_THREAD_INLINE btIntrusivePtr<T>::btIntrusivePtr(void) : m_ptr(nullptr)
	{
	}

	template<typename T>
	BT_THREAD_INLINE btIntrusivePtr<T>::btIntrusivePtr(const btIntrusivePtr & Ptr) : m_ptr(Ptr.m_ptr)
	{
		btRefObj::IncRef(m_ptr);
	}

	template<typename T>
	BT_THREAD_INLINE btIntrusivePtr<T>::btIntrusivePtr(T * const Object) : m_ptr(Object)
	{
		btRefObj::IncRef(m_ptr);
	}

	template<typename T>
	BT_THREAD_INLINE btIntrusivePtr<T>::~btIntrusivePtr(void)
	{
		btRefObj::DecRef(m_ptr);
	}

	template<typename T>
	BT_THREAD_INLINE bool btIntrusivePtr<T>::validade(void) const
	{
		return m_ptr != nullptr;
	}

	template<typename T>
	BT_THREAD_INLINE void btIntrusivePtr<T>::clear(void)
	{
		delete m_ptr;
		m_ptr = nullptr;
	}

	template<typename T>
	BT_THREAD_INLINE T & btIntrusivePtr<T>::operator*(void)
	{
		return *m_ptr;
	}

	template<typename T>
	BT_THREAD_INLINE const T & btIntrusivePtr<T>::operator*(void) const
	{
		return *m_ptr;
	}

	template<typename T>
	BT_THREAD_INLINE T * btIntrusivePtr<T>::operator->(void)
	{
		return m_ptr;
	}

	template<typename T>
	BT_THREAD_INLINE const T * btIntrusivePtr<T>::operator->(void) const
	{
		return m_ptr;
	}

	template<typename T>
	BT_THREAD_INLINE btIntrusivePtr<T> & btIntrusivePtr<T>::operator=(const btIntrusivePtr<T> & Ptr)
	{
		T* Temp = m_ptr;
		m_ptr = Ptr.m_ptr;

		btRefObj::IncRef(Ptr.m_ptr);
		btRefObj::DecRef(Temp);

		return *this;
	}

	template<typename T>
	BT_THREAD_INLINE T * btIntrusivePtr<T>::getInternalPtr(void) const
	{
		return m_ptr;
	}

	template<typename T>
	template<typename U>
	BT_THREAD_INLINE btIntrusivePtr<U> btIntrusivePtr<T>::dynamicCast(void) const
	{
		return btIntrusivePtr<U>(dynamic_cast<U*>(m_ptr));
	}

	template<typename T>
	template<typename U>
	BT_THREAD_INLINE const U * btIntrusivePtr<T>::dynamicCastType(void) const
	{
		return dynamic_cast<const U*>(m_ptr);
	}

	template<typename T>
	template<typename U>
	BT_THREAD_INLINE const btIntrusivePtr<U> btIntrusivePtr<T>::staticCast(void) const
	{
		return btIntrusivePtr<U>(static_cast<U*>(m_ptr));
	}

	template<typename T>
	template<typename U>
	BT_THREAD_INLINE btIntrusivePtr<U> btIntrusivePtr<T>::staticCast(void)
	{
		return btIntrusivePtr<U>(static_cast<U*>(m_ptr));
	}

	template<typename T>
	template<typename U>
	BT_THREAD_INLINE const U * btIntrusivePtr<T>::staticCastType(void) const
	{
		return static_cast<const U*>(m_ptr);
	}
}
#endif // _INSTRUSIVE_PTR_H_
