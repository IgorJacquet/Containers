/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_map.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:33:45 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/18 11:33:45 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"
#include <map>

/*
** constructor copy etc
*/

template <class Key, class Val>
void print_map_values(ft::map<Key, Val> &m, std::string name)
{
	typename ft::map<Key, Val>::iterator it = m.begin();

	std::cout << "     ***** Variable name : " << name << std::endl;
	while (it != m.end())
	{
		std::cout << "Key [" << it->first << "]   <>   Value : |" << it->second << "|" << std::endl;
		++it;
	}
}

template <class Key, class Val>
void print_vraie_map_values(std::map<Key, Val> &m, std::string name)
{
	typename std::map<Key, Val>::iterator it = m.begin();

	std::cout << "     ***** Variable name : " << name << std::endl;
	while (it != m.end())
	{
		std::cout << "Key [" << it->first << "]   <>   Value : |" << it->second << "|" << std::endl;
		++it;
	}
}

void insert_map_values(ft::map<int, std::string> &m, std::map<int, std::string> &m2)
{
	m.insert(ft::pair<int, std::string>(1, "Julou"));
	m.insert(ft::pair<int, std::string>(2, "julou22"));
	m.insert(ft::pair<int, std::string>(6, "six"));
	m.insert(ft::pair<int, std::string>(8, "mathildou"));
	m.insert(ft::pair<int, std::string>(10, "olaaa"));
	m.insert(ft::pair<int, std::string>(7, "bjr"));

	m2.insert(std::pair<int, std::string>(1, "Julou"));
	m2.insert(std::pair<int, std::string>(2, "julou22"));
	m2.insert(std::pair<int, std::string>(6, "six"));
	m2.insert(std::pair<int, std::string>(8, "mathildou"));
	m2.insert(std::pair<int, std::string>(10, "olaaa"));
	m2.insert(std::pair<int, std::string>(7, "bjr"));
}

static bool	check_it(ft::map<int, std::string>::iterator myIt, ft::map<int, std::string>::iterator myEnd, std::map<int, std::string>::iterator realIt)
{
	while (myIt != myEnd)
	{
		if ((*myIt).first != (*realIt).first)
			return (false);
		if ((*myIt).second != (*realIt).second)
			return (false);
		++myIt;
		++realIt;
	}
	return (true);
}

static bool	check_it_rev(ft::map<int, std::string>::reverse_iterator myIt, ft::map<int, std::string>::reverse_iterator myEnd, std::map<int, std::string>::reverse_iterator realIt)
{
	while (myIt != myEnd)
	{
		if ((*myIt).first != (*realIt).first)
			return (false);
		if ((*myIt).second != (*realIt).second)
			return (false);
		++myIt;
		++realIt;
	}
	return (true);
}

void    test_map_construct()
{
	print_title("Constructors");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	check("Constructor empty", (my1 == real1));
	insert_map_values(my1, real1);

	ft::map<int, std::string>	my2(my1.begin(), my1.end());
	std::map<int, std::string>	real2(real1.begin(), real1.end());
	check("Constructor range", (my2 == real2));
	
	ft::map<int, std::string>	my3(my2);
	std::map<int, std::string>	real3(real2);
	check("Constructor copy", (my3 == real3));

	ft::map<int, std::string>	my4 = my2;
	std::map<int, std::string>	real4 = real2;
	check("Constructor assignation", (my4 == real4));

	my1.insert(ft::pair<int, std::string>(42, "Julou2"));
	real1.insert(std::pair<int, std::string>(42, "Julou2"));
	my4 = my1;
	real4 = real1;
	check("Assignation", (my4 == real4));
}

void	test_map_iterators() // A terminer
{
	print_title("Iterators");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	ft::map<int, std::string>::iterator myIt = my1.begin();
	std::map<int, std::string>::iterator realIt = real1.begin();
	check("Iterator empty", check_it(myIt, my1.end(), realIt));

	insert_map_values(my1, real1);
	myIt = my1.begin();
	realIt = real1.begin();
	check("Iterator", check_it(myIt, my1.end(), realIt));

	ft::map<int, std::string>::reverse_iterator myItr = my1.rbegin();
	std::map<int, std::string>::reverse_iterator realItr = real1.rbegin();
	check("Iterator reverse", check_it_rev(myItr, my1.rend(), realItr));

	const ft::map<int, std::string>	my2(my1.begin(), my1.end());
	const std::map<int, std::string> real2(real1.begin(), real1.end());
	
	ft::map<int, std::string>::const_iterator myItc = my2.begin();
	ft::map<int, std::string>::const_iterator myItce = my2.end();
	std::map<int, std::string>::const_iterator realItc = real2.begin();

	bool ret = true;
	while (myItc != myItce)
	{
		if ((*myItc).second != (*realItc).second)
			ret = false;
		if ((*myItc).first != (*realItc).first)
			ret = false;
		++myItc;
		++realItc;
	}
	check("Iterator const", ret);

	ft::map<int, std::string>::const_reverse_iterator myItrc = my2.rbegin();
	ft::map<int, std::string>::const_reverse_iterator myItrce = my2.rend();
	std::map<int, std::string>::const_reverse_iterator realItrc = real2.rbegin();
	ret = true;
	while (myItrc != myItrce)
	{
		if ((*myItrc).second != (*realItrc).second)
			ret = false;
		if ((*myItrc).first != (*realItrc).first)
			ret = false;
		++myItrc;
		++realItrc;
	}
	check("Iterator rev const", ret);


}

void	test_map_capacity()
{
	print_title("Capacity");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	check("Empty", my1.empty(), real1.empty());
	check("Size", my1.size(), real1.size());

	insert_map_values(my1, real1);
	check("Empty", my1.empty(), real1.empty());
	check("Size", my1.size(), real1.size());
}

void	test_map_elements_access()
{
	print_title("Element access");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	insert_map_values(my1, real1);
	check("[1]", my1[1], real1[1]);
	check("[2]", my1[2], real1[2]);
	check("[10]", my1[10], real1[10]);
	check("[10] = 'test'", (my1[1] = "test"), (real1[1] = "test"));
	my1[53] = "cinquante trois";
	real1[53] = "cinquante trois";
	check("[] = val", (my1 == real1));
}

void	test_map_insert()
{
	print_title("Insert");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	insert_map_values(my1, real1);
	check("Insert", (my1 == real1));
	check("Insert return value", (my1.insert(ft::pair<int, std::string>(19, "Julou2"))).second, (real1.insert(std::pair<int, std::string>(19, "Julou2"))).second);
	
	ft::map<int, std::string>::iterator myIt = my1.begin();
	std::map<int, std::string>::iterator realIt = real1.begin();
	++myIt;
	++realIt;
	++myIt;
	++realIt;
	my1.insert(myIt, ft::pair<int, std::string>(42, "Julou29"));
	real1.insert(realIt, std::pair<int, std::string>(42, "Julou29"));
	check("Insert position", (my1 == real1));
	check("Insert return value", (my1.insert(myIt, ft::pair<int, std::string>(101, "julou100")))->second, (real1.insert(realIt, std::pair<int, std::string>(101, "julou100")))->second);

	ft::map<int, std::string>	my2;
	std::map<int, std::string>	real2;

	my2.insert(my1.begin(), my1.begin());
	real2.insert(real1.begin(), real1.begin());
	check("Insert range", (my2 == real2));
}

void 	test_map_erase()
{
	print_title("Erase");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	insert_map_values(my1, real1);
	my1.erase(1);
	real1.erase(1);
	check("Erase value", (my1 == real1));

	my1.erase(6);
	real1.erase(6);
	check("Erase value", (my1 == real1));

	my1.erase(1);
	real1.erase(1);
	check("Erase already erased", (my1 == real1));

	ft::map<int, std::string>	my2;
	std::map<int, std::string>	real2;

	insert_map_values(my2, real2);
	ft::map<int, std::string>::iterator myIt = my2.begin();
	std::map<int, std::string>::iterator realIt = real2.begin();
	++myIt;
	++realIt;

	my2.erase(myIt);
	real2.erase(realIt);
	check("Erase position", (my2 == real2));

	my2.erase(my2.begin(), my2.end());
	real2.erase(real2.begin(), real2.end());
	check("Erase range", (my2 == real2));
}

void	test_map_swap()
{
	print_title("Swap");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;
	ft::map<int, std::string>	my2;
	std::map<int, std::string>	real2;

	my1.swap(my2);
	real1.swap(real2);
	check("Swap empty", (my1 == real1));
	check("Swap empty", (my2 == real2));
	my1.swap(my2);
	real1.swap(real2);
	check("Swap empty", (my1 == real1));
	check("Swap empty", (my2 == real2));

	insert_map_values(my1, real1);
	my1.swap(my2);
	real1.swap(real2);
	check("Swap first empty", (my1 == real1));
	check("Swap first empty", (my2 == real2));
	my1.swap(my2);
	real1.swap(real2);
	check("Swap first empty", (my1 == real1));
	check("Swap first empty", (my2 == real2));

	insert_map_values(my2, real2);
	my1.swap(my2);
	real1.swap(real2);
	check("Swap", (my1 == real1));
	check("Swap", (my2 == real2));
	my1.swap(my2);
	real1.swap(real2);
	check("Swap", (my1 == real1));
	check("Swap", (my2 == real2));
}

void	test_map_clear()
{
	print_title("Clear");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	my1.clear();
	real1.clear();
	check("Clear empty", (my1 == real1));

	insert_map_values(my1, real1);
	my1.clear();
	real1.clear();
	check("Clear", (my1 == real1));

	my1.clear();
	real1.clear();
	check("Clear re empty", (my1 == real1));
}

void	test_map_observers()
{
	print_title("Observers");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	my1[1] = "un";
	my1[2] = "deux";
	my1[3] = "trois";
	my1[4] = "quat";
	real1[1] = "un";
	real1[2] = "deux";
	real1[3] = "trois";
	real1[4] = "quat";

	ft::map<int, std::string>::key_compare myComp = my1.key_comp();
	std::map<int, std::string>::key_compare realComp = real1.key_comp();

	check("Key_compare", myComp(1, 2), realComp(1, 2));
	check("Value comp", my1.value_comp()(ft::pair<int, std::string>(1, "Julouu"), ft::pair<int, std::string>(2, "Julo")), 
		real1.value_comp()(std::pair<int, std::string>(1, "Julouu"), std::pair<int, std::string>(2, "Julo")));
}

void	test_map_operations()
{
	print_title("map observations");
	ft::map<int, std::string>	my1;
	std::map<int, std::string>	real1;

	insert_map_values(my1, real1);
	check("Find", (my1.find(1))->second, (real1.find(1))->second);
	check("Find", (my1.find(6))->second, (real1.find(6))->second);
	check("Find not found", (my1.find(30) == my1.end()), (real1.find(30) == real1.end()));
	
	check("count", my1.count(1), real1.count(1));
	check("count", my1.count(2), real1.count(2));
	check("count not found", my1.count(53), real1.count(53));

	check("Lower bound", my1.lower_bound(7)->second, real1.lower_bound(7)->second);
	check("Lower bound", my1.lower_bound(2)->second, real1.lower_bound(2)->second);
	check("Lower bound not found", (my1.lower_bound(40) == my1.end()), (real1.lower_bound(40) == real1.end()));

	check("Upper bound", my1.upper_bound(7)->second, real1.upper_bound(7)->second);
	check("Upper bound", my1.upper_bound(2)->second, real1.upper_bound(2)->second);
	check("Upper bound not found", (my1.upper_bound(40) == my1.end()), (real1.upper_bound(40) == real1.end()));

	check("Equal range", my1.equal_range(7).second->second, real1.equal_range(7).second->second);
	check("Equal range", my1.equal_range(2).second->second, real1.equal_range(2).second->second);

	ft::pair<ft::map<int, std::string>::iterator, ft::map<int, std::string>::iterator> ret = my1.equal_range(40);
	std::pair<std::map<int, std::string>::iterator, std::map<int, std::string>::iterator> ret2 = real1.equal_range(40);
	check("Equal range not found", (ret.first == ret.second), (ret2.first == ret2.second));
}

void	test_map()
{
	print_header("MAP");
	
	test_map_construct();
	P("");
	test_map_iterators();
	P("");
	test_map_capacity();
	P("");
	test_map_elements_access();
	P("");
	test_map_insert();
	P("");
	test_map_erase();
	P("");
	test_map_swap();
	P("");
	test_map_clear();
	P("");
	test_map_observers();
	P("");
	test_map_operations();
	P("");
}