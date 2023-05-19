// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 2/12/23.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include <memory>
#include <algorithm>
#include "utility/RedBlackTree.hpp"
#include "utility/reverse_iterator.hpp"
#include "utility/algorithm.hpp"
#include "utility/pair.hpp"

namespace ft
{
	
	template<class T, class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
	
	private:
		typedef RedBlackTree<T, Compare, Alloc>	Tree;
	
	public:
		typedef 			T											key_type;
		typedef				T											value_type;
		typedef				Compare										key_compare;
		typedef				Compare										value_compare;
		typedef				Alloc										allocator_type;
		typedef	typename	allocator_type::reference					reference;
		typedef	typename	allocator_type::const_reference				const_reference;
		typedef	typename	allocator_type::pointer						pointer;
		typedef	typename	allocator_type::const_pointer				const_pointer;
		typedef typename	Tree::iterator								iterator;
		typedef typename	Tree::const_iterator						const_iterator;
		typedef				reverse_iterator<iterator> 					reverse_iterator;
		typedef				ft::reverse_iterator<const_iterator> 		const_reverse_iterator;
		typedef typename	iterator_traits<iterator>::difference_type	difference_type;
		typedef				size_t										size_type;
	
	private:
		Compare	_comp;
		Alloc	_alloc;
		Tree	_tree;
	
	public:
		explicit set(const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type())
				: _comp(comp), _alloc(alloc), _tree(comp, alloc) {}
		template <class InputIterator>
		set(InputIterator first, InputIterator last, const key_compare& comp = key_compare(),
		const allocator_type& alloc = allocator_type())
			: _comp(comp), _alloc(alloc), _tree(comp, alloc)
					{ this->insert(first, last); }
		set(const set& x) : _comp(x._comp), _alloc(x._alloc), _tree(x._tree) {}
		~set() {};
		set& operator= (const set& x) { _tree = x._tree; return *this; }
		// TODO:  Iterators
		iterator begin() { return _tree.begin(); }
		const_iterator begin() const { return _tree.begin(); }
		iterator end() { return _tree.end(); }
		const_iterator end() const { return _tree.end(); }
		reverse_iterator rbegin() { return reverse_iterator(end()); }
		const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
		reverse_iterator rend() { return reverse_iterator(begin()); }
		const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }
		//TODO:  Capacity
		bool empty() const { return (_tree.size()) ? 0 : 1; }
		size_type size() const { return _tree.size(); }
		size_type max_size() const { return _tree.max_size(); }
		// TODO:  Modifiers
		pair<iterator,bool> insert (const value_type& val)
		{
			size_t					s = size();
			pair<iterator,bool>		res(_tree.insert(val), s != size());
			
			return res;
		}
		iterator insert (iterator p, const value_type& v)
		{
			if (p != end() && !_comp(v, *p) && !_comp(*p, v))
				return p;
			return _tree.insert(v);
		}
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			for (; first != last; ++first)
				_tree.insert(*first);
		}
		void erase (iterator position) { _tree.remove(*position); }
		size_type erase (const key_type& k)
		{
			size_t s = size();
			
			_tree.remove(k);
			return s - size();
		}
		void erase (iterator first, iterator last)
		{
			
			typename Alloc::template rebind<pointer>::other	Alloc_pointer;
			size_t											size;
			size_t											index;
			pointer										*	holder;
			
			size = std::distance(first, last);
			holder = Alloc_pointer.allocate(size);
			
			for (index = 0; first != last; ++first, ++index)
				holder[index] = first.operator->();
			
			for (index = 0; index < size; ++index)
				_tree.remove(*holder[index]);
			
			Alloc_pointer.deallocate(holder, size);
		}
		void clear() { _tree.clear(); }
		void swap (set& x) { _tree.swap(x._tree); }
		// TODO:  Observers
		key_compare key_comp() const { return _comp; }
		value_compare value_comp() const { return value_compare(_comp); }
		// TODO:  Operations
		iterator find (const key_type& k)
		{ return _tree.find(k); }
		const_iterator find (const key_type& k) const
		{ return _tree.find(k); }
		size_type count (const key_type& k) const
		{ return find(k) != end() ? 1 : 0; }
		iterator lower_bound (const key_type& k)
		{ return _tree.lower_bound(k); }
		const_iterator lower_bound (const key_type& k) const
		{ return _tree.lower_bound(k); }
		iterator upper_bound (const key_type& k)
		{ return _tree.upper_bound(k); }
		const_iterator upper_bound (const key_type& k) const
		{ return _tree.upper_bound(k); }
		pair<iterator,iterator> equal_range (const key_type& k)
		{ pair<iterator,iterator> res(lower_bound(k), upper_bound(k)); return res; }
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{ pair<const_iterator,const_iterator> res(lower_bound(k), upper_bound(k)); return res; }
		// 	TODO:  Allocator
		allocator_type get_allocator() const { return _alloc; }
	};
	// TODO: non-member functions overloads
	template <class T, class Compare, class Alloc>
	void swap (set<T,Compare,Alloc>& x, set<T,Compare,Alloc>& y)
				{ x.swap(y); }
	
	template <class T, class Compare, class Alloc> bool operator ==
			(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Compare, class Alloc> bool operator !=
			(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{ return !(lhs == rhs); }
	template <class T, class Compare, class Alloc> bool operator <
			(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	template <class T, class Compare, class Alloc>  bool operator <=
			(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{ return !(rhs < lhs); }
	template <class T, class Compare, class Alloc>  bool operator >
			(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{ return rhs < lhs; }
	template <class T, class Compare, class Alloc>  bool operator >=
			(const set<T,Compare,Alloc>& lhs, const set<T,Compare,Alloc>& rhs)
	{ return !(lhs < rhs); }

}
