/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   MapIter.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:34:29 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/18 11:34:29 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef __MAPITER_HPP__
# define __MAPITER_HPP__

# include "Utils.hpp"
# include "Iterators.hpp"

namespace ft
{

template <typename T, class Compare>
class MapIter /*public ft::Iterator<ft::bidirectionnal_iterator_tag, T>*/
{
	public:
		typedef typename ft::Iterator<ft::bidirectionnal_iterator_tag, BST_List<T> >::value_type		value_type;
		typedef typename ft::Iterator<ft::bidirectionnal_iterator_tag, BST_List<T> >::difference_type	difference_type;
		typedef typename ft::Iterator<ft::bidirectionnal_iterator_tag, BST_List<T> >::reference			reference;
		typedef typename ft::Iterator<ft::bidirectionnal_iterator_tag, BST_List<T> >::pointer			pointer;
		typedef typename ft::Iterator<ft::bidirectionnal_iterator_tag, BST_List<T> >::iterator_category	iterator_category;

	BST_List<T>	*_elem;
	BST_List<T>	*_endlist;
	Compare		_comp;

	/*
	** Constructor - Destructor - Copy
	*/
	MapIter(const Compare &comp = Compare())
	:	_elem(NULL),
		_endlist(NULL),
		_comp(comp)
	{}

	MapIter(const MapIter &copy)
	:	_elem(copy._elem),
		_endlist(copy._endlist),
		_comp(copy._comp)
	{}

	MapIter(T *elem, T *endlist, const Compare &comp = Compare())
	:	_elem(elem),
		_endlist(endlist),
		_comp(comp)
	{}

	MapIter	&operator=(const MapIter &op)
	{
		if (op == *this)
			return (*this);
		_elem(op._elem);
		_endlist(op._endlist);
		_comp(op._comp);
		return (*this);
	}

	virtual ~MapIter() {}

	/*
	** Operators
	*/
	reference operator*() const
	{
		return (this->_elem->_v);
	}

	pointer operator->() const
	{
		return (&this->_elem->_v);
	}

	MapIter &operator++()
	{
		pointer tmp = _elem;

		tmp = tmp->next;
		if (tmp->right == _endlist)
		{
			tmp = _elem->parent;
			while (tmp != _endlist && comp(tmp->_v->first, _elem->_v->first))
				tmp = tmp->parent;
			_elem = tmp;
		}
		else if (tmp == _endlist)
			tmp = _endlist->right;
		else
		{
			tmp = _elem->right;
			while (tmp->left != _endlist)
				tmp = tmp->left;

		}
		return (*this);
	}

	MapIter &operator++(int)
	{
		MapIter tmp(*this);
		operator++();
		return(tmp);
	}

	MapIter &operator--()
	{
		pointer tmp = _elem;

		if (tmp->left == _endlist)
		{
			tmp = _elem->parent;
			while (tmp != _endlist && comp(_elem->_v->first, tmp->_v->first))
				tmp = tmp->parent;
			_elem = tmp;
		}
		else if (tmp == _endlist)
			_elem = _endlist->left;
		else
		{
			tmp = _elem->left;
			while (tmp->right != _endlist)
				tmp = tmp->right;
		}
		return (*this);
	}

	MapIter &operator--(int)
	{
		MapIter tmp(*this);
		operator--();
		return(tmp);
	}

	bool	operator==(const MapIter &it)
	{
		return ((this->_elem == it._elem));
	}

	bool	operator!=(const MapIter &it)
	{
		return ((this->_elem->p != it._elem->p));
	}
};

} // End namespace ft
#endif