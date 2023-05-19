// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 2/12/23.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	template<class Iter>
	class vector_iterator
	{
	public:
		typedef 			Iter									iterator_type;
		typedef typename ft::iterator_traits<Iter>::value_type		value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type	difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer			pointer;
		typedef typename ft::iterator_traits<Iter>::reference		reference;
		typedef	std::random_access_iterator_tag						iterator_category;
	
	public:
		vector_iterator() : _p(nullptr) {}
		~vector_iterator() {}
		template<class Iter2>
		vector_iterator(const vector_iterator<Iter2> &that) : _p(that.base()) {}
		template<class Iter2>
		vector_iterator& operator=(const vector_iterator<Iter2> &that)
		{ _p = that.base(); return *this; }
		explicit vector_iterator(pointer p) : _p(p) {}
		// Base: returns _p
		iterator_type base() const { return _p; }
		// Dereference operators
		reference	operator*() const { return *_p; }
		reference	operator[](difference_type i) const { return _p[i]; }
		pointer		operator->() const { return _p; }
		// Comparison operators
		template<class Iter1, class Iter2> friend bool
		operator==(const vector_iterator<Iter1> &it1, const vector_iterator<Iter2> &it2)
		{ return it1._p == it2._p; }
		template<class Iter1, class Iter2> friend bool
		operator!=(const vector_iterator<Iter1> &it1, const vector_iterator<Iter2> &it2)
		{ return it1._p != it2._p; }
		template<class Iter1, class Iter2> friend bool
		operator<=(const vector_iterator<Iter1> &it1, const vector_iterator<Iter2> &it2)
		{ return it1._p <= it2._p; }
		template<class Iter1, class Iter2> friend bool
		operator>=(const vector_iterator<Iter1> &it1, const vector_iterator<Iter2> &it2)
		{ return it1._p >= it2._p; }
		template<class Iter1, class Iter2> friend bool
		operator< (const vector_iterator<Iter1> &it1, const vector_iterator<Iter2> &it2)
		{ return it1._p <  it2._p; }
		template<class Iter1, class Iter2> friend bool
		operator> (const vector_iterator<Iter1> &it1, const vector_iterator<Iter2> &it2)
		{ return it1._p >  it2._p; }
		// Pre-Increment, Pre-Decrement operators
		vector_iterator& operator++() { ++_p; return *this; }
		vector_iterator& operator--() { --_p; return *this; }
		// Difference between two Iterators
		difference_type operator-(const vector_iterator &that) const
		{ return this->_p - that._p; }
		// Post-Increment, Post-Decrement operators
		vector_iterator operator++(int)
		{ pointer tmp = _p; ++_p; return vector_iterator(tmp); }
		vector_iterator operator--(int)
		{ pointer tmp = _p; --_p; return vector_iterator(tmp); }
		// Add, subtract operators , this +/- int
		vector_iterator operator+(int n) const { return vector_iterator(_p + n); }
		vector_iterator operator-(int n) const { return vector_iterator(_p - n); }
		// Overload operations += and -=
		vector_iterator& operator+=(int n) { _p += n; return *this; }
		vector_iterator& operator-=(int n) { _p -= n; return *this; }
	
	private:
		pointer	_p;
		
	};
	
	template<class Iter>
	vector_iterator<Iter> operator+(int n, const vector_iterator<Iter> &itr) { return itr + n; }
	template<class Iter>
	vector_iterator<Iter> operator-(int n, const vector_iterator<Iter> &itr) { return itr - n; }
	
}
