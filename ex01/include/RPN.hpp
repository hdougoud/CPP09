/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:11:14 by hdougoud          #+#    #+#             */
/*   Updated: 2026/02/04 20:26:09 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>

class RPN
{
	public:
		static int	calculates(char *);
	private:
		RPN();
		RPN(const RPN &src);
		RPN &operator=(const RPN &src);
		~RPN();

		static int	executeOperation(char op, std::stack<int> &st);
		static int	removeAndGetTopValue(std::stack<int> &st);
		static bool	isOperator(char c);
};
