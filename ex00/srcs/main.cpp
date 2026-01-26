/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:04:15 by votre_login       #+#    #+#             */
/*   Updated: 2026/01/26 16:48:24 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include "../include/BitcoinExchange.hpp"
#include "../include/color.hpp"

int main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << C_RED;
		std::cout << (ac > 2 ? "Please use only one file" : "Please use a file as the input argument");
		std::cout << RESET << std::endl;
		return (1);
	}
	(void) av;
	try {
		BitcoinExchange	be("data.csv");
	}
	catch (std::runtime_error &e) {
		std::cout << C_RED << e.what() << RESET << std::endl;
		return (1);
	}
	return (0);
}
