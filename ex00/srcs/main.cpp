/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:04:15 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/02 00:18:42 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fstream>
#include <iostream>
#include <limits>
#include "../include/BitcoinExchange.hpp"
#include "../include/color.hpp"

void	analyses_exchanges(const char *str);
bool	checkAndRemoveSpaces(std::string &date, std::string &value);

int	main(int ac, char **av)
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
	analyses_exchanges(av[1]);
	return (0);
}

void	analyses_exchanges(const char *str)
{
	std::string date, value;
	std::ifstream	fs;

	fs.open(str);
	if (fs.fail())
	{
		std::cout << C_RED << "impossible to open file \"" << str << "\"" << RESET << std::endl;
		return ;
	}
	fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (getline(fs, date, '|') && getline(fs, value))
	{
		if (checkAndRemoveSpaces(date, value))
			return ;
		if (!BitcoinExchange::isDateValide(date))
			return ;
		std::cout << date << std::endl;
	}
}

bool	checkAndRemoveSpaces(std::string &date, std::string &value)
{
	//TODO: check the spaces postion places like the subjects and removes them.
	return (0);
}
