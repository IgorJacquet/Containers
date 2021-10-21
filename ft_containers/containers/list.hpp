/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:32:19 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/18 11:32:19 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __LIST_HPP__
# define __LIST_HPP__

# include <memory>
# include <time.h>
# include <unistd.h>
# include "../utils/Utils.hpp"
# include "../utils/ListIter.hpp"
 

/*
** TODO
** commentires a remove au swap
** checker si les itérateur reçus sont du bon type
** checker pour les const machin là
*/

namespace ft
{
template <class T, class Alloc = std::allocator<T> > 
class list
{
	public :
		/*
		** Member types
		*/
		typedef T														value_type;
		typedef Alloc													allocator_type;
		typedef typename allocator_type::reference						reference;
		typedef typename allocator_type::const_reference				const_reference;
		typedef typename allocator_type::pointer						pointer;
		typedef typename allocator_type::const_pointer					const_pointer;
		typedef	ft::ListIter<value_type>								iterator;
		//typedef	ft::ListIter<value_type>								iterator; //modif
		typedef ft::ListIterConst<value_type>							const_iterator;
		//typedef ft::ListIter<value_type const>							const_iterator;  //modif
		typedef	ft::reverse_iterator<iterator>							reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>					const_reverse_iterator;
		typedef typename ft::iterator_traits<iterator>::difference_type	difference_type;
		typedef size_t													size_type;

		/*
		** Constructor - Destructor - Copy
		*/
		explicit list (const allocator_type& alloc = allocator_type())
		:	_alloc(alloc)
		{
			_endlist = new (DL_List<T>);
			_endlist->next = _endlist;
			_endlist->prev = _endlist;
		}

		explicit list (size_type n, const value_type& val =  value_type(), const allocator_type& alloc = allocator_type())
		:	_alloc(alloc)
		{
			_endlist = new (DL_List<T>);
			_endlist->next = _endlist;
			_endlist->prev = _endlist;
			insert(end(), n, val);
		}

		template <class InputIterator>
		list (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		:	_alloc(alloc)
		{
			_endlist = new (DL_List<T>);
			_endlist->next = _endlist;
			_endlist->prev = _endlist;
			insert(end(), first, last);
		}

		list (const list& x)
		:	_alloc(x._alloc)
		{
			_endlist = new (DL_List<T>);
			_endlist->next = _endlist;
			_endlist->prev = _endlist;

			const_iterator b = x.begin();
			const_iterator e = x.end();
			while (b != e)
			{
				add_elem_before(new_elem(*b), _endlist);
				(++b);
			}
		}

		~list()
		{
			//del_list();
			clear();
			delete _endlist;
		}

		list& operator= (const list& x)
		{
			if (&x == this)
				return (*this);
			this->clear();
			insert(end(), x.begin(), x.end());
			return (*this);
		}
		/*
		** Asked functions
		*/

		/*
		** Iterators
		*/
		iterator			begin()
		{
			return (iterator(_endlist->next));
		}

		iterator 			end()
		{
			return (iterator(_endlist));
		}

		const_iterator		begin() const
		{
			return (const_iterator(_endlist->next));
		}

		const_iterator 		end() const
		{
			return (const_iterator(_endlist));
		}

		reverse_iterator	rbegin()
		{
			return (reverse_iterator(end()));
		}

		reverse_iterator	rend()
		{
			return (reverse_iterator(begin()));
		}

		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(begin()));
		}

		/*
		**	Capacity
		*/
		bool		empty() const
		{
			//std::cout << "empt()" << std::endl;
			if (size() == 0)
				return (true);
			else
				return (false);		
		}

		size_type	size() const
		{
			size_type			sz = 0;
			DL_List<value_type>	*tmp = _endlist->next;

			//if (_endlist->next == _endlist)
			//	P("TRUEe");
			while (tmp != _endlist)
			{
				//std::cout << "empt()" << std::endl;
				++sz;
				tmp = tmp->next;
			}
			return (sz);
		}

		size_type	max_size() const {return (node_allocator().max_size());}

		/*
		** Element access
		*/
		reference		front() {return (_endlist->next->val);}

		const_reference	front() const {return (_endlist->next->val);}

		reference		back() {return (_endlist->prev->val);}

		const_reference	back() const {return (_endlist->prev->val);}

		/*
		** Modifiers
		*/
		template <class InputIterator>
		void 		assign(InputIterator first, InputIterator last)
		{
			clear();
			while (first != last)
			{
				//push_back(new_elem(*first));
				push_back(*first);
				++first;
			}
		}

		void 		assign (size_type n, const value_type& val)
		{
			clear();
			while (n--)
				push_back(val);
		}

		void		push_front(const value_type &val) {add_elem_front(new_elem(val));}

		void		pop_front() {del_one(_endlist->next);}

		void		push_back(const value_type &val) {add_elem_back(new_elem(val));}

		void		pop_back() {del_one(_endlist->prev);}

		iterator 	insert (iterator position, const value_type& val)
		{
			return (iterator(add_elem_before(new_elem(val), position._elem)));
		}

		void 		insert (iterator position, size_type n, const value_type& val)
		{
			while (n--)
			{
				add_elem_before(new_elem(val), position._elem);
			}
		}

		template <class InputIterator>
		void		insert (iterator position, InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				add_elem_before(new_elem(*first), position._elem);
				++first;
			}
		}

		iterator	erase (iterator position)
		{
			iterator ret(position._elem->next);

			del_one(position._elem);
			return (ret);
		}

		iterator	erase (iterator first, iterator last)
		{
			iterator ret(last._elem->next);
			iterator tmp;
	
			while (first != last)
			{
				tmp = first;
				++first;
				del_one(tmp._elem);
				
			}
			return (ret);
		}

		void		swap(list &x)
		{
			/*if (x == *this)
				return ;*/
			DL_List<T>	*tmp = x._endlist;
			x._endlist = _endlist;
			_endlist = tmp;
		}

		void		resize(size_type n, value_type val = value_type())
		{
			size_t	len = size();
			if (len > n)
			{
				while (len > n)
				{
					pop_back();
					--len;
				}
			}
			else
			{
				while (len < n)
				{
					insert(end(), val);
					++len;
				}
			}
		}

		void		clear()
		{
			DL_List<T> *node = _endlist->next;
			DL_List<T> *tmp;

			while (node != _endlist)
			{
				tmp = node->next;
				delete node;
				node = tmp;
			}
			_endlist->next = _endlist;
			_endlist->prev = _endlist;
		}

	/*
	** Operations
	*/
	void	splice (iterator position, list& x)
	{
		iterator	x_first = x.begin();
		iterator	x_last = x.end();
		iterator	x_tmp;

		while (x_first != x_last)
		{
			x_tmp = ++x_first;
			--x_first;
			x.disconnect_elem(x_first._elem);
			add_elem_before(x_first._elem, position._elem);
			x_first = x_tmp;
		}
	}

	void	splice (iterator position, list& x, iterator i)
	{
		if (position != i)
		{
			x.disconnect_elem(i._elem);
			add_elem_before(i._elem, position._elem);
		}
	}

	void	splice (iterator position, list& x, iterator first, iterator last)
	{
		iterator x_tmp;

		while (first != last)
		{
			x_tmp = ++first;
			--first;
			x.disconnect_elem(first._elem);
			add_elem_before(first._elem, position._elem);
			first = x_tmp;
		}
	}

	void	remove(const value_type& val)
	{
		iterator first = begin();
		iterator last = end();
		iterator tmp;

		while (first != last)
		{
			tmp = (++first)--;
			if (*first == val)
				del_one(first._elem);
			first = tmp;
		}
	}

	template <class Predicate>
	void	remove_if(Predicate pred)
	{
		iterator first = begin();
		iterator last = end();
		iterator tmp;

		while (first != last)
		{
			tmp = (++first)--;
			if (pred(*first))
				del_one(first._elem);
			first = tmp;
		}
	}

	void	unique()
	{
		iterator first = begin();
		iterator second = begin();
		iterator last = end();
		iterator tmp;

		++second;
		while (second != last)
		{
			tmp = (++second)--;
			if (second._elem->prev != _endlist && *second == *first)
				del_one(second._elem);
			else
				++first;
			second = tmp;
		}
	}

	template <class BinaryPredicate>
	void	unique(BinaryPredicate binary_pred)
	{
		iterator first = begin();
		iterator second = begin();
		iterator last = end();
		iterator tmp;

		
		while (second != last)
		{
			tmp = (++second)--;
			//++second;
			if (second._elem->prev != _endlist && binary_pred(*((--second)++), *second) == true)
				del_one(second._elem);
			// else
			// 	++first;
			second = tmp;
		}
	}

	void	merge(list& x)
	{
		if (&x == this)
			return ;
		iterator x_first = x.begin();
		iterator x_last = x.end();
		iterator first = begin();
		iterator tmp;

		while (x_first != x_last)
		{
			tmp = (++x_first)--;
			if (first != end() && *first < *x_first)
				++first;
			else
			{
				x.disconnect_elem(x_first._elem);
				add_elem_before(x_first._elem, first._elem);
				x_first = tmp;
			}
		}
	}

	template <class Compare>
	void	merge(list& x, Compare comp)
	{
		if (&x == this)
			return ;
		iterator x_first = x.begin();
		iterator x_last = x.end();
		iterator first = begin();
		iterator tmp;

		while (x_first != x_last)
		{
			tmp = (++x_first)--;
			if (first != end() && !comp(*x_first, *first))
				++first;
			else
			{
				x.disconnect_elem(x_first._elem);
				add_elem_before(x_first._elem, first._elem);
				x_first = tmp;
			}
		}
	}

	void	sort()
	{
		DL_List<T>	*first;
		//DL_List<T>	*tmp;
		bool		sorted = false;

		if (empty())
			return ;
		while (sorted == false)
		{
			sorted = true;
			first = _endlist->next;
			while (first->next != _endlist)
			{
				//if (std::less<T>{}(first->next->val, first->val))
				if (first->next->val < first->val)
				{
					swap_elem(first, first->next);
					sorted = false;
				}
				else
					first = first->next;	
			}
		}
	}

	template <class Compare>
	void	sort(Compare comp)
	{
		DL_List<T>	*first;
		//DL_List<T>	*tmp;
		bool		sorted = false;

		if (empty())
			return ;
		while (sorted == false)
		{
			sorted = true;
			first = _endlist->next;
			while (first->next != _endlist)
			{
				if (comp(first->next->val, first->val))
				{
					swap_elem(first, first->next);
					sorted = false;
				}
				else
					first = first->next;	
			}
		}
	}

	void	reverse()
	{
		DL_List<T>	*tmp;
		DL_List<T>	*first = _endlist->next;

		_endlist->next = _endlist->prev;
		_endlist->prev = first;
		while (first != _endlist)
		{
			tmp = first->prev;
			first->prev = first->next;
			first->next = tmp;
			first = first->prev;
		}
	}

	private :
		/*  
		** Allocator size for max_size
		** The real size to calculate max_size is DL_List no "T"
		** Doc https://stackoverflow.com/questions/14148756/what-does-template-rebind-do 
		*/
		typedef typename allocator_type::template rebind<DL_List<T> >::other node_allocator;
		
		allocator_type	_alloc;
		DL_List<T>		*_endlist;

		/*
		** Other
		*/

		/*
		** Using allocator for destroy / deallocate a node
		** https://stackoverflow.com/questions/26667026/difference-between-destroy-destructor-deallocate-in-stdallocator
		*/
		void		del_one(DL_List<T> *_elem)
		{
			_elem->prev->next = _elem->next;
			_elem->next->prev = _elem->prev;
			node_allocator().destroy(_elem);
			node_allocator().deallocate(_elem, 1);
		}

		DL_List<T>	*new_elem(const value_type &val)
		{
			DL_List<T> *n = new (DL_List<T>);

			n->next = NULL;
			n->prev = NULL;
			n->val = val;
			return (n);
		}

		void		add_elem_back(DL_List<T> *elem)
		{
			elem->prev = _endlist->prev;
			elem->next = _endlist;
			if (_endlist->next == _endlist)
				_endlist->next = elem;
			else
				_endlist->prev->next = elem;
			_endlist->prev = elem;
		}

		void		add_elem_front(DL_List<T> *elem)
		{
			elem->next = _endlist->next;
			elem->prev = _endlist;
			if (_endlist->prev == _endlist)
				_endlist->prev = elem;
			else
				_endlist->next->prev = elem;
			_endlist->next = elem;
		}

		DL_List<T>	*add_elem_before(DL_List<T> *add, DL_List<T> *pos)
		{
			pos->prev->next = add;
			add->prev = pos->prev;
			add->next = pos;
			pos->prev = add;
			return (add);
		}

		void		disconnect_elem(DL_List<T> *elem)
		{
			if (elem->prev)
				elem->prev->next = elem->next;
			if (elem->next)
				elem->next->prev = elem->prev;
			elem->prev = NULL;
			elem->next = NULL;
		}

		void		swap_elem(DL_List<T> *e1, DL_List<T> *e2)
		{
			DL_List<T> *tmp = e1->prev;

			e1->prev->next = e2;
			e2->next->prev = e1;

			e1->next = e2->next;
			e1->prev = e2;

			e2->next = e1;
			e2->prev = tmp;
		}
};
	
template <class T, class Alloc>
bool operator== (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	typename ft::list<T>::const_iterator it1 = lhs.begin();
	typename ft::list<T>::const_iterator it2 = rhs.begin();
	while (it1 != lhs.end())
	{
		if (it2 == rhs.end() || *it1 != *it2)
			return (false);
		++it1;
		++it2;
	}
	return (true);
}

template <class T, class Alloc>
bool operator!= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}


template <class T, class Alloc>
  bool operator<  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
  bool operator<= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
  bool operator>  (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
  bool operator>= (const ft::list<T,Alloc>& lhs, const ft::list<T,Alloc>& rhs)
{
	return (!(lhs < rhs));
}
  
template <class T, class Alloc>
  void swap (ft::list<T,Alloc>& x, ft::list<T,Alloc>& y)
{
	x.swap(y);
}

} // end namespace ft

#endif