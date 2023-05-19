// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 12/26/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include "vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class stack
	{
	protected:
		Container c;

	public:
		typedef				T								value_type;
		typedef				Container						container_type;
		typedef typename	container_type::reference 		reference;
		typedef typename	container_type::const_reference const_reference;
		typedef				size_t							size_type;

	public:
		explicit stack (const container_type& _c = container_type()) : c(_c) {}
		bool empty() const { return c.empty(); }
		size_type size() const { return c.size(); }
		value_type& top() { return c.back(); }
		const value_type& top() const { return c.back(); }
		void pop() { c.pop_back(); }
		void push (const value_type& val) { c.push_back(val); }

		template <class U, class _Container> friend bool
		operator==(const stack<U,_Container>& lhs, const stack<U,_Container>& rhs)
					{ return  lhs.c == rhs.c; }
		template <class U, class _Container> friend bool
		operator!=(const stack<U,_Container>& lhs, const stack<U,_Container>& rhs)
					{ return  lhs.c != rhs.c; }
		template <class U, class _Container> friend bool
		operator< (const stack<U,_Container>& lhs, const stack<U,_Container>& rhs)
					{ return  lhs.c <  rhs.c; }
		template <class U, class _Container> friend bool
		operator<=(const stack<U,_Container>& lhs, const stack<U,_Container>& rhs)
					{ return  lhs.c <= rhs.c; }
		template <class U, class _Container> friend bool
		operator> (const stack<U,_Container>& lhs, const stack<U,_Container>& rhs)
					{ return  lhs.c >  rhs.c; }
		template <class U, class _Container> friend bool
		operator>=(const stack<U,_Container>& lhs, const stack<U,_Container>& rhs)
					{ return  lhs.c >= rhs.c; }
	};
}
