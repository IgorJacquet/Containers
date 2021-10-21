/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:33:26 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/18 11:33:26 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __VECTOR_HPP__
# define __VECTOR_HPP__

# include <stdexcept>
# include "../utils/VectIter.hpp"
# include "../utils/Iterators.hpp"

/*
** TODO
** return error en cas de n qui depasse size etc
** throw des out of range au at etc
*/

namespace ft
{

template < class T, class Alloc = std::allocator<T> > 
class vector
{
	public:
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef size_t										size_type;
		typedef ft::iterator_traits<iterator>				difference_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef ft::VectIter<value_type>					iterator;
		typedef ft::VectIter<const value_type>				const_iterator;	
		typedef ft::reverse_iterator<iterator>				reverse_iterator;	
		typedef ft::reverse_iterator<const_iterator>		const_reverse_iterator;

		explicit vector (const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_max_size(NULL)
		{}

		explicit vector (size_type n, const value_type& val = value_type(), const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_max_size(NULL)
		{
			while (n > 0)
			{
				push_back(val);
				--n;
			}
		}
							
		template <class InputIterator>
				vector (InputIterator first, InputIterator last, const allocator_type& alloc = allocator_type())
		:	_alloc(alloc),
			_start(NULL),
			_end(NULL),
			_max_size(NULL)
		{
			while (first != last)
			{
				push_back(*first);
				++first;
			}
		}

		vector (const vector& x)
		:	_alloc(x._alloc),
			_start(NULL),
			_end(NULL),
			_max_size(NULL)
		{
			this->insert(this->end(), x.begin(), x.end());
		}

		~vector()
		{
			clear();
			_alloc.deallocate(_start, capacity());
		}

		vector& operator= (const vector& x)
		{
			if (&x == this)
				return (*this);
			this->clear();
			this->insert(this->end(), x.begin(), x.end());
			return (*this);
		}

		/*
		** Iterators
		*/
		iterator				begin()
		{
			return (iterator(_start));
		}

		const_iterator			begin() const
		{
			return (const_iterator(_start));
		}

		iterator				end()
		{
			return (iterator(_end));
		}
	
		const_iterator			end() const
		{
			return (const_iterator(_end));
		}

		reverse_iterator		rbegin()
		{
			return (reverse_iterator(_end));
		}

		const_reverse_iterator	rbegin() const
		{
			return (const_reverse_iterator(_end));
		}
	
		reverse_iterator		rend()
		{
			return (reverse_iterator(_start));
		}

		const_reverse_iterator	rend() const
		{
			return (const_reverse_iterator(_start));
		}

		/*
		** Capacity
		*/
		size_type	size() const
		{
			return (this->_end - this->_start);
		}

		size_type	max_size() const
		{
			return (allocator_type().max_size());
		}

		void		resize (size_type n, value_type val = value_type())
		{
			//if (n > max_size() || size() + n > max_size())
				//return (error jsp quoi);
			if (n < size())
			{
				while (size() > n)
				{
					--_end;
					_alloc.destroy(_end);
				}
			}
			else if (n > size())
			{
				insert(end(), n - size(), val);
			}
		}

		size_type	capacity() const
		{
			return (this->_max_size - this->_start);
		}

		bool		empty() const
		{
			if (size() == 0)
				return (true);
			return (false);
		}

		void		reserve (size_type n)
		{
			//if (n > this->max_size())
				//faire erreur;
			if (n > this->capacity())
			{
				pointer tmp_start = this->_start;
				pointer tmp_i = this->_start;
				pointer tmp_end = this->_end;
				size_t tmp_max_size = this->capacity();
				this->_start = _alloc.allocate(n); //new value_type[n];
				this->_end = this->_start;
				while (tmp_i != tmp_end)
				{
					_alloc.construct(_end, *tmp_i);
					tmp_i++;
					_end++;
				}
				_max_size = _start + n;
				_alloc.deallocate(tmp_start, tmp_max_size);
			}
		}

		/*
		** Elements access
		*/
		reference		operator[] (size_type n)
		{
			return (*(_start + n));
		}

		const_reference	operator[] (size_type n) const
		{
			return (*(_start + n));
		}

		reference		at (size_type n)
		{
			if (n >= size())
				throw std::out_of_range("Out of range");
			return (*(_start + n));
		}
		const_reference	at (size_type n) const
		{
			if (n >= size())
				throw std::out_of_range("Out of range");
			return (*(_start + n));
		}

		reference		front()
		{
			return (*_start);
		}

		const_reference	front() const
		{
			return (*_start);
		}

		reference back()
		{
			return (*(_end - 1));
		}

		const_reference back() const
		{
			return (*(_end - 1));
		}

		/*
		** Modifiers
		*/
		template <class InputIterator>
  		void		assign (InputIterator first, InputIterator last)
		{
			clear();
			insert(end(), first, last);
		}

		void		assign (size_type n, const value_type& val)
		{
			clear();
			insert(end(), n, val);
		}

		void push_back (const value_type& val)
		{
			insert(end(), val);
		}

		void pop_back()
		{
			erase(--(end()));
		}

		iterator	insert (iterator position, const value_type& val)
		{
			size_t last_pos;

			if (_end == _max_size)
			{
				last_pos = &(*position) - _start;
				reserve(capacity() == 0 ? 1 : capacity() * 2);
				position = iterator(_start + last_pos);
			}
			iterator itend = end();
			++_end;
			if (itend != position)
			{
				while (itend != position)
				{
					--itend;
					_alloc.construct(&(*(itend + 1)), *itend);
				}
			}
			_alloc.construct(&(*itend), val);
			return (itend);
		}
		
   		void		insert (iterator position, size_type n, const value_type& val)
		{
			while (n > 0)
			{
				--n;
				position = insert(position, val);
			}
		}

		template <class InputIterator>
			void	insert (iterator position, InputIterator first, InputIterator last)
		{
			while (first != last)
			{
				position = insert(position, *first);
				++first;
				++position;
			}
		}

		iterator	erase (iterator position)
		{
			pointer	tmp = &(*position);
			
			_alloc.destroy(&(*position));
			while (tmp + 1 != _end)
			{
				_alloc.construct(&(*tmp), *(&(*tmp) + 1));
				_alloc.destroy(&(*tmp) + 1);
				++tmp;
			}
			--_end;
			return (position);
		}

		iterator	erase (iterator first, iterator last)
		{
			iterator tmp = first;
	
			while (first != last)
			{
				tmp = erase(tmp);
				++first;
			}
			return (tmp);
		}

		void swap (vector& x)
		{
			if (x == *this)
				return ;
			allocator_type	tmp_alloc = _alloc;
			pointer			tmp_start = _start;
			pointer			tmp_end = _end;
			pointer			tmp_max_size = _max_size;

			_alloc = x._alloc;
			_start = x._start;
			_end = x._end;
			_max_size = x._max_size;

			x._alloc = tmp_alloc;
			x._start = tmp_start;
			x._end = tmp_end;
			x._max_size = tmp_max_size;
		}

		void		clear()
		{
			size_t i = size();
			while (i > 0)
			{
				--i;
				--_end;
				_alloc.destroy(_end);
			}
		}

	private:
		allocator_type	_alloc;
		pointer			_start;
		pointer			_end;
		pointer			_max_size;

};

template <class T, class Alloc>
bool operator== (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	if (lhs.size() != rhs.size())
		return (false);
	typename ft::vector<T>::const_iterator it = lhs.begin();
	typename ft::vector<T>::const_iterator it2 = rhs.begin();

	while (it2 != rhs.end())
	{
		if (it2 == rhs.end() || *it != *it2)
			return (false);
		++it;
		++it2;
	}
	return (true);
}

template <class T, class Alloc>
bool operator!= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (!(lhs == rhs));
}

template <class T, class Alloc>
bool operator<  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
}

template <class T, class Alloc>
bool operator<= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (!(rhs < lhs));
}

template <class T, class Alloc>
bool operator>  (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (rhs < lhs);
}

template <class T, class Alloc>
bool operator>= (const ft::vector<T,Alloc>& lhs, const ft::vector<T,Alloc>& rhs)
{
	return (!(lhs < rhs));
}


template <class T, class Alloc>
void swap (ft::vector<T,Alloc>& x, ft::vector<T,Alloc>& y)
{
	x.swap(y);
}

}

#endif