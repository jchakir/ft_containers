// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 12/12/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include <type_traits>

namespace ft {
	
	template <class T, T v>
	struct integral_constant
	{
		typedef T						value_type;
		typedef integral_constant<T,v>	type;
		static const	T value = v;
		operator T() { return value; }
	};
	
	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;
	
	template<typename T> struct is_integral: public false_type {};
	template<typename T> struct is_integral<const T>: public is_integral<T> {};
	template<typename T> struct is_integral<volatile const T>: public is_integral<T> {};
	template<typename T> struct is_integral<volatile T>: public is_integral<T> {};

	template<> struct is_integral<bool>: public true_type {};
	template<> struct is_integral<char>: public true_type {};
	template<> struct is_integral<char16_t>: public true_type {};
	template<> struct is_integral<char32_t>: public true_type {};
	template<> struct is_integral<wchar_t>: public true_type {};
	template<> struct is_integral<signed char>: public true_type {};
	template<> struct is_integral<short int>: public true_type {};
	template<> struct is_integral<int>: public true_type {};
	template<> struct is_integral<long int>: public true_type {};
	template<> struct is_integral<long long int>: public true_type {};
	template<> struct is_integral<unsigned char>: public true_type {};
	template<> struct is_integral<unsigned short int>: public true_type {};
	template<> struct is_integral<unsigned int>: public true_type {};
	template<> struct is_integral<unsigned long int>: public true_type {};
	template<> struct is_integral<unsigned long long int>: public true_type {};

	template<bool, class T = void> struct enable_if {};
	template<class T> struct enable_if<true, T> { typedef T type; };

}
