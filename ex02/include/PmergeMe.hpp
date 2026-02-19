/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:07:10 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/19 14:57:09 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <string>

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

		C		_container;

		void	convertInput(const std::string &str);
		void	printSequence(void) const;
		void	fordJohnson(C &sequence, int size);
		void	makePairs(C &sequence, C &impaire, C &nonParticipating, int size);
		void	createMainAndPend(C &sequence, C &main, C &pend, C &impaire, int size);
		void	insertPend(C &main, C &pend, int blocSize);
		void	printDebug(C &main, C &pend, C &impaire, C &nonParcipating, int size);

		static unsigned int	calculateJacobsthal(unsigned int n);
};

#include "../srcs/PmergeMe.tpp"
