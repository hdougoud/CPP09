/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:21:20 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/02 21:02:25 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"
#include <algorithm>
#include <cctype>
#include <cstdlib>
#include <errno.h>
#include <fstream>
#include <iostream>
#include <limits>
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
	if	(!read_csv(fs))
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
	std::string	date, value;

	errno = 0;
	fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (getline(fs, date, ',') && getline(fs, value))
	{
		if (!isDateValide(date))
			return (false);
		this->_exchange[date] = std::strtof(value.c_str(), NULL);
		if (errno)
		{
			std::cout << C_RED << "Invalid ammount format" << RESET << errno << std::endl;
			return (false);
		}
	}
	return (true);
}

bool	BitcoinExchange::isDateValide(const std::string &str)
{
	int					year, month, day;

	if (!extractDate(str, year, month, day))
	{
		std::cout << C_RED << "Invalid date format" << RESET << std::endl;
		return (false);
	}
	if (!validateDate(year, month, day))
		return (false);
	return (true);
}

void	BitcoinExchange::correspondenceSearch(const std::string &date, const float value) const
{
	std::map<std::string, float>::const_iterator it;

	it = this->_exchange.lower_bound(date);
	if (it->first != date)
		it--;
	std::cout << C_BLUE << date << " => " << value << " = " << it->second * value << RESET << std::endl;
}

bool	BitcoinExchange::extractDate(const std::string &str, int &year, int &month, int &day)
{
	char				dash1, dash2;
	std::stringstream	ss(str);

	ss >> year >> dash1 >> month >> dash2 >> day;
	if (ss.fail() || !ss.eof())
		return (false);
	if (dash1 != '-' || dash2 != '-')
		return (false);
	return (true);
}

bool	BitcoinExchange::validateDate(const int year, const int month, const int day)
{
	if (year < MIN_YEAR || year > MAX_YEAR)
	{
		std::cout << C_RED << "the year is outside the limits" << RESET << std::endl;
		return (false);
	}
	if (month < 1 || month > 12)
	{
		std::cout << C_RED << "the month is outside the limits" << RESET << std::endl;
		return (false);
	}
	if (!checkMonthLength(year, month, day))
	{
		std::cout << C_RED << "the day is outside the limits" << RESET << std::endl;
		return (false);
	}
	return (true);
}

bool	BitcoinExchange::checkMonthLength(const int year, const int month, const int day)
{
	int maxDay;

	if (month == 2)
		maxDay = (isLeapYear(year)) ? 29 : 28;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		maxDay = 30;
	else
		maxDay = 31;
	if (day < 1 || day > maxDay)
		return (false);
	return (true);
}

bool	BitcoinExchange::isLeapYear(const int year)
{
	if (year % 400 == 0)
		return (true);
	if (year % 100 == 0)
		return (false);
	if (year % 4 == 0)
		return (true);
	return (false);
}

