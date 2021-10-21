/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_queue.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ijacquet <ijacquet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 11:33:51 by ijacquet          #+#    #+#             */
/*   Updated: 2021/10/18 11:33:52 by ijacquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tester.hpp"

void	test_queue_operators()
{
	print_title("Relational operators");
	ft::queue<int> my1;
	std::queue<int> real1;
	ft::queue<int> my2;
	std::queue<int> real2;

	check("Operator ==", (my1 == my2), (real1 == real2));
	check("Operator !=", (my1 != my2), (real1 != real2));
	check("Operator <=", (my1 <= my2), (real1 <= real2));
	check("Operator <", (my1 < my2), (real1 < real2));
	check("Operator >=", (my1 >= my2), (real1 >= real2));
	check("Operator >", (my1 > my2), (real1 > real2));
	
	my1.push(19);
	my1.push(42);
	my2.push(19);
	my2.push(42);
	real1.push(19);
	real1.push(42);
	real2.push(19);
	real2.push(42);
	check("Operator ==", (my1 == my2), (real1 == real2));
	check("Operator !=", (my1 != my2), (real1 != real2));
	check("Operator <=", (my1 <= my2), (real1 <= real2));
	check("Operator <", (my1 < my2), (real1 < real2));
	check("Operator >=", (my1 >= my2), (real1 >= real2));
	check("Operator >", (my1 > my2), (real1 > real2));

	my1.push(19);
	my1.push(42);
	real1.push(19);
	real1.push(42);
	check("Operator ==", (my1 == my2), (real1 == real2));
	check("Operator !=", (my1 != my2), (real1 != real2));
	check("Operator <=", (my1 <= my2), (real1 <= real2));
	check("Operator <", (my1 < my2), (real1 < real2));
	check("Operator >=", (my1 >= my2), (real1 >= real2));
	check("Operator >", (my1 > my2), (real1 > real2));


}

void	test_queue_member_fct()
{
	print_title("Constructor");

	ft::list<int> lmy1((size_t)5, 19);
	std::deque<int> lreal1((size_t)5, 19);
	
	lmy1.push_front(42);
	lmy1.push_back(12);
	lreal1.push_front(42);
	lreal1.push_back(12);
	
	ft::queue<int> my1(lmy1);
	std::queue<int> real1(lreal1);
	check("Constructor from parent", (my1 == real1));

	ft::queue<int> my2;
	std::queue<int> real2;
	check("Constructor empty", (my2 == real2));

	P("");
	print_title("Member functions");
	P("Empty/Size/Front/Back are checked in every test");
	my2.push(1);
	real2.push(1);
	check("Push", (my2 == real2));
	my2.push(42);
	real2.push(42);
	my2.push(19);
	real2.push(19);
	check("Push", (my2 == real2));
	my2.pop();
	real2.pop();
	check("Pop", (my2 == real2));
	my2.push(19);
	real2.push(19);
	check("Push", (my2 == real2));
	my2.pop();
	real2.pop();
	check("Pop", (my2 == real2));
	my2.pop();
	real2.pop();
	check("Pop", (my2 == real2));

	my1.push(1);
	real1.push(1);
	check("Push", (my2 == real2));
	my1.push(42);
	real1.push(42);
	my1.push(19);
	real1.push(19);
	check("Push", (my2 == real2));
	my1.pop();
	real1.pop();
	my1.pop();
	real1.pop();
	my1.pop();
	real1.pop();
	check("Pop", (my2 == real2));
	
}

void	test_queue()
{
	print_header("QUEUE");
	test_queue_member_fct();
	P("");
	test_queue_operators();
	P("");
}