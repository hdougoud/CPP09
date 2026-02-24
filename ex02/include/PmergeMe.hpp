/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/04 22:07:10 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/24 09:35:42 by votre_login      ###   ########.fr       */
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

		long	getUs(void) const;
		int		getElements(void) const;
		void	sort(void);
		void	printSequence(void);
	private:
		PmergeMe();
		PmergeMe(const PmergeMe &src);
		PmergeMe &operator=(const PmergeMe &src);

		C		_container;
		C		_jacobsthalSuit;
		int		_elements;
		long	_us;

		void	convertInput(const std::string &str);
		void	printSequence(C &sequence) const;
		void	fordJohnson(C &sequence, int size);
		void	makePairs(C &sequence, C &impaire, int size) const;
		void	createMainAndPend(C &sequence, C &main, C &pend, C &impaire, C &nonParticipating, int size);
		void	sortPend(C &pend, int blockSize);
		void	insertPend(C &main, C &pend, C &impaire, int blocSize) const;
		void	printDebug(C &main, C &pend, C &impaire, int size) const;

		static unsigned int	calculateJacobsthal(unsigned int n);
		static bool			isSorted(C &sequence);
};

#include "../srcs/PmergeMe.tpp"
