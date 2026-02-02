/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:04:15 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/02 16:23:18 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdlib.h>
#include "../include/BitcoinExchange.hpp"
#include "../include/color.hpp"

void	analyses_exchanges(const char *str, BitcoinExchange &be);
bool	extactDateAndValue(std::string &line, std::string &date, float &value);

int	main(int ac, char **av)
{
	if (ac != 2)
	{
		std::cout << C_RED;
		std::cout << (ac > 2 ? "Please use only one file" : "Please use a file as input argument");
		std::cout << RESET << std::endl;
		return (1);
	}
	try {
		BitcoinExchange	be("data.csv");
		analyses_exchanges(av[1], be);
	}
	catch (std::runtime_error &e) {
		std::cout << C_RED << e.what() << RESET << std::endl;
		return (1);
	}
	return (0);
}

void	analyses_exchanges(const char *str, BitcoinExchange &be)
{
	float			value;
	std::string		line, date;
	std::ifstream	fs;

	fs.open(str);
	if (fs.fail())
	{
		std::cout << C_RED << "impossible to open file \"" << str << "\"" << RESET << std::endl;
		return ;
	}
	fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

	while (getline(fs, line))
	{
		if (extactDateAndValue(line, date, value))
			continue ;
		if (BitcoinExchange::isDateValide(date))
			return ;
		be.correspondenceSearch(date, value);
	}
}

bool	extactDateAndValue(std::string &line, std::string &date, float &value)
{
	size_t	separator;

	errno = 0;
	if ((separator = line.find(" | ")) == std::string::npos)
	{
		std::cout << C_RED << "Error: bad input => " << line << RESET << std::endl;
		return (1);
	}
	date = line.substr(0, separator);
	value = strtof(line.substr(separator + 3).c_str(), NULL);
	if (errno)
	{
		std::cout << C_RED << "Error: bad input => " << line << RESET << std::endl;
		return (1);
	}
	if (value < 0)
	{
		std::cout << C_RED << "Error: not a positive number." << RESET << std::endl;
		return (1);
	}
	if (value > 1000)
	{
		std::cout << C_RED << "Error: too large a number." << RESET << std::endl;
		return (1);
	}
	return (0);
}
