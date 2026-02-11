/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:07:10 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/07 07:52:08 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

template <typename C>
class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(const std::string &str);
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);
		~PmergeMe();
	private:
		C	_container;

		void		convertInput(const std::string &str);
		void		makePairs(const std::vector<int> &temp);
		void		printContainer(void) const;
};

#include "../srcs/PmergeMe.tpp"
