/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 15:03:42 by ijacquet          #+#    #+#             */
/*   Updated: 2021/11/12 15:03:43 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
# define UTILS_HPP

# include <iostream>
# include <iterator>
# include <sstream>
# include "ReverseIterator.hpp"
# include "RandomIterator.hpp"

namespace ft
{

	template<bool Cond, class E = void>
	struct enable_if {};

	template<class E> 
	struct enable_if<true, E>
	{
		typedef E type;
	};

	template <class I> struct is_integral
	{
		static const bool value = false;
	};

	template <> struct is_integral<bool>
	{
		static const bool value = true;
	};

	template <> struct is_integral<char>
	{
		static const bool value = true;
	};

	template <> struct is_integral<short int>
	{
		static const bool value = true;
	};

	template <> struct is_integral<int>
	{
		static const bool value = true;
	};

	template <> struct is_integral<long int>
	{
		static const bool value = true;
	};

	template <> struct is_integral<long long int>
	{
		static const bool value = true;
	};

	template <> struct is_integral<unsigned char>
	{
		static const bool value = true;
	};

	template <> struct is_integral<unsigned short int>
	{
		static const bool value = true;
	};

	template <> struct is_integral<unsigned int>
	{
		static const bool value = true;
	};

	template <> struct is_integral<unsigned long int>
	{
		static const bool value = true;
	};

	template <> struct is_integral<unsigned long long int>
	{
		static const bool value = true;
	};

	
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || *first2 < *first1)
				return false;
			else if (*first1 < *first2)
				return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2, class Compare>
	bool lexicographical_compare (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, InputIterator2 last2, Compare comp)
	{
		while (first1 != last1)
		{
			if (first2 == last2 || !comp(*first2, *first1)) return false;
			else if (comp(*first1, *first2)) return true;
			++first1; ++first2;
		}
		return (first2 != last2);
	}

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2)
	{
		while (first1 != last1)
		{
			if (!(*first1 == *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	template <class InputIterator1, class InputIterator2, class BinaryPredicate>
	bool equal (InputIterator1 first1, InputIterator1 last1,
		InputIterator2 first2, BinaryPredicate pred)
	{
		while (first1 != last1)
		{
			if (!pred(*first1, *first2))
				return false;
			++first1; ++first2;
		}
		return true;
	}

	typedef size_t										size_type;
	template <class InputIterator>
	size_type	iterator_len(InputIterator first, InputIterator last)
	{
		size_type i = 0;
		while (first != last)
		{
			first++;
			i++;
		}
		return i;
	}

	template <typename T>
	struct node
	{
		node *right;
		node *left;
		node *parent;
		
		T 		tab;

		node()
		:	right(NULL),
			left(NULL),
			parent(NULL)
		{}

		node(T v, node *nxt = NULL, node *prv = NULL)
		:	right(nxt),
			left(prv),
			tab(v)
		{}
	};

	template<typename T>
	node<T>	*minValueNode(node<T>	*node)
	{
		while (node && node->left != NULL)
			node = node->left;
		return node;
	}

	template<typename T>
	node<T>	*maxValueNode(node<T>	*node)
	{
		while (node && node->right != NULL)
			node = node->right;
		return node;
	}

	template <class T1, class T2> struct pair
	{
		typedef T1	first_type;
		typedef T2	second_type;

		first_type	first;
		second_type	second;

		pair(void) : first(), second()
		{
		}

		template<class U, class V>
		pair(const pair<U,V>& pr) : first(pr.first), second(pr.second)
		{
		}

		pair(const first_type& a, const second_type& b) : first(a), second(b)
		{
		}

		pair& operator=(const pair& pr)
		{
			first = pr.first;
			second = pr.second;
			return *this;
		}
	};

template <class T1, class T2>
bool operator==(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
	return (p1.first == p2.first && p1.second == p2.second);
}

template <class T1, class T2>
bool operator!=(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
	return (p1.first == p2.first && p1.second == p2.second);
}

template <class T1, class T2>
bool operator<(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
	return (p1.first < p2.first && p1.second < p2.second); 
}

template <class T1, class T2>
bool operator<=(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
	return (p1.first <= p2.first && p1.second <= p2.second);
}

template <class T1, class T2>
bool operator>(const pair<T1,T2>& p1, const pair<T1,T2>& p2) 
{
	return (p1.first > p2.first && p1.second > p2.second);
}

template <class T1, class T2>
bool operator>=(const pair<T1,T2>& p1, const pair<T1,T2>& p2)
{
	return (p1.first >= p2.first && p1.second >= p2.second);
}

template <class T1,class T2>
pair<T1,T2> make_pair (T1 x, T2 y)
{
	return (pair<T1,T2>(x,y));
}

}

#endif