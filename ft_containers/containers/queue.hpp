/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:32:39 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/21 12:49:52 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __QUEUE_HPP__
# define __QUEUE_HPP__

#include "list.hpp"

namespace ft
{

template <class T, class Container = ft::list<T> >
	class queue
{
	public:
		typedef T			value_type;
		typedef	Container	container_type;
		typedef size_t		size_type;

		explicit queue (const container_type& ctnr = container_type())
		:	_cont(ctnr)
		{}

		~queue() {}

		bool empty() const
		{
			return (this->_cont.empty());
		}

		size_type size() const
		{
			return (this->_cont.size());
		}
		
		value_type& front()
		{
			return (this->_cont.front());
		}
		
		const value_type& front() const
		{
			return (this->_cont.front());
		}

		value_type& back()
		{
			return (this->_cont.back());
		}
		
		const value_type& back() const
		{
			return (this->_cont.back());
		}

		void push (const value_type& val)
		{
			this->_cont.push_back(val);
		}

		void pop()
		{
			this->_cont.pop_front();
		}


	template <class Tx, class ContainerX>
		friend bool operator== (const queue<Tx,ContainerX>& lhs, const queue<Tx,ContainerX>& rhs);

	template <class Tx, class ContainerX>
		friend bool operator!= (const ft::queue<Tx,ContainerX>& lhs, const ft::queue<Tx,ContainerX>& rhs);

	template <class Tx, class ContainerX>
		friend bool operator<  (const ft::queue<Tx,ContainerX>& lhs, const ft::queue<Tx,ContainerX>& rhs);

	template <class Tx, class ContainerX>
		friend bool operator<= (const ft::queue<Tx,ContainerX>& lhs, const ft::queue<Tx,ContainerX>& rhs);

	template <class Tx, class ContainerX>
		friend bool operator>  (const ft::queue<Tx,ContainerX>& lhs, const ft::queue<Tx,ContainerX>& rhs);

	template <class Tx, class ContainerX>
		friend bool operator>= (const ft::queue<Tx,ContainerX>& lhs, const ft::queue<Tx,ContainerX>& rhs);

	protected:
		container_type _cont;
	
};

template <class T, class Container>
	bool operator== (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (lhs._cont == rhs._cont);
}

template <class T, class Container>
	bool operator!= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (lhs._cont != rhs._cont);
}

template <class T, class Container>
	bool operator<  (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (lhs._cont < rhs._cont);
}

template <class T, class Container>
	bool operator<= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (lhs._cont <= rhs._cont);
}

template <class T, class Container>
	bool operator>  (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (lhs._cont > rhs._cont);
}

template <class T, class Container>
	bool operator>= (const ft::queue<T,Container>& lhs, const ft::queue<T,Container>& rhs)
{
	return (lhs._cont >= rhs._cont);
}
	
}

#endif
