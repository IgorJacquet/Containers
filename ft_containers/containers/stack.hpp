/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:32:58 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/18 11:32:58 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __STACK_HPP__
# define __STACK_HPP__

# include <deque> // A VirEerrr // modif std::deque -> ft::deque
# include "list.hpp"

namespace ft
{
template <class T, class Container = ft::list<T> >
class stack
{
	public:
		typedef T			value_type;
		typedef Container	container_type;
		typedef size_t		size_type;

	explicit stack (const container_type& ctnr = container_type())
	:	_cont(ctnr)
	{}

	~stack() {};

	bool empty() const
	{
		return (this->_cont.empty());
	}

	size_type size() const
	{
		return (_cont.size());
	}

	value_type& top()
	{
		return (_cont.back());
	}

	const value_type& top() const
	{
		return (_cont.back());
	}

	void push (const value_type& val)
	{
		_cont.push_back(val);
	}

	void pop()
	{
		_cont.pop_back();
	}

	template <class Tx, class ContainerX>
  		friend bool operator== (const ft::stack<Tx,ContainerX>& lhs, const ft::stack<Tx,ContainerX>& rhs);
	template <class Tx, class ContainerX>
		friend bool operator!= (const ft::stack<Tx,ContainerX>& lhs, const ft::stack<Tx,ContainerX>& rhs);
	template <class Tx, class ContainerX>
		friend bool operator<  (const ft::stack<Tx,ContainerX>& lhs, const ft::stack<Tx,ContainerX>& rhs);
	template <class Tx, class ContainerX>
		friend bool operator<= (const ft::stack<Tx,ContainerX>& lhs, const ft::stack<Tx,ContainerX>& rhs);
	template <class Tx, class ContainerX>
		friend bool operator>  (const ft::stack<Tx,ContainerX>& lhs, const ft::stack<Tx,ContainerX>& rhs);
	template <class Tx, class ContainerX>
		friend bool operator>= (const ft::stack<Tx,ContainerX>& lhs, const ft::stack<Tx,ContainerX>& rhs);

	protected:
		container_type _cont;

};

template <class T, class Container>
  bool operator== (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
  {
	  return (lhs._cont == rhs._cont);
  }

template <class T, class Container>
  bool operator!= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
  {
	  return (lhs._cont != rhs._cont);
  }

template <class T, class Container>
  bool operator<  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
  {
	  return (lhs._cont < rhs._cont);
  }

template <class T, class Container>
  bool operator<= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
  {
	  return (lhs._cont <= rhs._cont);
  }

template <class T, class Container>
  bool operator>  (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
  {
	  return (lhs._cont > rhs._cont);
  }

template <class T, class Container>
  bool operator>= (const ft::stack<T,Container>& lhs, const ft::stack<T,Container>& rhs)
  {
	  return (lhs._cont >= rhs._cont);
  }

}

#endif