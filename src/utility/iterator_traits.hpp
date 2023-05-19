// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 12/21/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include <algorithm>

namespace ft
{
	//TODO: Iterator Traits
	template <class Iter>
	struct iterator_traits
	{
		typedef    typename Iter::difference_type	difference_type;
		typedef    typename Iter::value_type		value_type;
		typedef    typename Iter::pointer			pointer;
		typedef    typename Iter::reference			reference;
		typedef    typename Iter::iterator_category	iterator_category;
	};
	
	template <class T>
	struct iterator_traits<T*>
	{
		typedef T                                   value_type;
		typedef ptrdiff_t                           difference_type;
		typedef T*                                  pointer;
		typedef T&                                  reference;
		typedef std::random_access_iterator_tag     iterator_category;
	};
	
	template<class T>
	struct iterator_traits<const T*>
	{
		typedef		T							value_type;
		typedef 	ptrdiff_t					difference_type;
		typedef 	const T*					pointer;
		typedef 	const T&					reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};
}
