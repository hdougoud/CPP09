/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:22:39 by votre_login       #+#    #+#             */
/*   Updated: 2026/01/27 19:06:19 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <fstream>
#include <map>
#include <string>

#define MIN_YEAR 2009
#define MAX_YEAR 2026

class BitcoinExchange
{
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string &filename);
		BitcoinExchange(const BitcoinExchange &src);
		BitcoinExchange &operator=(const BitcoinExchange &src);
		~BitcoinExchange();
	private:
		std::map<std::string, float>	_exchange;

		bool		read_csv(std::ifstream &fs);
		static bool	isDateValide(const std::string &str);
		static bool	strToInt(const std::string &str, int &value);
};
