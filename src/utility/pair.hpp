// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 12/25/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include <algorithm>

namespace ft {

	template<class T1, class T2>
	struct pair {
		typedef T1 first_type;
		typedef T2 second_type;
		
		first_type first;
		second_type second;
		
		pair() : first(first_type()), second(second_type()) {}
		
		template<class U, class V>
		pair(const pair<U, V> &pr) : first(pr.first), second(pr.second) {}
		
		pair(const first_type &a, const second_type &b) : first(a), second(b) {}
		
		pair &operator=(const pair &pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};
	// Relational operators for pair.
	template <class T1, class T2> bool operator ==
	(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
		{ return lhs.first == rhs.first && lhs.second == rhs.second; }
	template <class T1, class T2> bool operator !=
	(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
				{ return !(lhs == rhs); }
	template <class T1, class T2> bool operator <
	(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
	{ return lhs.first<rhs.first || (!(rhs.first<lhs.first) && lhs.second<rhs.second); }
	template <class T1, class T2> bool operator <=
	(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
				{ return !(rhs < lhs); }
	template <class T1, class T2> bool operator >
	(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
				{ return rhs < lhs; }
	template <class T1, class T2> bool operator >=
	(const pair<T1,T2>& lhs, const pair<T1,T2>& rhs)
				{ return !(lhs < rhs); }

	template <class T1,class T2>
	pair<T1,T2> make_pair (T1 x, T2 y)
	{ return (pair<T1,T2>(x,y)); }
}
