// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 12/20/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

namespace ft
{
	// Equal function template
	template<class InputIterator1, class InputIterator2>
	bool equal(InputIterator1 first1, InputIterator1 last1, InputIterator2 first2)
	{
		for ( ; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
				return false;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2)
	{
		for ( ; first1 != last1; ++first1, ++first2)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
		}
		return (first2 != last2);
	}
	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
								  InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		for ( ;first1 != last1; ++first1, ++first2)
		{
			if (first2 == last2 || comp(*first2, *first1))
				return false;
			else if (comp(*first1, *first2))
				return true;
		}
		return (first2 != last2);
	}
}
