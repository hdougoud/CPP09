/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:57:36 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/23 00:15:37 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <sys/time.h>
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
	for (int i = 3; i < 33; i++)
		_jacobsthalSuit.push_back(PmergeMe<C>::calculateJacobsthal(i));
}

template <typename C>
PmergeMe<C>::PmergeMe(const PmergeMe &src) : _container(src._container), _jacobsthalSuit(src._jacobsthalSuit)
{
	return ;
}

template <typename C>
PmergeMe<C>	&PmergeMe<C>::operator=(const PmergeMe &src)
{
	if (this != &src)
	{
		this->_container = src._container;
		this->_jacobsthalSuit = src._jacobsthalSuit;
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
	int					i = 0;
	long				converted;
	std::stringstream	ss(str);

	while (ss >> converted)
	{
		//WARN: INT MAX AND INT MIN Dosen't work fix this later !!
		if (converted < 0 || converted >> std::numeric_limits<int>::max())
			throw std::invalid_argument("Error: use only positives numbers");
		if (i > 500000)
			throw std::invalid_argument("Error: too many numbers to sort\nThis program cannot sort more than 500'000 numbers");
		this->_container.push_back(converted);
	}
	if (!ss.eof() && ss.fail())
		throw std::invalid_argument("Error: use only numbers");
}

template <typename C>
void	PmergeMe<C>::sort(void)
{
	unsigned long	us;
	struct timeval	tStart;
	struct timeval	tEnd;

	//--------- DEBUG -----------------//
	std::cout << C_CORAL << "Jacobsthal Suit Test\n";
	for(typename C::iterator it = _jacobsthalSuit.begin(); it != _jacobsthalSuit.end(); it++)
		std::cout << *it << " ";
	std::cout << RESET << std::endl;
	//---------------------------------//

	std::cout << C_YELLOW << "\nINPUT\n";
	printSequence(this->_container);

	if (gettimeofday(&tStart, NULL))
		throw std::runtime_error("Error: gettimeofday failed");
	fordJohnson(this->_container, 1);
	if (gettimeofday(&tEnd, NULL))
		throw std::runtime_error("Error: gettimeofday failed");
	us = (tEnd.tv_usec - tStart.tv_sec) / 1000000;
	us = (tEnd.tv_usec - tStart.tv_usec);
	std::cout << C_BLUE << "Time taken for sorting: " << us << "us" << RESET << std::endl; 
	

	std::cout << C_YELLOW << "\nOUTPUT\n";
	printSequence(this->_container);
}


template <typename C>
void	PmergeMe<C>::fordJohnson(C &sequence, int size)
{
	C						main, pend, impaire, nonParticipating;
	typename C::iterator	it;

	if (size * 2 > static_cast<int>(sequence.size()))
		return;
	makePairs(sequence, impaire, nonParticipating, size);
	fordJohnson(sequence, size * 2);
	createMainAndPend(sequence, main, pend, impaire, size);
	//printDebug(main, pend, impaire, nonParticipating, size); //debug
	insertPend(main, pend, size);
	sequence = main;
}

template <typename C>
void	PmergeMe<C>::makePairs(C &sequence, C &impaire, C &nonParticipating, int size)
{
	typename C::iterator	it;

	for (it = sequence.begin(); std::distance(it, sequence.end()) >= size * 2; it += 2 * size)
	{
		if (*(it + size - 1) > *(it + size * 2 - 1))
			std::swap_ranges(it, it + size, it + size);
	}
	if (std::distance(it, sequence.end()) >= size)
	{
		impaire.assign(it, it + size);
		//it += size; //DEBUG: for printing nonParticipatingArray
	}
	(void) nonParticipating;
	//nonParticipating.insert(nonParticipating.begin(), it, sequence.end()); //DEBUG: for printing nonParticipatingArray
}

template <typename C>
void	PmergeMe<C>::createMainAndPend(C &sequence, C &main, C &pend, C &impaire, int size)
{
	typename C::iterator	it;

	for (it = sequence.begin(); std::distance(it, sequence.end()) >= size * 2; it += size)
	{
			pend.insert(pend.end(), it, it + size);
			it += size;
			main.insert(main.end(), it, it + size);
	}
	if (!pend.empty())
		sortPend(pend, size);
	if (!impaire.empty())
		pend.insert(pend.end(), impaire.begin(), impaire.end());
}

template <typename C>
void	PmergeMe<C>::sortPend(C &pend, int blockSize)
{
	C						sortedPend;
	typename C::iterator	jacobsthalNb; 
	typename C::iterator	rangeStart, rangeEnd, it;
	bool					isFinished;

	rangeStart = pend.begin() + blockSize;
	jacobsthalNb = this->_jacobsthalSuit.begin();
	sortedPend.insert(sortedPend.end(), pend.begin(), rangeStart);

	isFinished = false;
	while(!isFinished)
	{
		if (static_cast<unsigned long>(*jacobsthalNb * blockSize) >= pend.size())
		{
			rangeEnd = pend.end();
			isFinished = true;
		}
		else
			rangeEnd = pend.begin() + (*jacobsthalNb * blockSize);
		it = rangeEnd;
		while (std::distance(rangeStart, it) >= blockSize)
		{
			sortedPend.insert(sortedPend.end(), it - blockSize, it);
			it -= blockSize;
		}
		rangeStart = rangeEnd;
		jacobsthalNb++;
	}
	pend = sortedPend;
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
	int						mainStart;
	C						mainIdx;
	typename C::iterator	it, pendRef;

	if (pend.empty())
		return ;

	main.insert(main.begin(), pend.begin(), pend.begin() + blocSize);

	for (pendRef = (pend.begin() + blocSize); std::distance(pendRef, pend.end()) >= blocSize; pendRef += blocSize)
	{
		mainIdx.clear();
		for(it = main.begin(); std::distance(it, main.end()) >= blocSize; it += blocSize)
		{
			mainIdx.push_back(*(it + blocSize - 1));
		}
		//---------------DEBUG---------------//
		// std::cout << C_BLUE << "WinnerList\n";
		// for (it = mainIdx.begin(); it != mainIdx.end(); it++)
		// {
		// 	std::cout << *it <<  " ";
		// }
		// std::cout << RESET << std::endl;
		//-----------------------------------//
		it = std::lower_bound(mainIdx.begin(), mainIdx.end(), *(pendRef + blocSize - 1));
		mainStart = std::distance(mainIdx.begin(), it) * blocSize;
		main.insert(main.begin() + mainStart, pendRef, pendRef + blocSize);
	}

	
	std::cout << C_BLUE << "New main\n";
	int i = 0;
	for (pendRef = main.begin(); pendRef != main.end(); pendRef++)
	{
		if (i == 0)
			std::cout << "[ ";
		std::cout << *pendRef << " ";
		if (i++ == blocSize - 1)
		{
			std::cout << "]  ";
			i = 0;
		}
	}
	std::cout << RESET << std::endl;

}

template <typename C>
void	PmergeMe<C>::printSequence(C &sequence) const
{
	typename C::const_iterator it;

	std::cout << C_YELLOW;
	for (it = sequence.begin(); it != sequence.end(); it++)
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

