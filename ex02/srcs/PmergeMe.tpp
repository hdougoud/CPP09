/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:57:36 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/07 05:24:40 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
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

	convertInput(str, temp);
	this->makePairs(temp);
	std::cout << this->_container.size() << std::endl;
	this->printContainer();
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
void	PmergeMe<C>::makePairs(const std::vector<int> &temp)
{
	std::pair<int, int>							pair;
	typename std::vector<int>::const_iterator	it;

	it = temp.begin();
	for (it = temp.begin(); it != temp.end(); it++)
	{
		if (std::distance(it, temp.end()) < 1)
			break;
		pair.first = *it++;
		pair.second = *it;
		this->_container.push_back(pair);
	}
}


template <typename C>
void	PmergeMe<C>::printContainer(void) const
{
	typename C::const_iterator it;

	for (it = this->_container.begin(); it != this->_container.end(); it++)
		std::cout << C_BLUE << "first: " << it->first << " | second:  " << it->second << RESET << std::endl;
}

template <typename C>
void	PmergeMe<C>::convertInput(const std::string &str, std::vector<int> &temp)
{
	int					converted;
	std::stringstream	ss(str);

	while (ss >> converted)
	{
		if (converted < 0)
			throw std::invalid_argument("Error: use only positives numbers");
		temp.push_back(converted);
	}
	if (!ss.eof())
		throw std::invalid_argument("Error: use only numbers");
}

