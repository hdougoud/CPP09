/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdougoud <hdougoud@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/03 09:11:10 by hdougoud          #+#    #+#             */
/*   Updated: 2026/02/04 22:01:19 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/RPN.hpp"
#include <cctype>
#include <limits>
#include <stack>
#include <stdexcept>
#include <sstream>

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

int	RPN::calculates(char *str)
{
	char				arg;
	std::stringstream	ss(str);
	std::stack<int>		stack;

	while (ss >> arg)
	{
		if (ss.fail())
			throw std::invalid_argument("Error: bad input\nUse only one character per argument");
		if (std::isdigit(arg))
		{
			stack.push(arg - '0');
			continue;
		}
		if (!isOperator(arg))
			throw std::invalid_argument("Error: illegal argument\nUse only numbers and the operators + - * /");
		stack.push(executeOperation(arg, stack));
	}
	if (stack.size() != 1)
		throw std::invalid_argument("Error: the calculation is impossible\nThere is more than one number in the stack");
	return stack.top();
}

int	RPN::executeOperation(char op, std::stack<int> &st)
{
	int		first, second;
	long	result;

	if (st.size() < 2)
		throw std::invalid_argument("Error: the calculation is impossible");
	first = removeAndGetTopValue(st);
	second = removeAndGetTopValue(st);
	switch (op)
	{
		case '+':
			result = second + first;
			break ;
		case '-':
			result = second - first;
			break ;
		case '*':
			result = second * first;
			break ;
		case'/':
			result = second / first;
	}
	if (result < std::numeric_limits<int>::min() || result > std::numeric_limits<int>::max())
		throw std::runtime_error("Error: result outside de numerical limits");
	return ( static_cast<int>(result));
}

int	RPN::removeAndGetTopValue(std::stack<int> &st)
{
	int value;

	value = st.top();
	st.pop();
	return (value);
}

bool	RPN::isOperator(char c)
{
	return (c == '+' || c == '-' || c == '*' || c == '/');
}

