/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:32:31 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/18 11:32:31 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAP_HPP__
# define __MAP_HPP__

# include "../utils/Utils.hpp"
# include "../utils/MapIter.hpp"

namespace ft
{

template < class Key, class T, class Compare = ft::less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
class map
{
	public:
		typedef Key											key_type;
		typedef T											mapped_type;	
		typedef ft::pair<key_type, mapped_type>				value_type;
		typedef Compare										key_compare;
		class value_compare : ft::binary_function<value_type, value_type, bool>
		{
			friend class map<key_type, mapped_type, key_compare, Alloc>;

			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}

			public:
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}


		};
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef ft::ListIter<value_type>								iterator;
		typedef ft::ListIterConst<value_type>							const_iterator;
		//typedef ft::ListIter<const value_type>							const_iterator; //modif
		typedef	ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef	typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t													size_type;

		explicit map (const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_comp(comp)
		{
			_endlist = new (DL_List<ft::pair<key_type, mapped_type> >); //Voir si on enleve pas ça mdr
			_endlist->next = _endlist;
			_endlist->prev = _endlist;
		}

		template <class InputIterator>
		map (InputIterator first, InputIterator last, const key_compare& comp = key_compare(), const allocator_type& alloc = allocator_type())
		:	_endlist(NULL),
			_alloc(alloc),
			_comp(comp)

		{
			_endlist = new (DL_List<ft::pair<key_type, mapped_type> >);
			_endlist->next = _endlist;
			_endlist->prev = _endlist;
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}
		
		map (const map& x)
		{
			_endlist = new (DL_List<ft::pair<key_type, mapped_type> >);
			_endlist->next = _endlist;
			_endlist->prev = _endlist;
			const_iterator start = x.begin();
			
			while (start != x.end())
			{
				insert(*start);
				++start;
			}
		}
		
		~map()
		{
			this->clear();
			delete _endlist;
		}

		map& operator= (const map& x)
		{
			if (&x == this)
				return (*this);
			this->clear();
			this->insert(x.begin(), x.end());
			return (*this);
		}

		iterator begin()
		{
			return (iterator(_endlist->next));
		}

		const_iterator begin() const
		{
			return (const_iterator(_endlist->next));
		}

		iterator end()
		{
			return (iterator(_endlist));	
		}

		const_iterator end() const
		{
			return (const_iterator(_endlist));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		bool empty() const
		{
			if (_endlist->next == _endlist && _endlist->prev == _endlist)
				return (true);
			return (false);
		}

		size_type size() const
		{
			DL_List<value_type>	*tmp = _endlist;
			size_type			s = 0;

			while (tmp->next != _endlist)
			{
				++s;
				tmp = tmp->next;
			}
			return (s);
		}

		size_type max_size() const
		{
			return (DL_List_allocator().max_size());
		}

		mapped_type& operator[] (const key_type& k)
		{
			iterator tmp = find(k);

			if (tmp == end())
			{
				insert(ft::make_pair(k, mapped_type()));
				tmp = find(k);
				
				return ((*tmp).second);
			}
			return ((*tmp).second);
		}

		ft::pair<iterator,bool> insert (const value_type& val)
		{
			DL_List<value_type> *to_add;
			DL_List<value_type> *tmp = _endlist->next;

			//BST_List<T> *new_elem = new BST_List<T>();
			while (tmp != _endlist && key_compare()(tmp->val.first, val.first)/*tmp->val.first < val.first*/)
			{
				tmp = tmp->next;
			}
			if (tmp != _endlist && tmp->val.first == val.first)
				return (ft::pair<iterator, bool>(iterator(tmp), false));
			to_add = new_elem(val);
			add_elem_before(to_add, tmp);
			return (ft::pair<iterator, bool>(iterator(to_add), true));
		}

		iterator insert (iterator position, const value_type& val)
		{
			DL_List<value_type> *to_add;
			// iterator tmp = position;

			while (position._elem != _endlist && key_compare()(val.first, (*position).first))
				--position;
			if (position._elem != _endlist && (*position).first == val.first)
				return (position);
			while (position._elem != _endlist && key_compare()((*position).first, val.first))
				++position;
			if (position._elem != _endlist && (*position).first == val.first)
				return (position);
			// insert(val);
			to_add = new_elem(val);
			add_elem_before(to_add, position._elem);
			return (iterator(to_add));
		}
		
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				insert(*first);
				++first;
			}
		}

		void erase (iterator position)
		{
			del_one(position._elem);
		}

		size_type erase (const key_type& k)
		{
			element_type *tmp = _endlist->next;

			while (tmp != _endlist)
			{
				if (tmp->val.first == k)
				{
					del_one(tmp);
					return ((size_type)1);
				}
				tmp = tmp->next;
			}
			return ((size_type)0);
		}

     	void erase (iterator first, iterator last)
		{
			iterator tmp;

			while (first != last)
			{
				tmp = ++first;
				--first;
				del_one(first._elem);
				first = tmp;
			}
		}

		void swap (map& x)
		{
			element_type *tmp = x._endlist;
			x._endlist = _endlist;
			_endlist = tmp;
		}
	
		void clear()
		{
			DL_List<value_type> *node = _endlist->next;
			DL_List<value_type> *tmp;

			while (node != _endlist)
			{
				tmp = node->next;
				DL_List_allocator().destroy(node);
				DL_List_allocator().deallocate(node, 1);
				node = tmp;
			}
			_endlist->next = _endlist;
			_endlist->prev = _endlist;
		}

		/*
		** Observers
		*/
		key_compare key_comp() const
		{
			return (key_compare());
		}

		value_compare value_comp() const
		{
			return (value_compare(key_compare()));
		}

		/*
		** Operations
		*/
		iterator find (const key_type& k)
		{
			iterator tmp = begin();
			
			while (tmp != end())
			{
				
				if ((*tmp).first == k)
					return (tmp);
				++tmp;
			}
			return (tmp);
		}

		const_iterator find (const key_type& k) const
		{
			const_iterator tmp = begin();
			
			while (tmp != end())
			{
				if ((*tmp).first == k)
					return (tmp);
				++tmp;
			}
			return (tmp);
		}

		size_type count (const key_type& k) const
		{
			element_type *tmp = _endlist->next;

			while (tmp != _endlist)
			{
				if (tmp->val.first == k)
					return ((size_type)1);
				tmp = tmp->next;
			}
			return ((size_type)0);
		}

		iterator lower_bound (const key_type& k)
		{
			iterator tmp = begin();

			while (tmp != end())
			{
				if (key_compare()(tmp->first, k) == false)
					return (tmp);
				++tmp;
			}
			return (tmp);
		}

		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator tmp = begin();

			while (tmp != end())
			{
				if (key_compare()(tmp->first, k) == false)
					return (tmp);
				++tmp;
			}
			return (tmp);
		}

		iterator upper_bound (const key_type& k)
		{
			iterator tmp = begin();

			while (tmp != end())
			{
				if (key_compare()(k, tmp->first) == true)
					return (tmp);
				++tmp;
			}
			return (tmp);
		}

		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator tmp = begin();

			while (tmp != end())
			{
				if (key_compare()(k, tmp->first) == true)
					return (tmp);
				++tmp;
			}
			return (tmp);
		}
		
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const
		{
			const_iterator low = lower_bound(k);
			const_iterator upper = upper_bound(k);

			return (ft::make_pair<const_iterator, const_iterator>(low, upper));
		}

		pair<iterator,iterator>             equal_range (const key_type& k)
		{
			iterator low = lower_bound(k);
			iterator upper = upper_bound(k);
			return (ft::make_pair<iterator, iterator>(low, upper));
		}


	private:
		/*
		** Attributs
		*/
		typedef typename allocator_type::template rebind<DL_List<value_type> >::other DL_List_allocator;
		typedef DL_List<value_type> element_type;

		DL_List<value_type> *_endlist;
		allocator_type 		_alloc;
		key_compare			_comp;


		void		del_one(DL_List<value_type> *_elem)
		{
			_elem->prev->next = _elem->next;
			_elem->next->prev = _elem->prev;
			DL_List_allocator().destroy(_elem);
			DL_List_allocator().deallocate(_elem, 1);
		}

		DL_List<value_type>	*new_elem(const value_type &val)
		{
			DL_List<value_type> *n = DL_List_allocator().allocate(1);
			DL_List_allocator().construct(n, DL_List<value_type>(val));
			return (n);
		}


		DL_List<value_type>	*add_elem_before(DL_List<value_type> *add, DL_List<value_type> *pos)
		{
			pos->prev->next = add;
			add->prev = pos->prev;
			add->next = pos;
			pos->prev = add;
			return (add);
		}

		void		disconnect_elem(DL_List<value_type> *elem)
		{
			if (elem->prev)
				elem->prev->next = elem->next;
			if (elem->next)
				elem->next->prev = elem->prev;
			elem->prev = NULL;
			elem->next = NULL;
		}
};

}

#endif