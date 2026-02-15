/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:07:10 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/15 20:31:00 by votre_login      ###   ########.fr       */
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

		void	sort(void);
	private:
		C					_container;
		std::vector<int>	_main;
		std::vector<int>	_pend;

		void		convertInput(const std::string &str);
		void		printSequence(void) const;

		static void	makePairs(std::vector<int> &numbers);
		static void	sortPair(std::pair<int, int> &p);
		static void	printContainer(const std::vector<std::pair<int, int> > &vec);
};

#include "../srcs/PmergeMe.tpp"
