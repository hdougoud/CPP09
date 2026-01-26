/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:21:20 by votre_login       #+#    #+#             */
/*   Updated: 2026/01/26 17:17:52 by hdougoud         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"
#include <cctype>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <cstdlib>
#include "../include/color.hpp"

void	extractCSV(std::ofstream &fs, BitcoinExchange &be);

BitcoinExchange::BitcoinExchange()
{
	return ;
}

BitcoinExchange::BitcoinExchange(const std::string &filename)
{
	std::ifstream	fs;

	//TODO:check .csv extention
	fs.open(filename.c_str());
	if (!fs.is_open())
		throw (std::runtime_error("Error cannot open the file"));
	if (fs.eof())
		throw (std::runtime_error("Error files is empty"));
	if	(read_csv(fs))
		throw (std::runtime_error("Error bad argument in file"));
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src) : _exchange(src._exchange)
{
	return ;
}

BitcoinExchange	&BitcoinExchange::operator=(const BitcoinExchange &src)
{
	if (this != &src)
	{
		this->_exchange = src._exchange;
	}
	return (*this);
}

BitcoinExchange::~BitcoinExchange()
{
	return ;
}

bool	BitcoinExchange::read_csv(std::ifstream &fs)
{
	std::string	date;
	std::string	value;

	errno = 0;
	getline(fs, date);
	while (fs.peek() != fs.eof())
	{
		getline(fs, date, ',');
		getline(fs, value);
		if (isDateValide(date))
		{
			std::cout << "date invalid" << std::endl;
			return (1);
		}
		this->_exchange[date] = std::strtof(value.c_str(), NULL);
		if (errno)
		{
			std::cout << "errno error" << std::endl;
			return (1);
		}
	}
	return (0);
}

bool	BitcoinExchange::isDateValide(const std::string &str)
{
//	int							npos;
//	int							year, month, day;
//	std::string::const_iterator	it;

	std::cout << str.length() << std::endl;
	if (str.length() != 10)
		return (1);
	return (0);
}
