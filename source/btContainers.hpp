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

#ifndef _CONTAINERS_H_
#define _CONTAINERS_H_

#include "btCommon.hpp"

namespace beatoThread
{
	template <typename _type_>
	class btVector
	{
	public:
		btVector(void);
		~btVector(void);

		void			clear(void);

		size_t			apend(const _type_ & obj);
		size_t			prepend(const _type_ & obj);
		size_t			insert(const _type_ & obj, int index = 0);

		size_t			findIndex(const _type_ & obj) const;
		
		size_t			num(void) const;
		size_t			numAllocated(void) const;
		size_t			size(void) const;
		
		_type_*			getPtr(void);
		const _type_*	getPtr(void) const;

		const _type_& 	operator[](size_t index) const;
		_type_& 		operator[](size_t index);

		size_t			operator+=(const _type_ & obj);
		size_t			operator+=(const btVector<_type_> & obj);


		_type_& 		alloc(void);

		bool			removeAt(size_t index);
		bool			remove(const _type_ & obj);

	private:
		size_t			m_num;
		size_t			m_size;
		_type_ *		m_array;
	};
};
#endif // !_CONTAINERS_H_
