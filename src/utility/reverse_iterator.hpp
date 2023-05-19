// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 9/22/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include "iterator_traits.hpp"

namespace ft
{
	//TODO: Reverse iterator
	template<class Iter>
	class reverse_iterator
	{
	public:
		typedef				Iter										iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category	iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type			value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type		difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer				pointer;
		typedef typename ft::iterator_traits<Iter>::reference			reference;

	public:
		reverse_iterator() {}
		~reverse_iterator() {}
		template<class Iter2>
		reverse_iterator(const reverse_iterator<Iter2> &that) : _data(that.base()) {}
		template<class Iter2>
		reverse_iterator& operator=(const reverse_iterator<Iter2> &that)
				{ _data = that.base(); return *this; }
		explicit reverse_iterator(Iter data) : _data(data) {}
		// Base: returns _data
		iterator_type base() const { return _data; }
		// Dereference operators
		reference	operator*()		const { Iter t = _data; return *(--t); }
		pointer		operator->()	const { Iter t = _data; return &(*(--t)); }
		reference	operator[](difference_type i) const { return *(*this + i); }
		// Pre-Increment, Pre-Decrement operators
		reverse_iterator& operator++() { --_data; return *this; }
		reverse_iterator& operator--() { ++_data; return *this; }
		// Post-Increment, Post-Decrement operators
		reverse_iterator operator++(int)
			{ iterator_type t = _data; --_data; return reverse_iterator(t); }
		reverse_iterator operator--(int)
			{ iterator_type t = _data; ++_data; return reverse_iterator(t); }
		// Add, subtract operators , this +- int
		reverse_iterator operator+(int n) const { return reverse_iterator(_data - n); }
		reverse_iterator operator-(int n) const { return reverse_iterator(_data + n); }
		// Difference between two Iterators
		difference_type operator-(const reverse_iterator &that) const
					{ return that._data - this->_data; }
		// compound assignment operations += and -=
		reverse_iterator& operator-=(int n) { _data += n; return *this; }
		reverse_iterator& operator+=(int n) { _data -= n; return *this; }

	private:
		iterator_type _data;
	};
	
	// Comparison operators
	template<class Iter1, class Iter2>
	bool operator==(const reverse_iterator<Iter1> &it1, const reverse_iterator<Iter2> &it2)
					{ return it1.base() == it2.base(); }
	template<class Iter1, class Iter2>
	bool operator!=(const reverse_iterator<Iter1> &it1, const reverse_iterator<Iter2> &it2)
					{ return it1.base() != it2.base(); }
	template<class Iter1, class Iter2>
	bool operator<=(const reverse_iterator<Iter1> &it1, const reverse_iterator<Iter2> &it2)
					{ return it1.base() >= it2.base(); }
	template<class Iter1, class Iter2>
	bool operator>=(const reverse_iterator<Iter1> &it1, const reverse_iterator<Iter2> &it2)
					{ return it1.base() <= it2.base(); }
	template<class Iter1, class Iter2>
	bool operator< (const reverse_iterator<Iter1> &it1, const reverse_iterator<Iter2> &it2)
					{ return it1.base() >  it2.base(); }
	template<class Iter1, class Iter2>
	bool operator> (const reverse_iterator<Iter1> &it1, const reverse_iterator<Iter2> &it2)
					{ return it1.base() <  it2.base(); }

	// Add, substract operators, int +/- this
	template<class T>
	reverse_iterator<T> operator+(int n, const reverse_iterator<T> &itr) { return itr + n; }
	template<class T>
	reverse_iterator<T> operator-(int n, const reverse_iterator<T> &itr) { return itr - n; }
}
