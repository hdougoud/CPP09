/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:57:36 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/15 20:38:43 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"
#include <algorithm>
#include <iostream>
#include <iterator>
#include <limits>
#include <sstream>
#include <stdexcept>
#include <utility>
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
	//TODO: ADD TIMER
	this->printSequence();
	makePairs(this->_container);
	this->printSequence();

}

template <typename C>
void	PmergeMe<C>::makePairs(std::vector<int> &numbers)
{
	int									impaire;
	std::vector<int>					next;
	std::vector<std::pair<int, int> >	pairs;
	std::vector<int>::iterator			it;

	(void) impaire;
	impaire = -1;
	if (numbers.size() < 2)
		return ;
	for(it = numbers.begin(); it != numbers.end(); it++)
	{
		if (std::distance(it, numbers.end()) < 2)
		{
			impaire = *it;
			break;
		}
		if (*it > *(it + 1))
			std::iter_swap(it, it + 1);
		pairs.push_back(std::pair<int, int>(*it++, *it));
		next.push_back(pairs.back().second);
	}
	PmergeMe<C>::printContainer(pairs);
	makePairs(next);

}

template <typename C>
void	PmergeMe<C>::printSequence(void) const
{
	typename C::const_iterator it;

	for (it = this->_container.begin(); it != this->_container.end(); it++)
		std::cout << C_YELLOW << *it << " " << RESET;
	std::endl(std::cout);
}

template <typename C>
void	PmergeMe<C>::printContainer(const std::vector<std::pair<int, int> > &vec)
{
	std::vector<std::pair<int, int>		>::const_iterator it;

	std::cout << C_YELLOW << "{\n";
	for (it = vec.begin(); it != vec.end(); it++)
		std::cout << C_BLUE << "    " << it->first << " " << it->second << RESET << "\n";
	std::cout << C_YELLOW << "}\n";
	std::endl(std::cout);
}

template <typename C>
void	PmergeMe<C>::sortPair(std::pair<int, int> &p)
{
	int	temp;

	if (p.first > p.second)
	{
		temp = p.first;
		p.first = p.second;
		p.second = temp;
	}
}

