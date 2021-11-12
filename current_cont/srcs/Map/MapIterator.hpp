/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:03:32 by ijacquet          #+#    #+#             */
/*   Updated: 2021/11/12 16:40:04 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPITERATOR_HPP
# define MAPITERATOR_HPP

# include "../Utils/Utils.hpp"

namespace ft
{
    template<typename T, typename node>
    class map_iterator
    {
        public:
			typedef	T					value_type;
			typedef	value_type&			reference;
			typedef	value_type const&	const_reference;
			typedef	value_type*			pointer;
			typedef ptrdiff_t			difference_type;
			typedef node*				node_ptr;
			node	*_node;
			map_iterator(node *src)
			{
				_node = src;
			}

			map_iterator() : _node(NULL)
			{
			}

			map_iterator(map_iterator const &src)
			{
				*this = src;
			}
			
			virtual ~map_iterator()
			{
			}

			map_iterator&	operator=(map_iterator const &rhs)
			{
				_node = rhs._node;
				return *this;
			}

			operator map_iterator<const T, node>() const
			{
				return map_iterator<const T, node>(this->_node);
			}

			template <class U>
			bool	operator==(const map_iterator<U, node> &x) const 
			{
				return this->_node == x._node;
			}
			
			template <class U>
			bool	operator!=(const map_iterator<U, node> &x) const
			{
				return this->_node != x._node;
			}

			map_iterator	&operator++(void)
			{
				if (_node->right)
					_node = minValueNode(_node->right);
				else if (_node->parent)
				{
					node	*tmp = _node;
					_node = _node->parent;
					while (_node && tmp == _node->right)
					{
						tmp = _node;
						_node = _node->parent;
					}
				}
				return *this;
			}

			map_iterator	operator++(int)
			{
				map_iterator tmp(*this);
				this->operator++();
				
				return tmp;
			}

			map_iterator	&operator--(void)
			{
				if (_node->left)
					_node = maxValueNode(_node->left);
				else if (_node->parent)
				{
					node	*tmp = _node;
					_node = _node->parent;
					while (_node && tmp == _node->left)
					{
						tmp = _node;
						_node = _node->parent;
					}
				}
				return *this;
			}

			map_iterator	operator--(int)
			{
				map_iterator tmp(*this);
				this->operator--();
				
				return tmp;
			}

			reference		operator*(void) const
			{
				return this->_node->tab;
			}

			pointer			operator->(void) const
			{
				return &this->_node->tab;
			}
    };
}

#endif