/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/25 19:22:39 by votre_login       #+#    #+#             */
/*   Updated: 2026/02/02 19:26:06 by votre_login      ###   ########.fr       */
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

		static bool	isDateValide(const std::string &str);
		void		correspondenceSearch(const std::string &date, const float value) const;
	private:
		std::map<std::string, float>	_exchange;

		bool		read_csv(std::ifstream &fs);
		static bool	extractDate(const std::string &str, int &year, int &mouth, int &day);
		static bool	validateDate(const int year, const int month, const int day);
		static bool	checkMonthLength(const int year, const int month, const int day);
		static bool	isLeapYear(const int year);
};
