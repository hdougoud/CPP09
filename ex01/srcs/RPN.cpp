/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:11:10 by hdougoud          #+#    #+#             */
/*   Updated: 2026/02/03 16:57:34 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"
#include <cctype>
#include <stack>
#include <stdexcept>
#include <string>

RPN::RPN()
{
	return ;
}

RPN::RPN(const RPN &src)
{
	(void) src;
	return ;
}

RPN	&RPN::operator=(const RPN &src)
{
	(void) src;
	return (*this);
}

RPN::~RPN()
{
	return ;
}

int	RPN::calculates(std::stringstream &ss)
{


}

bool	RPN::isOperator(char c)
{
	switch (c)
	{
		case '+':
			return (true);
		case '-':
			return (true);
		case '*':
			return (true);
		case '/':
			return (true);
		default:
			return (false);
	}
}
