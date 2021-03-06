/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:03:24 by ijacquet          #+#    #+#             */
/*   Updated: 2021/11/12 17:23:57 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include <iostream>
# include "../Vector/Vector.hpp"

namespace ft
{
	template <class T, class Container = ft::vector<T> >
	class	stack
	{
		public:
			typedef T				value_type;
			typedef Container		container_type;
			typedef unsigned int	size_type;

			explicit	stack(const container_type& ctnr = container_type()) : _ctnr(ctnr)
			{
			}
			
			virtual 	~stack(void)
			{
			}

			bool		empty() const
			{
				return _ctnr.empty();
			}

			size_type	size() const
			{
				return _ctnr.size();
			}

			value_type& top()
			{
				return _ctnr.back();
			}

			const value_type&	top() const
			{
				return _ctnr.top();
			}

			void 		push(const value_type& val)
			{
				_ctnr.push_back(val);
			}

			void 		pop()
			{
				_ctnr.pop_back();
			}

			stack		&operator=(const stack& x)
			{
				_ctnr = x._ctnr;

				return *this;
			}

			friend bool operator==(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
			{
				return (lhs._ctnr == rhs._ctnr);
			}

			friend bool operator<(const stack<T, Container> &lhs, const stack<T, Container> &rhs)
			{
				return (lhs._ctnr < rhs._ctnr);
			}

		protected:
			container_type	_ctnr;
	};

	template <class T, class Container>
	bool operator!=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	template <class T, class Container>
	bool operator<=(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(rhs < lhs);
	}

	template <class T, class Container>
	bool operator>(const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}

	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs < rhs);
	}
}

#endif
