/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:07:10 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/17 14:57:38 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>
#include <vector>

template <typename C>
class PmergeMe
{
	public:
		PmergeMe(const std::string &str);
		~PmergeMe();

		void	sort(void);
	private:
		PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);

		C			_container;

		void		convertInput(const std::string &str);
		void		printSequence(void) const;
		void		makePairs(C &sequence, int size);

		static void			insertPend(C &main, C &pend, int blocSize);
		static unsigned int	calculateJacobsthal(unsigned int n);
};

#include "../srcs/PmergeMe.tpp"
