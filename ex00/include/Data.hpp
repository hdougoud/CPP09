/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Data.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: votre_login <votre_login@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/21 15:12:03 by votre_login       #+#    #+#             */
/*   Updated: 2026/01/21 21:47:02 by votre_login      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <map>

class Data
{
	public:
		Data();
		Data(const Data &src);
		Data &operator=(const Data &src);
		~Data();
	private:
		std::map<std::string, float> stock_history;
};
