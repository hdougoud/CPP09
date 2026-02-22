/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:07:59 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/22 23:52:17 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <exception>
#include <iostream>
#include <stdexcept>
#include <vector>
#include <list>
#include <deque>
#include "../include/color.hpp"
#include "../include/PmergeMe.hpp"

void	checkInput(int ac, char **av, std::string &input);

int main(int ac, char **av)
{
	std::string input;

	try{
		checkInput(ac, av, input);
		PmergeMe<std::vector<int> > vec(input);
		PmergeMe<std::deque<int> > deq(input);
		vec.sort();
		deq.sort();
	}
	catch (std::exception &e) {
		std::cerr << C_RED << e.what() << RESET << std::endl;
		return (1);
	}
	return (0);
}

void	checkInput(int ac, char **av, std::string &input)
{
	std::string errorMsg;

	if (ac < 2)
		throw std::invalid_argument("Please use at least one argument");
	if (ac > 2)
	{
		for (int i = 1; av[i]; i++)
		{
			input += av[i];
			input += " ";
		}
		return ;
	}
	input = av[1];
}
