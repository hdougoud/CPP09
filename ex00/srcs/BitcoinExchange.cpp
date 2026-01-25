/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:21:20 by votre_login       #+#    #+#             */
/*   Updated: 2026/01/26 00:18:00 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/BitcoinExchange.hpp"
#include <iostream>
#include <fstream>
#include <stdexcept>

void	extractCSV(std::ofstream &fs, BitcoinExchange &be);

BitcoinExchange::BitcoinExchange()
{
	return ;
}

BitcoinExchange::BitcoinExchange(const std::string &filename)
{
	std::ifstream	fs;

	fs.open(filename.c_str());
	if (!fs.is_open())
		throw (std::runtime_error("filename not found exception"));
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
	std::string	line;

	while (getline(fs, line))
	{
		std::cout << line << std::endl;
	}
	
}
