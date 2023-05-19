// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 2/12/23.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include "iterator_traits.hpp"
#include "BSTNode.hpp"

namespace ft
{
	template<class T>
	class BSTIterator
	{
	public:
		typedef 			T										iterator_type;
		typedef typename	ft::iterator_traits<T>::value_type		value_type;
		typedef typename	ft::iterator_traits<T>::difference_type	difference_type;
		typedef typename	ft::iterator_traits<T>::pointer			pointer;
		typedef typename	ft::iterator_traits<T>::reference		reference;
		typedef				std::bidirectional_iterator_tag			iterator_category;
		
	private:
		typedef	BSTNode<value_type>	Node;
		Node	*_current, *_nil;
	
	public:
		BSTIterator() : _current(nullptr), _nil(nullptr) {}
		BSTIterator(Node *current, Node *nil) : _current(current), _nil(nil) {}
		template<class T2>
		BSTIterator(const BSTIterator<T2> &that) { *this = that; }
		template<class T2>
		BSTIterator & operator=(const BSTIterator<T2> &that)
		{ swap_from_to(that, *this); return *this; }
		BSTIterator & operator++()
		{
			if (_current == _nil)
			{
				_current = _nil = nullptr;
				return *this;
			}
			else if (_current->right != _nil)
			{
				_current = _current->right;
				while (_current->left != _nil)
					_current = _current->left;
			}
			else
			{
				while (_current->parent && _current->parent->right == _current)
					_current = _current->parent;
				if (_current->parent == nullptr)
					_current = _nil;
				else
					_current = _current->parent;
			}
			return *this;
		}
		BSTIterator & operator--()
		{
			if (_current == _nil)
			{
				if (_nil->parent == nullptr)
					return *this;
				_current = _nil->parent;
				while (_current->right != _nil)
					_current = _current->right;
			}
			else if (_current->left != _nil)
			{
				_current = _current->left;
				while (_current->right != _nil)
					_current = _current->right;
			}
			else
			{
				while (_current->parent && _current->parent->left == _current)
					_current = _current->parent;
				if (_current->parent == nullptr)
					_current = _nil;
				else
					_current = _current->parent;
			}
			return *this;
		}
		BSTIterator operator++(int)
		{ BSTIterator it = *this; ++(*this); return it; }
		BSTIterator operator--(int)
		{ BSTIterator it = *this; --(*this); return it; }
		template<class T1, class T2> friend bool operator ==
		(const BSTIterator<T1> &it1, const BSTIterator<T2> &it2)
		{ return it1._current == it2._current; }
		template<class T1, class T2> friend bool operator !=
		(const BSTIterator<T1> &it1, const BSTIterator<T2> &it2)
		{ return it1._current != it2._current; }
		reference	operator*() const { return *_current->val; }
		pointer		operator->() const { return _current->val; }
		// extra methode to fix same problems
		template<class T1, class T2>
		friend void swap_from_to(const BSTIterator<T1> &from, BSTIterator<T2> &to)
		{ to._current = from._current; to._nil = from._nil; }
	};
}
