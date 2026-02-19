/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:57:36 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/19 16:06:29 by votre_login      ###   ########.fr       */
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
	if (this->_container.size() > static_cast<unsigned long>(std::numeric_limits<int>::max()))
		throw std::invalid_argument("Error: Too much numbers");
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
	std::cout << C_CORAL << "Jacobsthal Suit Test\n";
	for(int i = 3; i < 10; i++)
		std::cout << PmergeMe<C>::calculateJacobsthal(i) << " ";
	std::cout << RESET << std::endl;
	//---------------------------------//

	//--------- DEBUG -----------------//
	std::cout << C_YELLOW << "INPUT\n";
	this->printSequence();
	//---------------------------------//

	//TODO: ADD TIMER
	this->fordJohnson(this->_container, 1);

	//--------- DEBUG -----------------//
	std::cout << C_YELLOW << "\nOUTPUT\n";
	this->printSequence();
	//--------- DEBUG -----------------//
}


template <typename C>
void	PmergeMe<C>::fordJohnson(C &sequence, int size)
{
	C						main;
	C						pend;
	C						impaire;
	C						nonParticipating;
	typename C::iterator	it;

	if (size * 2 > static_cast<int>(sequence.size()))
		return;

	makePairs(sequence, impaire, nonParticipating, size);
	fordJohnson(sequence, size * 2);
	createMainAndPend(sequence, main, pend, impaire, size);
	printDebug(main, pend, impaire, nonParticipating, size); //debug
	insertPend(main, pend, size);

	this->_container = main;
}

template <typename C>
void	PmergeMe<C>::makePairs(C &sequence, C &impaire, C &nonParticipating, int size)
{
	typename C::iterator	it;

	//TODO: Protect MAX input args
	for (it = sequence.begin(); std::distance(it, sequence.end()) >= size * 2; it += 2 * size)
	{
		if (*(it + size - 1) > *(it + size * 2 - 1))
			std::swap_ranges(it, it + size, it + size);
	}
	if (std::distance(it, sequence.end()) >= size)
	{
		impaire.assign(it, it + size);
		it += size; //DEBUG: for printing nonParticipatingArray
	}
	nonParticipating.insert(nonParticipating.begin(), it, sequence.end()); //DEBUG: for printing nonParticipatingArray
}

template <typename C>
void	PmergeMe<C>::createMainAndPend(C &sequence, C &main, C &pend, C &impaire, int size)
{
	typename C::iterator	it;
	typename C::iterator	blocEnd;

	for (it = sequence.begin(); std::distance(it, sequence.end()) >= size; it += size)
	{
			pend.insert(pend.end(), it, it + size);
			it += size;
			main.insert(main.end(), it, it + size);
	}
	if (!impaire.empty())
		pend.insert(pend.end(), impaire.begin(), impaire.end());
}

template <typename C>
void	PmergeMe<C>::printDebug(C &main, C &pend, C &impaire, C &nonParcipating, int size)
{
	typename C::iterator	it;

	std::cout << C_YELLOW << "\nThe main\n"; 
	int i = 0;
	for (it = main.begin(); it != main.end(); it++)
	{
		if (i == 0)
			std::cout << "[ ";
		std::cout << *it << " ";
		if (i++ == size - 1)
		{
			std::cout << "]  ";
			i = 0;
		}
	}

	std::cout << "\nThe pend\n";
	i = 0;
	for (it = pend.begin(); it != pend.end(); it++)
	{
		if (i == 0)
			std::cout << "[ ";
		std::cout << *it << " ";
		if (i++ == size - 1)
		{
			std::cout << "]  ";
			i = 0;
		}
	}

	std::cout << C_CORAL << "\nImpaire\n";
	i = 0;
	for (it = impaire.begin(); it != impaire.end(); it++)
	{
		if (i == 0)
			std::cout << "[ ";
		std::cout << *it << " ";
		if (i++ == size - 1)
		{
			std::cout << "]  ";
			i = 0;
		}
	}

	std::cout << C_CORAL << "\nNon Participating\n" << "[ ";
	for (it = nonParcipating.begin(); it != nonParcipating.end(); it++)
		std::cout << *it << " ";
	std::cout << "]\n";
}

template <typename C>
void	PmergeMe<C>::insertPend(C &main, C &pend, int blocSize)
{
	C						winnerListPositon;
	typename C::iterator	it;
	typename C::iterator	begin;
	typename C::iterator	end;


	if (static_cast<int>(pend.size()) == blocSize)
	{
		main.insert(main.begin(), pend.begin(), pend.end());
		return ;
	}
	for (it = main.begin() + blocSize - 1;; it += blocSize)
	{
		winnerListPositon.push_back(*it);
		if (std::distance(it, main.end()) <= blocSize)
			break;
	}

	//---------------DEBUG--------------//
	std::cout << C_PURPLE "Winner List\n";
	for (it = winnerListPositon.begin(); it != winnerListPositon.end(); it++)
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
unsigned int PmergeMe<C>::calculateJacobsthal(unsigned int n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return PmergeMe<C>::calculateJacobsthal(n - 1) + 2 * PmergeMe<C>::calculateJacobsthal(n - 2);
}


