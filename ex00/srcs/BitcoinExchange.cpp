/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:21:20 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/02 21:39:34 by votre_login      ###   ########.fr       */
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
	read_csv(fs);
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

void	BitcoinExchange::read_csv(std::ifstream &fs)
{
	std::string	date, value;

	errno = 0;
	fs.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	while (getline(fs, date, ',') && getline(fs, value))
	{
		isDateValide(date);
		this->_exchange[date] = std::strtof(value.c_str(), NULL);
		if (errno)
			throw std::invalid_argument("invalid exchange_rate format");
	}
}

void	BitcoinExchange::isDateValide(const std::string &str)
{
	int					year, month, day;

	extractDate(str, year, month, day);
	validateDate(year, month, day);
}

void	BitcoinExchange::correspondenceSearch(const std::string &date, const float value) const
{
	std::map<std::string, float>::const_iterator it;

	it = this->_exchange.lower_bound(date);
	if (it->first != date)
		it--;
	std::cout << C_BLUE << date << " => " << value << " = " << it->second * value << RESET << std::endl;
}

void	BitcoinExchange::extractDate(const std::string &str, int &year, int &month, int &day)
{
	char				dash1, dash2;
	std::stringstream	ss(str);

	ss >> year >> dash1 >> month >> dash2 >> day;
	if (ss.fail() || !ss.eof())
		throw std::invalid_argument("bad input");
	if (dash1 != '-' || dash2 != '-')
		throw std::invalid_argument("bad input");
}

void	BitcoinExchange::validateDate(const int year, const int month, const int day)
{
	if (year < MIN_YEAR || year > MAX_YEAR)
		throw std::out_of_range("The year is outside the limits");
	if (month < 1 || month > 12)
		throw std::out_of_range("The month is outside the limits");
	checkMonthLength(year, month, day);
}

void	BitcoinExchange::checkMonthLength(const int year, const int month, const int day)
{
	int maxDay;

	if (month == 2)
		maxDay = (isLeapYear(year)) ? 29 : 28;
	else if (month == 4 || month == 6 || month == 9 || month == 11)
		maxDay = 30;
	else
		maxDay = 31;
	if (day < 1 || day > maxDay)
		throw std::out_of_range("The month is outside the limits");
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

