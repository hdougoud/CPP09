/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:04:15 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/03 13:34:30 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../include/color.hpp"
#include "../include/RPN.hpp"

int main(int ac, char **av)
{
	(void) av;
	if (ac != 2)
	{
		std::cout << C_YELLOW \
		<< "Please enter your calculation in a single argument as shown in the example below.\n" \
		<< "./RPN \"7 7 * 7 -\"" << RESET << std::endl;
		return (1);
	}
	try {
		std::cout << C_BLUE << RPN::calculates(av[1])	 << RESET << std::endl;
	}
	catch (const std::invalid_argument &e) {
		std::cerr << C_RED << e.what() << RESET << std::endl;
	}
	return (0);
}
