/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:11:10 by hdougoud          #+#    #+#             */
/*   Updated: 2026/02/03 13:42:01 by hdougoud         ###   ########.fr       */
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

int	RPN::calculates(char *input)
{
	std::stack<int>	rpn;
	std::string		errorMsg;
	int				result = 0;

	while (*input)
	{
		while (std::isspace(*input))
			input++;
		if (!std::isdigit(*input) && !RPN::isOperator(*input))
		{
			errorMsg = "Error: Illegal argument exception ";
			throw std::invalid_argument(errorMsg += *input);
		}
		input++;
		if (*input && !std::isspace(*input))
		{
			errorMsg = "Error: Illegal argument exception ";
			throw std::invalid_argument(errorMsg += *input);
		}
		input++;
	}
	return (result);
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
