// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 9/13/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include "utility/type_traits.hpp"
#include "utility/vector_iterator.hpp"
#include "utility/reverse_iterator.hpp"
#include "utility/algorithm.hpp"
#include <memory>
#include <stdexcept>
#include <algorithm>

namespace ft
{
	template<class T, class Alloc = std::allocator<T> >
	class vector
	{
	private:
		T		*_data;
		size_t	_size;
		size_t	_capacity;
		Alloc	_allocator;

	private:
		size_t	_calcCapacity(size_t newSize, size_t capacity = 1)
		{
			if (capacity * 2 > newSize)
				return capacity * 2;
			return newSize;
		}
		void	_move_data(T* dst, T* src, size_t len)
		{
			// std::memmove(dst, src, len * sizeof(T));
			if (dst == src)
				return;
			if (src < dst)
			{
				while (len--)
				{
					_allocator.construct(dst + len, src[len]);
					_allocator.destroy(src + len);
				}
			}
			else
			{
				for (size_t i = 0; i < len; ++i)
				{
					_allocator.construct(dst + i, src[i]);
					_allocator.destroy(src + i);
				}
			}
		}
		template<class InputIterator>
		void _insert_range_helper(const size_t position, InputIterator first, InputIterator last)
		{
			const size_t	n_element = std::distance(first, last);
			size_t			pos = position, newCap ;
			T*				newData;
			
			if (_size + n_element > _capacity)
			{
				newCap = _calcCapacity(_size + n_element, _capacity);
				newData = _allocator.allocate(newCap);
				try
				{
					for ( ; first != last; ++first, ++pos)
						_allocator.construct(newData + pos, *first);
				}
				catch (...)
				{
					while (position != pos)
					{
						--pos;
						_allocator.destroy(newData + pos);
					}
					_allocator.deallocate(newData, newCap);
					throw ;
				}
				_move_data(newData, _data, position);
				_move_data(newData + pos, _data + position, _size - position);
				if (_data)
					_allocator.deallocate(_data, _capacity);
				_size += n_element;
				_capacity = newCap;
				_data = newData;
			}
			else
			{
				_move_data(_data + pos + n_element, _data + pos, _size - pos);
				try
				{
					for ( ; first != last; ++first, ++pos)
						_allocator.construct(_data + pos, *first);
				}
				catch (...)
				{
					_move_data(_data + pos, _data + position + n_element, _size - position);
					_size = _size + pos - position;
					throw ;
				}
				_size += n_element;
			}
		}

	public:
		typedef Alloc														allocator_type;
		typedef T															value_type;
		typedef T&															reference;
		typedef const T&													const_reference;
		typedef T*															pointer;
		typedef const T*													const_pointer;
		typedef vector_iterator<T*>											iterator;
		typedef vector_iterator<const T*>									const_iterator;
		typedef ft::reverse_iterator<iterator>								reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>						const_reverse_iterator;
		typedef typename	ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t														size_type;

	public:
		explicit vector (const allocator_type& alloc = allocator_type())
			: _data(nullptr), _size(0), _capacity(0), _allocator(alloc) {}

		vector(const vector &that)
			: _size(0)
		{
			_capacity = that._capacity;
			if (_capacity)
				_data = _allocator.allocate(_capacity);
			else
				_data = nullptr;
			for (; _size < that._size; ++_size)
				_allocator.construct(_data + _size, that[_size]);
		}

		explicit vector (size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type())
			: _data(nullptr), _size(0), _capacity(0), _allocator(alloc)
		{
			this->reserve(n);
			for (; _size < n; ++_size)
				_allocator.construct(_data + _size, val);
		}

		template <class InputIterator>
		
		vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type(),
				typename ft::enable_if<ft::is_integral<InputIterator>::value == false,
				InputIterator>::type = InputIterator())
				: _data(nullptr), _size(0), _capacity(0), _allocator(alloc)
		{
			size_type	n = 0;
			
			if (typeid(typename ft::iterator_traits<InputIterator>::iterator_category) == typeid(std::input_iterator_tag))
			{
				for (; first != last; ++first)
					this->push_back(*first);
				return;
			}
			for (InputIterator counter(first); counter != last; ++counter)
				++n;
			this->reserve(n);
			for (; _size < n; ++_size, ++first)
				_allocator.construct(_data + _size, *first);
		}

		~vector()
		{
			while (_size)
			{
				--_size;
				_allocator.destroy(_data + _size);
			}
			if (_data)
				_allocator.deallocate(_data, _capacity);
		}

		vector & operator=(const vector &that)
		{
			if (this == &that)
				return *this;
			// free old data
			this->clear();
			if (_data)
				_allocator.deallocate(_data, _capacity);
			// allocate for new data
			_capacity = that._capacity;
			if (_capacity)
				_data = _allocator.allocate(_capacity);
			else
				_data = nullptr;
			for (_size = 0; _size < that._size; ++_size)
				_allocator.construct(_data + _size, that[_size]);
			return *this;
		}
		// TODO: <Capacity>
		bool	empty() const { return !_size; }
		size_t	size() const { return _size; }
		size_t	capacity() const { return _capacity; }
		size_type max_size() const
		{ return _allocator.max_size() > PTRDIFF_MAX ? PTRDIFF_MAX : _allocator.max_size(); }
		void reserve (size_type n)
		{
			if (n > _capacity)
			{
				pointer new_data;
				
				new_data = _allocator.allocate(n);
				this->_move_data(new_data, _data, _size);
				if (_capacity)
					_allocator.deallocate(_data, _capacity);
				_data = new_data;
				_capacity = n;
			}
		}
		void resize (size_type n, value_type val = value_type())
		{
			// if n < size: reduce size (destroy)
			if (n < _size)
			{
				for (size_type i = n; i < _size; ++i)
					_allocator.destroy(_data + i);
			}
			// if n > size
			else if (n > _size)
			{
				if (n > _capacity)
					this->reserve(_calcCapacity(n, _capacity));
				for (; _size < n; ++_size)
					_allocator.construct(_data + _size, val);
			}
			_size = n;
		}
		
		allocator_type get_allocator() const { return _allocator;}
		// TODO: <Element access>
		reference operator[](size_type n) { return _data[n]; }
		const_reference operator[](size_type n) const { return _data[n]; }
		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("ft::vector out of range");
			return _data[n];
		}
		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("ft::vector out of range");
			return _data[n];
		}
		reference front() { return *_data; }
		const_reference front() const { return *_data; }
		reference back() { return _data[_size - 1]; }
		const_reference back() const { return _data[_size - 1]; }
		// TODO: <Iterators>
		iterator		begin()		const { return iterator(_data); }
		iterator		end()		const { return iterator(_data + _size); }
		// Reverse Iterators
		reverse_iterator		rbegin()	const { return reverse_iterator(this->end()); }
		reverse_iterator		rend()		const { return reverse_iterator(this->begin()); }
		// TODO: <Modifiers>
		void push_back(const_reference t)
		{
			if (_size == _capacity)
				this->reserve(_capacity ? _capacity * 2 : 1);
			_allocator.construct(_data + _size, t);
			++_size;
		}
		void pop_back()
		{
			--_size;
			_allocator.destroy(_data + _size);
		}
		void clear()
		{
			while (_size)
			{
				--_size;
				_allocator.destroy(_data + _size);
			}
		}
		void swap (vector& x)
		{
			size_type	size = x._size;
			size_type	capacity = x._capacity;
			pointer		data = x._data;
			
			x._size = _size;
			x._capacity = _capacity;
			x._data = _data;
			_size = size;
			_capacity = capacity;
			_data = data;
		}
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last,
					 typename ft::enable_if<ft::is_integral<InputIterator>::value == false,
					 InputIterator>::type = InputIterator())
		{
			size_type	new_size = 0;
			size_type	index = 0;
			
			if (typeid(typename ft::iterator_traits<InputIterator>::iterator_category) == typeid(std::input_iterator_tag))
			{
				for (; first != last; ++first)
					this->push_back(*first);
				return;
			}
			for (InputIterator counter = first; counter != last; ++counter)
				++new_size;
			this->reserve(new_size);
			if (_size <= new_size)
			{
				while (index < _size)
				{
					_data[index] = *first;
					++first;
					++index;
				}
				while (_size < new_size)
				{
					_allocator.construct(_data + index, *first);
					++first;
					++_size;
				}
			}
			else
			{
				while (index < new_size)
				{
					_data[index] = *first;
					++first;
					++index;
				}
				while (index < _size)
				{
					_allocator.destroy(_data + index);
					++index;
				}
			}
			_size = new_size;
		}
		void assign (size_type n, const value_type& val)
		{
			size_type	index = 0;

			this->reserve(n);
			if (_size <= n)
			{
				while (index < _size)
				{
					_data[index] = val;
					++index;
				}
				while (index < n)
				{
					_allocator.construct(_data + index, val);
					++index;
				}
			}
			else
			{
				while (index < n)
				{
					_data[index] = val;
					++index;
				}
				while (index < _size)
				{
					_allocator.destroy(_data + index);
					++index;
				}
			}
			_size = n;
		}
		iterator erase (iterator position)
		{
			size_type 	pos;

			pos = position - iterator(_data);
			--_size;
			for (; pos < _size; ++pos)
				_data[pos] = _data[pos + 1];
			_allocator.destroy(_data + pos);
			return (position);
		}
		iterator erase (iterator first, iterator last)
		{
			size_type 	pos_first, pos_last;
			
			pos_first = first - iterator(_data);
			pos_last = last - iterator(_data);
			for (; pos_last < _size; ++pos_first, ++pos_last)
				_data[pos_first] = _data[pos_last];
			while (pos_first < _size)
			{
				--_size;
				_allocator.destroy(_data + _size);
			}
			return first;
		}
		iterator insert (iterator position, const value_type& val)
		{
			size_type pos = position - iterator(_data);

			if (_size == _capacity)
				this->reserve(_capacity ? _capacity * 2 : 1);
			this->_move_data(_data + pos + 1, _data + pos, _size - pos);
			_allocator.construct(_data + pos, val);
			++_size;
			return (iterator(_data + pos));
		}
		void insert (iterator position, size_type n, const value_type& val)
		{
			size_type pos;

			if (n == 0)
				return;
			pos = position - iterator(_data);
			if (_size + n > _capacity)
				this->reserve(_calcCapacity(_size + n, _capacity));
			this->_move_data(_data + pos + n, _data + pos, _size - pos);
			_size += n;
			for (; n != 0; --n, ++pos)
				_allocator.construct(_data + pos, val);
		}
		template <class InputIterator>
		void insert (iterator position, InputIterator first, InputIterator last,
					 typename ft::enable_if<ft::is_integral<InputIterator>::value == false,
					 InputIterator>::type = InputIterator())
		{
			if (std::is_same<typename ft::iterator_traits<InputIterator>::iterator_category, std::input_iterator_tag>::value)
			{
				vector tmp;
				for ( ; first != last; ++first)
					tmp.push_back(*first);
				_insert_range_helper(position - begin(), tmp.begin(), tmp.end());
			}
			else
				_insert_range_helper(position - begin(), first, last);
		}
	};

	// TODO: relational operators
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return ft::equal(lhs.begin(), lhs.end(), rhs.begin());
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
				{ return !(lhs == rhs); }
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{ return ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()); }
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
				{ return !(rhs < lhs); }
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
				{ return rhs < lhs; }
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
				{ return !(lhs < rhs); }
	//<relational operators, ends here>
	template<class T, class Alloc>
	void swap (vector<T, Alloc> &v1, vector<T, Alloc> &v2)
				{ v1.swap(v2); }
}
