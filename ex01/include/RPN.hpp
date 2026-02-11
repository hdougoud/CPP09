/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:11:14 by hdougoud          #+#    #+#             */
/*   Updated: 2026/02/05 17:04:39 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stack>

class RPN
{
	public:
		static float	calculates(char *);
	private:
		RPN();
		RPN(const RPN &src);
		RPN &operator=(const RPN &src);
		~RPN();

		static float	executeOperation(char op, std::stack<float> &st);
		static float	removeAndGetTopValue(std::stack<float> &st);
		static bool		isOperator(char c);
};
