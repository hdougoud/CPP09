/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/20 21:04:15 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/02 22:04:34 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cerrno>
#include <exception>
#include <fstream>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <stdlib.h>
#include "../include/BitcoinExchange.hpp"
#include "../include/color.hpp"

void	analyses_exchanges(const char *str, BitcoinExchange &be);
void	extractDateAndValue(std::string &line, std::string &date, float &value);

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
	catch (std::exception &e) {
		std::cout << C_RED << e.what() << RESET << std::endl;
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
		try{
			extractDateAndValue(line, date, value);
			BitcoinExchange::isDateValide(date);
			be.correspondenceSearch(date, value);
		}
		catch (std::invalid_argument &e) {
			std::cerr << C_RED << e.what() << RESET << std::endl;
		}
		catch (std::out_of_range &e) {
			std::cerr << C_RED << e.what() << RESET << std::endl;
		}
	}
}

void	extractDateAndValue(std::string &line, std::string &date, float &value)
{
	size_t		separator;
	std::string	errorLine;

	errno = 0;
	if ((separator = line.find(" | ")) == std::string::npos)
	{
		errorLine = "Error: bad input => " + line;
		throw std::invalid_argument(errorLine);
	}
	date = line.substr(0, separator);
	value = strtof(line.substr(separator + 3).c_str(), NULL);
	if (errno)
	{
		errorLine = "Error: bad input => " + line;
		throw std::invalid_argument(errorLine);
	}
	if (value < 0)
	{
		throw std::invalid_argument("Error: not a positive number.");
	}
	if (value > 1000)
	{
		throw std::invalid_argument("Error: too large a number.");
	}
}
