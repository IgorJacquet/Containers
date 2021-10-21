/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:33:40 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/18 11:33:40 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <list>

template <class T>
void	print_list(ft::list<T> &list, std::string name)
{
	ft::list<int>::iterator first = list.begin();
	ft::list<int>::iterator last = list.end();
	size_t 					i = 0;

	std::cout << name << "|" << std::endl;
	while (first != last)
	{
		std::cout << "Val : " << i << " --> " << *first << std::endl;
		++i;
		++first;
	}
	std::cout << "|" << std::endl << std::endl;
}

template <class T>
void	print_vraie_list(std::list<T> &list, std::string name)
{
	std::list<int>::iterator first = list.begin();
	std::list<int>::iterator last = list.end();
	size_t 					i = 0;

	std::cout << name << "|" << std::endl;
	while (first != last)
	{
		std::cout << "Val : " << i << " --> " << *first << std::endl;
		++i;
		++first;
	}
	std::cout << "|" << std::endl << std::endl;
}

template <class T>
void	basic_values(ft::list<T> &l1, ft::list<T> &l2)
{
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);

	l2.push_back(103);
	l2.push_back(-5);
	l2.push_back(42);
	l2.push_back(19);
}

template <class T>
void	basic_values(ft::list<T> &l1, std::list<T> &l2)
{
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);

	l2.push_back(1);
	l2.push_back(2);
	l2.push_back(3);
	l2.push_back(4);
	l2.push_back(5);
}

template <class T>
void	basic_values(ft::list<T> &l1)
{
	l1.push_back(1);
	l1.push_back(2);
	l1.push_back(3);
	l1.push_back(4);
	l1.push_back(5);
}

template <class T>
void	reset(ft::list<T> &l1, ft::list<T> &l2)
{
	l1.clear();
	l2.clear();
	basic_values(l1, l2);
}

void	test_list_constructor()
{
	print_title("Constructors");
	
	ft::list<int>	my1;
	std::list<int>	real1;
	check("Empty constructor", (my1 == real1));

	ft::list<int>	my2((size_t)9, 19);
	std::list<int>	real2((size_t)9, 19);
	check("Fill constructor", (my2 == real2));

	my2.clear();
	my2.push_back(1);
	my2.push_back(2);
	my2.push_back(3);
	my2.push_back(4);
	real2.clear();
	real2.push_back(1);
	real2.push_back(2);
	real2.push_back(3);
	real2.push_back(4);
	ft::list<int>	my3(my2.begin(), my2.end());
	std::list<int>	real3(real2.begin(), real2.end());
	check("Range constructor", (my3 == real3));

	ft::list<int>	my4(my3);
	std::list<int>	real4(real3);
	check("Copy constructor", (my4 == real4));

	ft::list<int>	my5 = my4;
	std::list<int>	real5 = real4;
	check("Operator =", (my5 == real5));

	my4 = my3;
	real4 = real3;
	check("Operator =", (my4 == real4));
}

void	test_list_iterators()
{
	print_title("Iterators / Capacity / Element Access"); 
	ft::list<int>	my1;
	std::list<int>	real1;
	check("Empty()", my1.empty(), real1.empty());
	check("Size()", my1.size(), real1.size());
	basic_values(my1, real1);
	check("Empty()", my1.empty(), real1.empty());
	check("Size()", my1.size(), real1.size());

	bool test = true;
	ft::list<int>::iterator myIt = my1.begin();
	std::list<int>::iterator realIt = real1.begin();
	while (myIt != my1.end())
	{
		if (*myIt != *realIt)
			test = false;
		++myIt;
		++realIt;
	}
	check("Begin() / End()", test);
	
	test = true;
	ft::list<int>::reverse_iterator myItR = my1.rbegin();
	std::list<int>::reverse_iterator realItR = real1.rbegin();
	while (myItR != my1.rend())
	{
		if (*myItR != *realItR)
			test = false;
		++myItR;
		++realItR;
	}
	check("RBegin() / REnd()", test);

	check("Front()", my1.front(), real1.front());
	check("Back()", my1.back(), real1.back());

}

void	test_list_const_iterators()
{
	print_title("Const Iterators"); 
	const ft::list<int>	my1((size_t)2, 19);
	const std::list<int>	real1((size_t)2, 19);

	bool test = true;
	ft::list<int>::const_iterator myIt = my1.begin();
	//*myIt = 2;
	std::list<int>::const_iterator realIt = real1.begin();
	//*realIt = 2;
	while (myIt != my1.end())
	{
		if (*myIt != *realIt)
			test = false;
		++myIt;
		++realIt;
	}
	check("Begin() / End()", test);
	
	test = true;
	ft::list<int>::const_reverse_iterator myItR = my1.rbegin();
	std::list<int>::const_reverse_iterator realItR = real1.rbegin();
	while (myItR != my1.rend())
	{
		if (*myItR != *realItR)
			test = false;
		++myItR;
		++realItR;
	}
	check("RBegin() / REnd()", test);
}

void	test_list_assign()
{
	print_title("Assign");
	ft::list<int>	my1;
	std::list<int>	real1;
	basic_values(my1, real1);

	ft::list<int>	my2;
	std::list<int>	real2;
	my2.assign(my1.begin(), my1.end());
	real2.assign(real1.begin(), real1.end());
	check("assign iterators", (my2 == real2));

	ft::list<int>::iterator myIt = my1.begin();
	std::list<int>::iterator realIt = real1.begin();
	++myIt;
	++realIt;
	++myIt;
	++realIt;
	my2.assign(myIt, my1.end());
	real2.assign(realIt, real1.end());
	check("assign iterators", (my2 == real2));

	ft::list<int>	my3;
	std::list<int>	real3;
	my3.assign((size_t)10, 19);
	real3.assign((size_t)10, 19);
	check("assign values", (my3 == real3));
	my3.assign((size_t)5, 42);
	real3.assign((size_t)5, 42);
	check("assign values", (my3 == real3));
}

void	test_list_push()
{
	print_title("Push");
	ft::list<int>	my1;
	std::list<int>	real1;

	my1.push_front(1);
	real1.push_front(1);
	check("push_front(1)", (my1 == real1));
	my1.push_front(2);
	real1.push_front(2);
	check("push_front(2)", (my1 == real1));

	my1.pop_front();
	real1.pop_front();
	check("pop_front()", (my1 == real1));
	my1.pop_front();
	real1.pop_front();
	check("pop_front()", (my1 == real1));

	my1.push_back(3);
	real1.push_back(3);
	check("push_back(3)", (my1 == real1));
	my1.push_back(4);
	real1.push_back(4);
	check("push_back(4)", (my1 == real1));

	my1.pop_back();
	real1.pop_back();
	check("pop_back()", (my1 == real1));
	my1.pop_back();
	real1.pop_back();
	check("pop_back()", (my1 == real1));
}

void	test_list_insert()
{
	print_title("Insert");
	//test1
	ft::list<int>	my1;
	std::list<int>	real1;

	ft::list<int>::iterator myIt = my1.begin();
	std::list<int>::iterator realIt = real1.begin();

	my1.insert(myIt, 19);
	real1.insert(realIt, 19);
	my1.insert(myIt, 42);
	real1.insert(realIt, 42);
	check("insert value begin", (my1 == real1));

	my1.insert(my1.end(), 91);
	real1.insert(real1.end(), 91);
	my1.insert(my1.end(), 24);
	real1.insert(real1.end(), 24);
	check("insert value end", (my1 == real1));

	myIt = my1.begin();
	realIt = real1.begin();
	++myIt;
	++realIt;
	my1.insert(myIt, 192);
	real1.insert(realIt, 192);
	check("insert value inside", (my1 == real1));

	//test2
	ft::list<int>	my2;
	std::list<int>	real2;

	ft::list<int>::iterator myIt2 = my2.begin();
	std::list<int>::iterator realIt2 = real2.begin();

	my2.insert(myIt2, (size_t)3, 19);
	real2.insert(realIt2, (size_t)3, 19);
	my2.insert(myIt2, (size_t)3, 42);
	real2.insert(realIt2, (size_t)3, 42);
	check("insert size value begin", (my2 == real2));

	my2.insert(my2.end(), (size_t)3, 91);
	real2.insert(real2.end(), (size_t)3, 91);
	my2.insert(my2.end(), (size_t)3, 24);
	real2.insert(real2.end(), (size_t)3, 24);
	check("insert size value end", (my2 == real2));

	++myIt2;
	++realIt2;
	my2.insert(myIt2, 192);
	real2.insert(realIt2, 192);
	check("insert size value inside", (my2 == real2));

	//test3
	ft::list<int>	my3;
	std::list<int>	real3;

	ft::list<int>::iterator myIt3 = my3.begin();
	std::list<int>::iterator realIt3 = real3.begin();

	my3.insert(myIt3, my2.begin(), my2.end());
	real3.insert(realIt3, real2.begin(), real2.end());
	check("insert iterators", (my3 == real3));

	myIt3 = my3.begin();
	realIt3 = real3.begin();
	++myIt3;
	++realIt3;
	my3.insert(myIt3, my2.begin(), my2.end());
	real3.insert(realIt3, real2.begin(), real2.end());
	check("insert iterators", (my3 == real3));
}

void	test_list_erase()
{
	print_title("Erase");
	ft::list<int>	my1;
	std::list<int>	real1;
	basic_values(my1, real1);

	my1.erase(my1.begin());
	real1.erase(real1.begin());
	check("erase begin()", (my1 == real1));

	ft::list<int>::iterator myIt = my1.begin();
	std::list<int>::iterator realIt = real1.begin();
	++myIt;
	++realIt;
	my1.erase(myIt);
	real1.erase(realIt);
	check("erase iterator", (my1 == real1));

	my1.erase(my1.begin(), my1.end());
	real1.erase(real1.begin(), real1.end());
	check("erase range", (my1 == real1));
}

void	test_list_swap()
{
	print_title("Swap / Swap extern");
	ft::list<int>	my1;
	std::list<int>	real1;
	ft::list<int>	my2;
	std::list<int>	real2;

	my1.swap(my2);
	real1.swap(real2);
	check("swap", (my1 == real1));
	check("swap", (my2 == real2));

	ft::swap(my1, my2);
	std::swap(real1, real2);

	check("swap extern", (my1 == real1));
	check("swap extern", (my2 == real2));

	basic_values(my1, real1);
	my2.push_back(19);
	my2.push_back(42);
	my2.push_back(101);
	my2.push_back(24);
	my2.push_back(91);
	real2.push_back(19);
	real2.push_back(42);
	real2.push_back(101);
	real2.push_back(24);
	real2.push_back(91);

	my1.swap(my2);
	real1.swap(real2);
	check("swap", (my1 == real1));
	check("swap", (my2 == real2));

	ft::swap(my1, my2);
	std::swap(real1, real2);
	check("swap extern", (my1 == real1));
	check("swap extern", (my2 == real2));
}

void	test_list_resize()
{
	print_title("Resize");
	ft::list<int>	my1;
	std::list<int>	real1;

	my1.resize(0);
	real1.resize(0);
	check("resize(0)", (my1 == real1));

	my1.resize(9);
	real1.resize(9);
	check("resize(9)", (my1 == real1));

	my1.resize(9, 19);
	real1.resize(9, 19);
	check("resize(9, 19)", (my1 == real1));

	ft::list<int>	my2;
	std::list<int>	real2;
	basic_values(my2, real2);

	my2.resize(4, 10);
	real2.resize(4, 10);
	check("resize(4, 10)", (my2 == real2));

	my2.resize(9, 19);
	real2.resize(9, 19);
	check("resize(9, 19)", (my2 == real2));
}

void	test_list_clear()
{
	print_title("clear");
	ft::list<int>	my1;
	std::list<int>	real1;

	my1.clear();
	real1.clear();
	check("clear void", (my1 == real1));

	basic_values(my1, real1);
	my1.clear();
	real1.clear();
	check("clear", (my1 == real1));
}

void	test_list_splice()
{
	print_title("Splice");
	ft::list<int>	my1;
	std::list<int>	real1;
	ft::list<int>	my2;
	std::list<int>	real2;

	my2.splice(my2.begin(), my1);
	real2.splice(real1.begin(), real1);
	check("Splice empty 2", (my2 == real2));
	check("Splice empty 1", (my1 == real1));

	basic_values(my1, real1);
	my2.splice(my2.begin(), my1);
	real2.splice(real2.begin(), real1);
	check("Splice first empty 2", (my2 == real2));
	check("Splice first empty 1", (my1 == real1));
	
	ft::list<int>	my3;
	std::list<int>	real3;
	basic_values(my3, real3);
	ft::list<int>::iterator myIt = my3.begin();
	std::list<int>::iterator realIt = real3.begin();
	++myIt;
	++realIt;
	++myIt;
	++realIt;
	my3.splice(myIt, my1);
	real3.splice(realIt, real1);
	check("Splice fill 3", (my3 == real3));
	check("Splice fill 1", (my1 == real1));

	my1.clear();
	real1.clear();
	myIt = ++(my3.begin());
	realIt = ++(real3.begin());
	my1.splice(my1.begin(), my3, myIt);

	real1.splice(real1.begin(), real3, realIt);
	check("Splice one iter 1", (my1 == real1));
	check("Splice one iter 3", (my3 == real3));

	myIt = ++(my3.begin());
	realIt = ++(real3.begin());
	++myIt;
	++realIt;
	my1.splice(my1.begin(), my3, myIt);
 	real1.splice(real1.begin(), real3, realIt);
 	check("Splice one iter 1", (my1 == real1));
	check("Splice one iter 3", (my3 == real3));

	myIt = my2.begin();
	realIt = real2.begin();
	my1.splice(++(my1.begin()), my2, myIt);
 	real1.splice(++(real1.begin()), real2, realIt);
	check("Splice range iter 1", (my1 == real1));
	check("Splice range iter 2", (my2 == real2));

}

void 	test_list_remove()
{
	print_title("Splice");
	ft::list<int>	my1;
	std::list<int>	real1;

	basic_values(my1, real1);
	my1.push_back(19);
	real1.push_back(19);
	my1.push_back(19);
	real1.push_back(19);
	my1.push_back(42);
	real1.push_back(42);

	my1.remove(12);
	real1.remove(12);
	check("Remove", (my1 == real1));
	my1.remove(19);
	real1.remove(19);
	check("Remove", (my1 == real1));
	my1.remove(1);
	real1.remove(1);
	check("Remove", (my1 == real1));
}

void	test_list_remove_if()
{
	print_title("Remove If");
	ft::list<int>	my1;
	std::list<int>	real1;

	my1.remove_if(test_pair);
	real1.remove_if(test_pair);
	check("Remove if, empty", (my1 == real1));

	basic_values(my1, real1);
	my1.remove_if(test_pair);
	real1.remove_if(test_pair);
	check("Remove if", (my1 == real1));

	basic_values(my1, real1);
	my1.remove_if(pred);
	real1.remove_if(pred);
	check("Remove if", (my1 == real1));
}

void	test_list_unique()
{
	print_title("Unique");
	ft::list<int>	my1;
	std::list<int>	real1;

	my1.unique();
	real1.unique();
	check("unique empty", (my1 == real1));
	my1.unique(compare_supEq);
	real1.unique(compare_supEq);
	check("unique fct empty", (my1 == real1));
	
	basic_values(my1, real1);
	my1.push_back(-1);
	my1.push_back(19);
	my1.push_back(19);
	my1.push_front(0);
	my1.push_front(0);
	my1.push_front(1);
	my1.push_front(1);
	real1.push_back(-1);
	real1.push_back(19);
	real1.push_back(19);
	real1.push_front(0);
	real1.push_front(0);
	real1.push_front(1);
	real1.push_front(1);

	my1.unique();
	real1.unique();
	check("unique", (my1 == real1));

	my1.push_back(-1);
	my1.push_back(19);
	my1.push_back(19);
	my1.push_front(0);
	my1.push_front(0);
	my1.push_front(1);
	my1.push_front(1);
	real1.push_back(-1);
	real1.push_back(19);
	real1.push_back(19);
	real1.push_front(0);
	real1.push_front(0);
	real1.push_front(1);
	real1.push_front(1);
	my1.unique(compare_supEq);
	real1.unique(compare_supEq);
	check("unique", (my1 == real1));

}

void	test_list_merge()
{
	print_title("Merge");
	ft::list<int>	my1;
	std::list<int>	real1;
	ft::list<int>	my2;
	std::list<int>	real2;

	my1.merge(my2);
	real1.merge(real2);
	check("merge empty", (my1 == real1));
	check("merge empty", (my2 == real2));	

	basic_values(my2, real2);
	my1.merge(my2);
	real1.merge(real2);
	check("merge first empty", (my1 == real1));
	check("merge first empty", (my2 == real2));

	ft::list<int>	my3;
	std::list<int>	real3;
	basic_values(my3, real3);
	my1.merge(my3);
	real1.merge(real3);
	check("merge", (my1 == real1));
	check("merge", (my3 == real3));

	ft::list<int>	my4;
	std::list<int>	real4;
	ft::list<int>	my5;
	std::list<int>	real5;

	my4.merge(my5, compare_infEq);
	real4.merge(real5, compare_infEq);
	check("merge fct empty", (my4 == real4));
	check("merge fct empty", (my5 == real5));

	basic_values(my5, real5);
	my4.merge(my5, compare_infEq);
	real4.merge(real5, compare_infEq);
	check("merge fct first empty", (my4 == real4));
	check("merge fct first empty", (my5 == real5));

	ft::list<int>	my6;
	std::list<int>	real6;
	basic_values(my6, real6);
	my4.merge(my6, compare_infEq);
	real4.merge(real6, compare_infEq);
	check("merge fct", (my4 == real4));
	check("merge fct", (my6 == real6));

	basic_values(my6, real6);
	my4.merge(my6, compare_sup);
	real4.merge(real6, compare_sup);
	check("merge fct", (my4 == real4));
	check("merge fct", (my6 == real6));

	basic_values(my6, real6);
	my4.merge(my6, compare_Eq);
	real4.merge(real6, compare_Eq);
	check("merge fct", (my4 == real4));
	check("merge fct", (my6 == real6));
}

void	test_list_sort()
{
	print_title("Sort");
	ft::list<int>	my1;
	std::list<int>	real1;

	my1.sort();
	real1.sort();
	check("sort empty", (my1 == real1));
	
	basic_values(my1, real1);
	my1.sort();
	real1.sort();
	check("sort already sorted", (my1 == real1));

	my1.push_front(19);
	my1.push_front(42);
	my1.push_front(-3);
	my1.push_back(42);
	my1.push_back(19);
	my1.push_back(101);
	real1.push_front(19);
	real1.push_front(42);
	real1.push_front(-3);
	real1.push_back(42);
	real1.push_back(19);
	real1.push_back(101);
	my1.sort();
	real1.sort();
	check("sort", (my1 == real1));

	ft::list<int>	my2;
	std::list<int>	real2;

	my2.sort(compare_supEq);
	real2.sort(compare_supEq);
	check("sort fct empty", (my2 == real2));

	basic_values(my2, real2);
	my2.sort(compare_supEq);
	real2.sort(compare_supEq);
	check("sort fct already sorted", (my2 == real2));

	my2.push_front(19);
	my2.push_front(42);
	my2.push_front(-3);
	my2.push_back(42);
	my2.push_back(19);
	my2.push_back(101);
	real2.push_front(19);
	real2.push_front(42);
	real2.push_front(-3);
	real2.push_back(42);
	real2.push_back(19);
	real2.push_back(101);
	my2.sort();
	real2.sort();
	check("sort fct", (my2 == real2));
}

void	test_list_reverse()
{
	print_title("Reverse");
	ft::list<int>	my1;
	std::list<int>	real1;

	my1.reverse();
	real1.reverse();
	check("reverse empty", (my1 == real1));

	basic_values(my1, real1);
	my1.reverse();
	real1.reverse();
	check("reverse", (my1 == real1));

	my1.push_front(19);
	real1.push_front(19);
	my1.reverse();
	real1.reverse();
	check("reverse", (my1 == real1));
}

void	test_list_modifiers()
{
	//print_title("Modifiers");
	test_list_assign();
	P("");
	test_list_push();
	P("");
	test_list_insert();
	P("");
	test_list_erase();
	P("");
	test_list_swap();
	P("");
	test_list_resize();
	P("");
	test_list_clear();
}

void	test_list_operations()
{
	test_list_splice();
	P("");
	test_list_remove();
	P("");
	test_list_remove_if();
	P("");
	test_list_unique();
	P("");
	test_list_merge();
	P("");
	test_list_sort();
	P("");
	test_list_reverse();

}

void	test_list_operators()
{
	print_title("Relational operators");
	ft::list<int>	my1;
	std::list<int>	real1;
	ft::list<int>	my2;
	std::list<int>	real2;

	check("Operator ==", (my1 == my2), (real1 == real2));
	check("Operator !=", (my1 != my2), (real1 != real2));
	check("Operator <=", (my1 <= my2), (real1 <= real2));
	check("Operator <", (my1 < my2), (real1 < real2));
	check("Operator >=", (my1 >= my2), (real1 >= real2));
	check("Operator >", (my1 > my2), (real1 > real2));

	basic_values(my1, real1);
	basic_values(my2, real2);
	check("Operator ==", (my1 == my2), (real1 == real2));
	check("Operator !=", (my1 != my2), (real1 != real2));
	check("Operator <=", (my1 <= my2), (real1 <= real2));
	check("Operator <", (my1 < my2), (real1 < real2));
	check("Operator >=", (my1 >= my2), (real1 >= real2));
	check("Operator >", (my1 > my2), (real1 > real2));

	my1.push_back(19);
	real1.push_back(19);
	check("Operator ==", (my1 == my2), (real1 == real2));
	check("Operator !=", (my1 != my2), (real1 != real2));
	check("Operator <=", (my1 <= my2), (real1 <= real2));
	check("Operator <", (my1 < my2), (real1 < real2));
	check("Operator >=", (my1 >= my2), (real1 >= real2));
	check("Operator >", (my1 > my2), (real1 > real2));
}

void test_list()
{
	print_header("LIST");
	test_list_constructor();
	P("");
	test_list_iterators();
	P("");
	test_list_const_iterators();
	P("");
	test_list_modifiers();
	P("");
	test_list_operations();
	P("");
	test_list_operators();
	P("");

}
