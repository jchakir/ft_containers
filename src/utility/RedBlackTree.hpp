// *********************************************************************
// Created by Jaouad Chakir (jchakir@student.1337.ma) on 12/29/22.
// Copyright (c) 1337.ma(@1337FIL) . All rights reserved.
// *********************************************************************

#pragma once

#include "BSTNode.hpp"
#include "BSTIterator.hpp"
#include "iterator_traits.hpp"

namespace ft
{
	template <class T, class Compare, class Alloc>
	class RedBlackTree
	{
	private:
		enum 				{ RED = 0, BLACK = 1 };
		typedef				T									type;
		typedef				ft::BSTNode<type>					Node;
		typedef typename	Alloc::template rebind<Node>::other	Allocator;

	private:
		Node		*_nil;
		Node		*_root;
		size_t		_size;
		Compare		_comp;
		Allocator	_alloc;
		Alloc		_type_alloc;

	private:
		Node *_new_node(type* val = nullptr, Node *parent = nullptr, bool color = BLACK)
		{
			Node *node = _alloc.allocate(1);
			node->val = val;
			node->color = color;
			node->parent = parent;
			node->right = nullptr;
			node->left = nullptr;
			return node;
		}
		type* _new_value_type(const type &value)
		{
			type* val = _type_alloc.allocate(1);
			_type_alloc.construct(val, value);
			return val;
		}
		void _leftRotate(Node* node)
		{
			Node *parent = node->parent;
			Node *right = node->right;

			node->right = right->left;
			node->right->parent = node;
			right->left = node;
			node->parent = right;
			right->parent = parent;
			if (parent == nullptr)
				_root = right;
			else if (parent->left == node)
				parent->left = right;
			else
				parent->right = right;
		}
		void _rightRotate(Node* node)
		{
			Node *parent = node->parent;
			Node *left = node->left;

			node->left = node->left->right;
			node->left->parent = node;
			left->right = node;
			node->parent = left;
			left->parent = parent;
			if (parent == nullptr)
				_root = left;
			else if (parent->left == node)
				parent->left = left;
			else
				parent->right = left;
		}
		Node *_get_successor(Node *node) const
		{
			node = node->right;
			if (node == _nil)
				return nullptr;
			while (node->left != _nil)
				node = node->left;
			return node;
		}
		Node *_get_predecessor(Node *node) const
		{
			node = node->left;
			if (node == _nil)
				return nullptr;
			while (node->right != _nil)
				node = node->right;
			return node;
		}
		/*
		 this methode deallocate a leaf node and it's left child nil node
		 node must be a leaf node
		 */
		void _deallocate_leaf_node(Node *node)
		{
			if (node == nullptr)
				return;
			if (node == _root)
			{
				_alloc.deallocate(_root, 1);
				_root = nullptr;
				return;
			}
			if (node->parent->right == node)
				node->parent->right = _nil ;
			else
				node->parent->left = _nil ;
			_alloc.deallocate(node, 1);
		}
		void _deallocate_value_type(type* val)
		{
			if (val == nullptr)
				return;
			_type_alloc.destroy(val);
			_type_alloc.deallocate(val, 1);
		}
		/*
		methode recursively call it's self
		according successor/predecessor
		until node in leaf (have no children)
		 */
		Node *_remove_replace(Node *node)
		{
			Node		*replace;

			if ((replace = _get_successor(node)))
				node->val = replace->val;
			else if ((replace = _get_predecessor(node)))
				node->val = replace->val;
			else
				return node;
			return _remove_replace(replace);
		}
		void _insert_base_fix_properties(Node *node)
		{
			Node 	*parent_sibling;

			while (node->parent && node->parent->color == RED)
			{
				if (node->parent == node->parent->parent->left)
				{
					parent_sibling = node->parent->parent->right;
					if (parent_sibling->color == RED)
					{
						node->parent->color = BLACK;
						parent_sibling->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->right)
						{
							node = node->parent;
							_leftRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_rightRotate(node->parent->parent);
					}
					
				}
				else
				{
					parent_sibling = node->parent->parent->left;
					if (parent_sibling->color == RED)
					{
						node->parent->color = BLACK;
						parent_sibling->color = BLACK;
						node->parent->parent->color = RED;
						node = node->parent->parent;
					}
					else
					{
						if (node == node->parent->left)
						{
							node = node->parent;
							_rightRotate(node);
						}
						node->parent->color = BLACK;
						node->parent->parent->color = RED;
						_leftRotate(node->parent->parent);
					}
				}
			}
			_root->color = BLACK;
		}
		void _remove_fix_properties(Node *d_black)
		{
			Node	*sibling;
			
			while(d_black != _root && d_black->color == BLACK)
			{
				if (d_black->parent->left == d_black)
				{
					sibling = d_black->parent->right;
					if (sibling->color == RED)
					{
						sibling->color = BLACK;
						d_black->parent->color = RED;
						_leftRotate(d_black->parent);
						sibling = d_black->parent->right;
					}
					if (sibling->right->color == BLACK && sibling->left->color == BLACK)
					{
						sibling->color = RED;
						d_black = d_black->parent;
					}
					else
					{
						if (sibling->right->color == BLACK)
						{
							sibling->left->color = RED;
							sibling->color = RED;
							_rightRotate(sibling);
							sibling = d_black->parent->right;
						}
						sibling->color = d_black->parent->color;
						d_black->parent->color = BLACK;
						sibling->right->color = BLACK;
						_leftRotate(d_black->parent);
						d_black = _root;
					}
				}
				else
				{
					sibling = d_black->parent->left;
					if (sibling->color == RED)
					{
						sibling->color = BLACK;
						d_black->parent->color = RED;
						_rightRotate(d_black->parent);
						sibling = d_black->parent->left;
					}
					if (sibling->right->color == BLACK && sibling->left->color == BLACK)
					{
						sibling->color = RED;
						d_black = d_black->parent;
					}
					else
					{
						if (sibling->left->color == BLACK)
						{
							sibling->right->color = BLACK;
							sibling->color = RED;
							_leftRotate(sibling);
							sibling = d_black->parent->left;
						}
						sibling->color = d_black->parent->color;
						d_black->parent->color = BLACK;
						sibling->left->color = BLACK;
						_rightRotate(d_black->parent);
						d_black = _root;
					}
				}
			}
			d_black->color = BLACK;
		}
		Node *_search(const type &val) const
		{
			Node *current = _root;

			if (_root == nullptr)
				return nullptr;
			while (current != _nil)
			{
				if (_comp(val, *current->val))
					current = current->left;
				else if (_comp(*current->val, val))
					current = current->right;
				else
					return current;
			}
			return nullptr;
		}
	
	public:
		typedef		ft::BSTIterator<type*>			iterator;
		typedef		ft::BSTIterator<const type*>	const_iterator;

	public:
		explicit RedBlackTree(const Compare& comp, const Alloc &alloc)
				: _nil(_new_node()), _root(nullptr), _size(0),
				_comp(comp), _alloc(alloc), _type_alloc(alloc) {}
		RedBlackTree(const RedBlackTree &that) : _nil(_new_node()), _root(nullptr), _size(0),
					 _comp(that._comp), _alloc(that._alloc), _type_alloc(that._type_alloc)
										{ *this = that; }
		RedBlackTree& operator=(const RedBlackTree &that)
		{
			const_iterator begin = that.begin(), end = that.end();

			clear();

			for (; begin != end; ++begin)
				insert(*begin);
			return *this;
		}
		~RedBlackTree() { clear(); _alloc.deallocate(_nil, 1); }
		iterator  end() const { return iterator(_nil, _nil); }
		iterator  begin() const
		{
			Node *current = _root;

			if (_root == nullptr)
				return iterator(_nil, _nil);
			while (current->left != _nil)
				current = current->left;
			return iterator(current, _nil);
		}
		iterator insert(const type& value)
		{
			enum	{ RIGHT = 0, LEFT = 1 };
			bool	right_left;
			Node	*node = _root, *parent;
			
			// if is the first Node, create _root and _nil, then exit.
			if (_root == nullptr)
			{
				_root = _new_node(_new_value_type(value));
				_root->right = _nil;
				_root->left = _nil;
				++_size;
				_nil->parent = _root;
				return iterator(_root, _nil) ;
			}
			// if not the first Node, iterate to the leaf node.
			while (node != _nil)
			{
				parent = node;
				if (_comp(value, *node->val))
				{
					right_left = LEFT;
					node = node->left;
				}
				else if (_comp(*node->val, value))
				{
					right_left = RIGHT;
					node = node->right;
				}
				else
					return iterator(node, _nil);
			}
			// create new node with color RED.
			node = _new_node(_new_value_type(value), parent, RED);
			right_left == RIGHT ? parent->right = node : parent->left = node ;
			node->right = _nil ;
			node->left = _nil ;
			// check if this tree is Red-Black Tree, with rotate and recolor if needed.
			_insert_base_fix_properties(node);
			_nil->parent = _root;
			++_size;
			return iterator(node,_nil) ;
		}
		void remove(const type& val)
		{
			Node *node = _search(val);

			if (node == nullptr)
				return ;
			_deallocate_value_type(node->val);
			node = _remove_replace(node);
			if (node->color == BLACK && node != _root)
				_remove_fix_properties(node);
			_deallocate_leaf_node(node);
			_nil->parent = _root;
			--_size;
		}
		iterator find(const type& val) const
		{
			Node *found = _search(val);

			if (found)
				return iterator(found, _nil);
			else
				return iterator(_nil, _nil);
		}
		iterator lower_bound(const type& val) const
		{
			Node *current = _root, *lower = _nil;
			
			if (_root == nullptr)
				return iterator(_nil, _nil);
			while (current != _nil)
			{
				if (_comp(val, *current->val))
				{
					lower = current;
					current = current->left;
				}
				else if (_comp(*current->val, val))
					current = current->right;
				else
					return iterator(current, _nil);
			}
			return iterator(lower, _nil);
		}
		iterator upper_bound(const type& val) const
		{
			Node *current = _root, *upper = _nil;
			
			if (_root == nullptr)
				return iterator(_nil, _nil);
			while (current != _nil)
			{
				if (_comp(val, *current->val))
				{
					upper = current;
					current = current->left;
				}
				else
					current = current->right;
			}
			return iterator(upper, _nil);
		}
		void clear()
		{
			Node	*node;

			while (_root)
			{
				_deallocate_value_type(_root->val);
				node = _remove_replace(_root);
				_deallocate_leaf_node(node);
			}
			_nil->parent = nullptr;
			_size = 0;
		}
		void swap(RedBlackTree& that)
		{
			Node	*root = _root, *nil = _nil;
			size_t	size = _size;

			_root = that._root;
			_nil = that._nil;
			_size = that._size;
			that._root = root;
			that._nil = nil;
			that._size = size;
		}
		size_t size() const { return _size; }
		size_t max_size() const
		{
			size_t type_size, node_size;

			type_size = _type_alloc.max_size() ;
			node_size = _alloc.max_size() ;
			if (type_size > PTRDIFF_MAX)
				type_size = PTRDIFF_MAX;
			if (node_size > PTRDIFF_MAX)
				node_size = PTRDIFF_MAX;

			if (type_size + node_size > PTRDIFF_MAX)
				return PTRDIFF_MAX;
			else
				return type_size + node_size ;
		}
	};
}
