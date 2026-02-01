/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:21:20 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/01 23:54:00 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <stdexcept>
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
	fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (getline(fs, date, ',') && getline(fs, value))
	{
		if (isDateValide(date))
		{
			std::cout << "Invalid date format" << std::endl;
			return (1);
		}
		this->_exchange[date] = std::strtof(value.c_str(), NULL);
		if (errno)
		{
			std::cout << "Invalid ammount format" << errno << std::endl;
			return (1);
		}
	}
	return (0);
}

bool	BitcoinExchange::isDateValide(const std::string &str)
{
	int					year, month, day;

	if (extractDate(str, year, month, day))
		return (1);
	if (validateDate(year, month, day))
		return (1);
	//std::cout << year << " " << month << " " << day << std::endl;
	return (0);
}

bool	BitcoinExchange::extractDate(const std::string &str, int &year, int &month, int &day)
{
	char				dash1, dash2;
	std::stringstream	ss(str);

	ss >> year >> dash1 >> month >> dash2 >> day;
	if (ss.fail() || !ss.eof())
		return (1);
	if (dash1 != '-' || dash2 != '-')
		return (1);
	return (0);
}

bool	BitcoinExchange::validateDate(int &year, int &month, int &day)
{
	if (year < MIN_YEAR || year > MAX_YEAR)
		return (1);
	if (month < 1 || month > 12)
		return (1);
	if (day < 1 || day > 31)
		return (1);
	return (0);
}

