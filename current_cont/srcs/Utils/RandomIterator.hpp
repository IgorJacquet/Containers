/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RandomIterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:03:36 by ijacquet          #+#    #+#             */
/*   Updated: 2021/11/12 15:03:37 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RANDOMITERATOR_HPP
# define RANDOMITERATOR_HPP

# include <limits>
# include <cstddef>
# include <stddef.h>

namespace ft {
	template <typename type>
    class Random
    {
		protected:
			type						*_value;
		public:
			typedef	type				value_type;
			typedef	value_type&			reference;
			typedef	value_type const&	const_reference;
			typedef	value_type*			pointer;
			typedef ptrdiff_t			difference_type;

			Random(void) : _value(NULL)
			{
			}

			Random(type *x) : _value(x)
			{
			}

			Random(const Random& x)
			{
				*this = x;
			}

			virtual ~Random(void)
			{
			}

			Random&	operator=(Random const &x)
			{
				if (this == &x)
					return *this;
				this->_value = x._value;
				return *this;
			}
			
			value_type		*getValue(void) const
			{
				return _value; 
			}

			bool			operator==(const Random &x) const
			{
				return this->_value == x._value;
			}

			bool			operator!=(const Random &x) const
			{
				return this->_value != x._value;
			}

			bool			operator<(const Random &x) const
			{
				return this->_value < x._value;
			}

			bool			operator<=(const Random &x) const
			{
				return this->_value <= x._value;
			}

			bool			operator>(const Random &x) const
			{
				return this->_value > x._value;
			}

			bool			operator>=(const Random &x) const
			{
				return this->_value >= x._value;
			}

			Random<type>	&operator++(void)
			{
				this->_value++;
				return *this;
			}

			Random<type>	operator++(int)
			{
				Random tmp(*this);
				this->operator++();
				return tmp;
			}

			Random<type>	&operator--(void)
			{
				this->_value--;
				return *this;
			}

			Random<type>	operator--(int)
			{
				Random tmp(*this);
				this->operator--();
				return tmp;
			}


			difference_type	operator-(const Random &x) const
			{
				return (this->_value - x._value);
			}

			Random<type>	operator+(difference_type n) const
			{
				return Random(this->_value + n);
			}

			Random<type>	operator-(difference_type n) const
			{
				return Random(this->_value - n);
			}

			friend Random<type>	operator+(difference_type n, const Random &x)
			{
				return x._value + n;
			}
    };
}

#endif