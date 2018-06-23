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
#ifndef _COMMON_H_
#define _COMMON_H_

#if (defined(__WIN32__) || defined(__WINRT__)) && !defined(__GNUC__)
#define BT_THREAD_CALL __cdecl
#elif defined(__OS2__) || defined(__EMX__)
#	define BT_THREAD_CALL _System
#	if defined (__GNUC__) && !defined(_System)
#		define _System /* for old EMX/GCC compat.  */
#	endif
#else
#define BT_THREAD_CALL
#endif

#if defined(__BTTH_DLL__)	//build as a shared lib (.dll/.so)
#	if defined(_MSC_VER) || defined(__BORLANDC__)
#		define BT_THREAD_API extern __declspec(dllexport)
#	elif defined(__GNUC__) && __GNUC__>=4
#		define BT_THREAD_API extern __attribute__ ((visibility("default")))
#	endif //
#elif (__BTTH_STC__)		//build as a static lib
#	define BT_THREAD_API extern
#else						//integrated in the executable
#	define BT_THREAD_API
#endif // !defined(__BTTH_DLL__)

//CREATE THE INLINE KEY
#if defined(__GNUC__)
#	define BT_THREAD_INLINE __inline__
#elif defined(_MSC_VER) || defined(__BORLANDC__)
#	define BT_THREAD_INLINE __inline
#	ifndef __inline__
#		define __inline__ __inline
#	endif
#else
#	define BT_THREAD_INLINE inline
#		ifndef __inline__
#			define __inline__ inline
#		endif
#endif

//CREATE THE FORCE INLINE KEY
#if defined(_MSC_VER)
#	define BT_THREAD_FORCE_INLINE __forceinline
#elif ( (defined(__GNUC__) && (__GNUC__ >= 4)) || defined(__clang__) )
#	define BT_THREAD_FORCE_INLINE __attribute__((always_inline)) static __inline__
#else
#	define BT_THREAD_FORCE_INLINE static BT_THREAD_INLINE
#endif

namespace beatoThread
{
	namespace btTypes
	{
		//typedef void*	btThrHandle;
		typedef void*			btThrHandle;
		typedef	void*			btCountHandle;
		typedef void*			btMutexHandle;
		typedef unsigned long	btNativeThrHandle;

		typedef	signed char			btSint8;
		typedef	unsigned char		btUint8;
		typedef	signed short		btSint16;
		typedef	unsigned short		btUint16;
		typedef	signed int			btSint32;
		typedef	unsigned int		btUint32;
		typedef	signed long long	btSint64;
		typedef	unsigned long long	btUint64;
	};

};
#endif // !_COMMON_H_
