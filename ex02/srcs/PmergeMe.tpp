/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 00:57:36 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/07 03:12:05 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/PmergeMe.hpp"
#include <iostream>
#include <sstream>
#include <stdexcept>
#include "../include/color.hpp"

template <typename C>
PmergeMe<C>::PmergeMe()
{
	return ;
}

template <typename C>
PmergeMe<C>::PmergeMe(std::string str)
{
	int					temp;
	std::stringstream	ss(str);

	while (ss >> temp)
	{
		if (ss.fail())
			throw std::invalid_argument("Error: use only numbers");
		this->_container.push_back(temp);
	}
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
void	PmergeMe<C>::printContainer(void) const
{
	typename C::const_iterator it;

	for (it = this->_container.begin(); it != this->_container.end(); it++)
		std::cout << C_BLUE << *it << RESET << std::endl;
}

