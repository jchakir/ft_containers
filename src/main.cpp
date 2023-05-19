// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 9/3/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#include <iostream>
#include <exception>
#include <vector>
#include <stack>
#include <map>
#include <set>
#include "vector.hpp"
#include "stack.hpp"
#include "map.hpp"
#include "set.hpp"

#ifndef ns
	#define ns ft
#endif

void main_()
{
	ns::vector<int> v1;
	ns::vector<int> v2(13, 1337);
	ns::vector<int> v3(v2.begin(), v2.end());
	
	std::cout << "v1.size() = " << v1.size() << " ,  v1.cap() = " << v1.capacity() << '\n' ;
	std::cout << "v2.size() = " << v2.size() << " ,  v2.cap() = " << v2.capacity() << '\n' ;
	std::cout << "v3.size() = " << v3.size() << " ,  v3.cap() = " << v3.capacity() << '\n' ;
	
	std::cout << v2[9] << '\n';
	std::cout << v3[9] << '\n';
	
	v2.clear();
	for (int i = 0; i < 9; ++i)
		v2.push_back(i);
	
	std::cout << "v1.size() = " << v1.size() << " ,  v1.cap() = " << v1.capacity() << '\n' ;
	std::cout << "v2.size() = " << v2.size() << " ,  v2.cap() = " << v2.capacity() << '\n' ;
	std::cout << "v3.size() = " << v3.size() << " ,  v3.cap() = " << v3.capacity() << '\n' ;
	
	v1.assign(v2.begin(), v2.end());
	
	v2.insert(v2.begin() + 3, 37);
	
	std::cout << "v1.size() = " << v1.size() << " ,  v1.cap() = " << v1.capacity() << '\n' ;
	std::cout << "v2.size() = " << v2.size() << " ,  v2.cap() = " << v2.capacity() << '\n' ;
	std::cout << "v3.size() = " << v3.size() << " ,  v3.cap() = " << v3.capacity() << '\n' ;
	
	std::cout << v1[5] << '\n';
	std::cout << v2[5] << '\n';
	std::cout << v3[5] << '\n';
	
	ns::set<int> s ;
	s.insert(v2.begin(), v2.end());
	
	for (ns::set<int>::iterator b = s.begin(), e = s.end(); b != e; ++b)
		std::cout << *b << ' ' ;
	std::cout << "\nset.size() = " << s.size() << '\n';
	
	ns::map<int, int> m;
	
	for (int i = 0; i < 11; ++i)
		m.insert(ns::make_pair(i, i * i));
	
	for (ns::map<int, int>::iterator b = m.begin(), e = m.end(); b != e; ++b)
		std::cout << b->first << ' ' << b->second << '\n' ;
	std::cout << "\nmap.size() = " << m.size() << '\n';
}

int main()
{
	try { main_(); }
	catch (const std::exception &e)
	{std::cerr << "int main() Exception Error: " << e.what() << std::endl;}
	catch (const char *s)
	{std::cerr << "int main() Exception Error: " << s << std::endl;}
	catch (...)
	{std::cerr << "int main() unknown Exception Error\n" ;}

//	std::cout << "\n-----------------------------------------------------\n";
//	system("leaks program");
	return 0;
}
