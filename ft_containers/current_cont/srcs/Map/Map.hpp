#ifndef MAP_HPP
# define MAP_HPP

# include "../Utils/Utils.hpp"
# include "MapIterator.hpp"

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc = std::allocator<pair<const Key,T> > >
	class	map
	{
		public:
			typedef Key											key_type;
			typedef T											mapped_type;
			typedef pair<const key_type, mapped_type>			value_type;
			typedef Compare										key_compare;
			typedef	Alloc										allocator_type;
			typedef	typename allocator_type::reference			reference;
			typedef typename allocator_type::const_reference	const_reference;
			typedef typename allocator_type::pointer			pointer;
			typedef typename allocator_type::const_pointer		const_pointer;
			typedef ptrdiff_t									difference_type;
			typedef size_t										size_type;
			typedef ft::node<value_type>						node_type;
			typedef node_type*									node_ptr;
		
			typedef ft::map_iterator<value_type, node_type >		iterator;
			typedef ft::map_iterator<const value_type, node_type >	const_iterator;
			typedef ft::reverse_iterator<iterator>					reverse_iterator;
			typedef ft::reverse_iterator<const_iterator>			const_reverse_iterator;

			class value_compare
			{
				friend class map;
				public:
					Compare comp;
					value_compare (Compare c) : comp(c) {}
				public:
					typedef bool	result_type;
					typedef			value_type first_argument_type;
					typedef			value_type second_argument_type;
					bool			operator()(const value_type& x, const value_type& y) const { return comp(x.first, y.first); };
			};

			/**********************/
			/**	MEMBER FUNCTIONS **/
			/**********************/

			explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
			: _pairAlloc(alloc), _comp(comp), _size(0), _root(NULL), _ghost(NULL), _lastElem(NULL)
			{
				return ;
			}

			template <class InputIterator>
			map(InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type()): _pairAlloc(alloc), _comp(comp), _size(0), _root(NULL), _ghost(NULL), _lastElem(NULL)
			{
				insert(first, last);

				return ;
			};

			map(const map& x): _size(0), _root(NULL), _ghost(NULL), _lastElem(NULL)
			{
				*this = x;
				return;
			};

			map& operator=(const map& x)
			{
				clear();
				this->_comp = x._comp;
				this->_nodeAlloc = x._nodeAlloc;
				this->_pairAlloc = x._pairAlloc;
				insert(x.begin(), x.end());
				
				return *this;
			};

			~map()
			{
				clear();
				if (_root)
					_nodeAlloc.deallocate(_root, _size);
				if (_ghost)
					_nodeAlloc.deallocate(_ghost, 1);

				return ;
			};
			
			/*
			**	Iterators
			*/
			iterator begin()
			{
				return iterator(minValueNode(_root));
			}

			const_iterator begin() const
			{
				return const_iterator(minValueNode(_root));
			}

			iterator end()
			{
				if (!_root || !size())
					return iterator(_lastElem);
				return iterator(_lastElem->right);
			}

			const_iterator end() const
			{
				if (!_root || !size())
					return const_iterator(_lastElem);
				return const_iterator(_lastElem->right);
			}

			reverse_iterator rbegin()
			{ 
				return reverse_iterator(_ghost); 
			}

			const_reverse_iterator rbegin() const
			{
				return const_reverse_iterator(end()); 
			}

			reverse_iterator rend()
			{
				return reverse_iterator(begin()); 
			}

			const_reverse_iterator rend() const
			{
				return const_reverse_iterator(begin());
			}

			/*
			**	Capacity
			*/		
			size_type size() const
			{
				return this->_size;
			}

			size_type max_size() const
			{
				return _nodeAlloc.max_size();
			}

			bool empty() const
			{
				return (!(_size) ? true : false);
			}

			/*
			**	Element access
			*/
			mapped_type& operator[](const key_type& k)
			{
				return (*((this->insert(value_type(k, mapped_type()))).first)).second;
			}

			/*
			**	Modifiers
			*/
			pair<iterator,bool> insert(const value_type& val)
			{
				ft::pair<iterator, bool>	ret;

				if (count(val.first))
					ret.second = false;
				else
				{
					_root = _insert(_root, val);
					ret.second = true;
				}
				ret.first = find(val.first);

				return ret;
			}

			iterator insert(iterator position, const value_type& val)
			{
				(void)position;
				return insert(val).first;
			}

			template <class InputIterator>
			void insert(InputIterator first, InputIterator last)
			{
				while (first != last)
					insert(*first++);
			}
			
			void erase(iterator position)
			{
				if (!_root)
					return ;
				--_size;
				_root = _deleteNode(_root, value_type(position->first, position->second));
				return ;
			}

			size_type erase(const key_type& k)
			{
				iterator pos = find(k);
				if (!count(k) || !_root)
					return 0;
				--_size;
				_root = _deleteNode(_root, value_type(k, find(k)->second));
				return 1;
			}

			void erase(iterator first, iterator last)
			{
				iterator tmp;

				while (first != last)
				{
					if (_size == 0)
						break;
					_size--;
					tmp = ++first;
					--first;
					_root = _deleteNode(_root, value_type(first->first, first->second));
					first = tmp;
				}
			}

			void swap(map& x)
			{
				map<Key, T, Compare, Alloc>	tmp;

				tmp._comp = this->_comp;
				tmp._nodeAlloc = this->_nodeAlloc;
				tmp._pairAlloc = this->_pairAlloc;
				tmp._root = this->_root;
				tmp._ghost = this->_ghost;
				tmp._lastElem = this->_lastElem;
				tmp._size = this->_size;

				this->_comp = x._comp;
				this->_nodeAlloc = x._nodeAlloc;
				this->_pairAlloc = x._pairAlloc;
				this->_root = x._root;
				this->_ghost = x._ghost;
				this->_lastElem = x._lastElem;
				this->_size = x._size;

				x._comp = tmp._comp;
				x._nodeAlloc = tmp._nodeAlloc;
				x._pairAlloc = tmp._pairAlloc;
				x._root = tmp._root;
				x._ghost = tmp._ghost;
				x._lastElem = tmp._lastElem;
				x._size = tmp._size;
			}

			void clear()
			{
				for (size_type i = 0; i < _size; i++)
					_pairAlloc.destroy(&_root->tab);
				_size = 0;
				_root = NULL;
				_ghost = NULL;
				_lastElem = NULL;

				return ;
			}


			/*
			**	Observers
			*/
			key_compare		key_comp() const
			{
				return key_compare();
			}
			
			value_compare	value_comp() const
			{
				return value_compare(key_compare());
			}

			/*
			**	Operations
			*/
			iterator		find(const key_type& k)
			{
				iterator	it = begin();

				while (it != end())
				{
					if (!key_comp()(k, it->first) && !key_comp()(it->first, k))
						break ;
					if (it._node == _lastElem)
						return end();
					++it;
				}
				return it;
			}

			const_iterator	find(const key_type& k) const
			{
				const_iterator	it = begin(); const_iterator	ite = end();

				while (it != ite)
				{
					if (!key_comp()(k, it->first) && !key_comp()(it->first, k))
						break ;
					if (it._node == _lastElem)
						return ++ite;
					++it;
				}
				return it;
			}

			size_type		count(const key_type& k) const
			{
				if (!_root)
					return 0;
				const_iterator	it = begin(); const_iterator	ite = end();
				if (!key_comp()(k, it->first) && !key_comp()(it->first, k))
					return 1;
				while (it != ite)
				{
					if (!key_comp()(k, it->first) && !key_comp()(it->first, k))
						return 1;
					++it;
				}
				return 0;
			}

			iterator		lower_bound(const key_type& k)
			{
				iterator it = begin(), ite = end();
				while (it != ite)
				{
					if (!_comp(it->first, k))
						break;
					++it;
				}
				return it;
			}

			const_iterator	lower_bound(const key_type& k) const
			{
				const_iterator it = begin(), ite = end();
				while (it != ite)
				{
					if (!_comp(it->first, k))
						break;
					++it;
				}
				return it;
			}

			iterator		upper_bound(const key_type& k)
			{
				iterator it = begin(), ite = end();
				while (it != ite)
				{
					if (_comp(k, it->first))
						break;
					++it;
				}
				return it;
			}

			const_iterator	upper_bound(const key_type& k) const
			{
				const_iterator it = begin(), ite = end();
				while (it != ite)
				{
					if (_comp(k, it->first))
						break;
					++it;
				}
				return it;
			}


			pair<iterator,iterator>             equal_range(const key_type& k)
			{
				ft::pair<iterator, iterator>	ret; 
				ret.first = lower_bound(k), ret.second = upper_bound(k);
				
				return ret;
			}

			pair<const_iterator,const_iterator>	equal_range(const key_type& k) const
			{
				ft::pair<const_iterator, const_iterator>	ret;
				ret.first = lower_bound(k), ret.second = upper_bound(k);

				return ret;
			}

			/*
			**	Allocator
			*/
			allocator_type get_allocator() const
			{
				return this->_pairAlloc;
			}

		private:
			allocator_type							_pairAlloc;
			std::allocator<ft::node<value_type> >	_nodeAlloc;
			key_compare								_comp;
			size_type								_size;
			node_ptr								_root;
			node_ptr								_ghost;
			node_ptr								_lastElem;
			
			node_ptr								_insert(node_ptr node, value_type val)
			{
				if (!_root || !node || node == _ghost)
				{
					node = _newNode(val);
					if (!_root)
						_root = node;
					else if (node == _ghost)
						_lastElem = node;
					_size++;
				}
				else if (key_comp()(val.first, node->tab.first))
				{
					node->left = _insert(node->left, val);
					node->left->parent = node;
				}
				else
				{
					node->right = _insert(node->right, val);
					node->right->parent = node;
				}
				if (!_ghost || !key_comp()(val.first, _lastElem->tab.first))
				{	
					if (_ghost)
						!key_comp()(node->tab.first, _lastElem->tab.first) ? _setGhost(true) : _setGhost(false);
					else
						_setGhost(true);
				}
				return node;
			}

			node_ptr								_newNode(value_type& val)
			{
				node_ptr tmp = _nodeAlloc.allocate(1);
				_pairAlloc.construct(&tmp->tab, val);

				tmp->left = NULL;
				tmp->right = NULL;
				tmp->parent = NULL;

				return tmp;
			}

			node_ptr								_deleteNode(node_ptr root, value_type val);
			
			void									_setGhost(bool add)
			{
				if (!_ghost)
					_ghost = _nodeAlloc.allocate(1);
				if (add)
				{
					_lastElem = maxValueNode(_root);
					_lastElem->right = _ghost;
				}
				if (size() == 0)
					_lastElem = NULL;
				_ghost->right = NULL;
				_ghost->left = NULL;
				_ghost->parent = _lastElem;
			}
	};

	template<class Key, class T, class Compare, class Alloc>
	typename map<Key, T, Compare, Alloc>::node_ptr	map<Key, T, Compare, Alloc>::_deleteNode(node_ptr node, value_type val)
	{
		if (!_size)
			_lastElem = _ghost;
		if (!node || node == _ghost)
			return node;
		else if (key_comp()(val.first, node->tab.first))
			node->left = _deleteNode(node->left, val);
		else if ((key_comp()(node->tab.first, val.first)))
			node->right = _deleteNode(node->right, val);
		else
		{
			if (!node->left && !node->right)
			{
				_pairAlloc.destroy(&node->tab);
				return NULL;
			}
			else if (!node->left)
			{
				node_ptr tmp = node->right;
				tmp->parent = node->parent;
				_pairAlloc.destroy(&node->tab);
				return tmp;
			}
			else if (!node->right)
			{
				node_ptr tmp = node->left;
				tmp->parent = node->parent;
				_pairAlloc.destroy(&node->tab);
				return tmp;
			}
			node_ptr tmp = minValueNode(node->right);
			_pairAlloc.destroy(&node->tab);
			_pairAlloc.construct(&node->tab, tmp->tab);
			node->right = _deleteNode(node->right, tmp->tab);
		}
		return node;
	}


	/**************************************/
	/*** NON MEMBER FUNCTIONS OVERLOADS ***/
	/**************************************/

	/*
	** RELATIONAL OPERATORS
	*/

	template<class Key, class T, class Compare, class Alloc>
	bool operator==(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin()));
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator!=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (lhs == rhs ? false : true);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return ft::lexicographical_compare(lhs.begin(), --lhs.end(), rhs.begin(), --rhs.end());
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator<=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	bool operator>=(const map<Key, T, Compare, Alloc>& lhs, const map<Key, T, Compare, Alloc>& rhs)
	{
		return !(lhs < rhs);
	}

	template<class Key, class T, class Compare, class Alloc>
	void	swap(map<Key, T, Compare, Alloc>& lhs, map<Key, T, Compare, Alloc>& rhs)
	{
		lhs.swap(rhs);
	}

}

#endif
