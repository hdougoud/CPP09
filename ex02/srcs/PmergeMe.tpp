/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:57:36 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/17 14:58:33 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <vector>
#include "../include/color.hpp"

template <typename C>
PmergeMe<C>::PmergeMe()
{
	return ;
}

template <typename C>
PmergeMe<C>::PmergeMe(const std::string &str)
{
	std::vector<int>		temp;

	convertInput(str);
}

template <typename C>
PmergeMe<C>::PmergeMe(const PmergeMe &src) : _container(src._container)
{
	return ;
}

template <typename C>
PmergeMe<C>	&PmergeMe<C>::operator=(const PmergeMe &src)
{
	if (this != &src)
	{
		this->_container = src._container;
	}
	return (*this);
}

template <typename C>
PmergeMe<C>::~PmergeMe()
{
	return ;
}

template <typename C>
void	PmergeMe<C>::convertInput(const std::string &str)
{
	long				converted;
	std::stringstream	ss(str);

	while (ss >> converted)
	{
		//WARN: INT MAX AND INT MIN Dosen't work fix this later !!
		if (converted < 0 || converted >> std::numeric_limits<int>::max())
			throw std::invalid_argument("Error: use only positives numbers");
		this->_container.push_back(converted);
	}
	if (!ss.eof() && ss.fail())
		throw std::invalid_argument("Error: use only numbers");
}

template <typename C>
void	PmergeMe<C>::sort(void)
{

	//--------- DEBUG -----------------//
	std::cout << C_CORAL << "Jacobsthal Suit Test\n"
				<< PmergeMe<C>::calculateJacobsthal(1) << " "
				<< PmergeMe<C>::calculateJacobsthal(2) << " "
				<< PmergeMe<C>::calculateJacobsthal(3) << " "
				<< PmergeMe<C>::calculateJacobsthal(4) << " "
				<< PmergeMe<C>::calculateJacobsthal(5) << " "
				<< PmergeMe<C>::calculateJacobsthal(6) << " "
				<< PmergeMe<C>::calculateJacobsthal(7) << " "
				<< PmergeMe<C>::calculateJacobsthal(8) << " \n" << std::endl;
	//---------------------------------//

	//TODO: ADD TIMER
	std::cout << C_YELLOW << "INPUT\n";
	this->printSequence();
	makePairs(this->_container, 1);
}


template <typename C>
void	PmergeMe<C>::makePairs(C &sequence, int size)
{
	C						main;
	C						pend;
	C						impaire;
	typename C::iterator	it;
	typename C::iterator	blocEnd;

	//TODO: Protect MAX input args
	if (size * 2 > static_cast<int>(sequence.size()))
		return;
	for (it = sequence.begin(); std::distance(it, sequence.end()) >= size * 2; it += 2 * size)
	{
		if (*(it + size - 1) > *(it + size * 2 - 1))
			std::swap_ranges(it, it + size, it + size);
	}

	//--------- DEBUG -----------------//
	std::cout << C_RED << "Impaire\n";
	if (std::distance(it, sequence.end()) >= size)
		impaire.assign(it, it + size);
	for (it = impaire.begin(); it != impaire.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::endl(std::cout);
	this->printSequence();
	//---------------------------------//

	makePairs(sequence, size * 2);
	blocEnd = sequence.begin() + size;
	for (it = sequence.begin(); it < blocEnd; it++)
		main.push_back(*it);
	for (it = sequence.begin() + size; std::distance(it, sequence.end()) >= size;)
	{
		int i = 0;
		while (i++ < size)
			main.push_back(*it++);
		i = 0;
		while (i++ < size && std::distance(it, sequence.end()) >= size)
			pend.push_back(*it++);
	}
	if (!impaire.empty())
	{
		for(it = impaire.begin(); it != impaire.end(); it++)
			pend.push_back(*it);
	}

	PmergeMe<C>::insertPend(main, pend, size);

	this->_container = main;

	//--------- DEBUG -----------------//
	std::cout << C_YELLOW << "\nThe main\n"; 
	for (it = main.begin(); it != main.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << "\nThe pend\n";
	for (it = pend.begin(); it != pend.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << RESET << std::endl;
	//---------------------------------//
}

template <typename C>
void	PmergeMe<C>::printSequence(void) const
{
	typename C::const_iterator it;

	std::cout << C_YELLOW;
	for (it = this->_container.begin(); it != this->_container.end(); it++)
		std::cout << *it << " ";
	std::cout << RESET << std::endl;
}

template <typename C>
void	PmergeMe<C>::insertPend(C &main, C &pend, int blocSize)
{
	int						jacobsthalNb;
	int						pendBlocNb;
	C						winnerList;
	typename C::iterator	it;
	typename C::iterator	low;
	typename C::iterator	high;

	(void) main;
	(void) jacobsthalNb;
	(void) pendBlocNb;
	while (it + 1 != main.end())
	{
		winnerList.push_back(*it);
		it += blocSize;
	}

	jacobsthalNb = PmergeMe<C>::calculateJacobsthal(3) - 1;
	pendBlocNb = pend.size() / blocSize;
	
}

template <typename C>
unsigned int PmergeMe<C>::calculateJacobsthal(unsigned int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return PmergeMe<C>::calculateJacobsthal(n - 1) + 2 * PmergeMe<C>::calculateJacobsthal(n - 2);
}
