// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 2/12/23.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

namespace ft
{
	template<class T>
	struct BSTNode
	{
		T		*val;
		bool	color;
		BSTNode	*parent;
		BSTNode	*right;
		BSTNode	*left;
	};
}