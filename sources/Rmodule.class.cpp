/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Rmodule.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hades <hades@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 21:35:05 by hades             #+#    #+#             */
/*   Updated: 2015/01/18 14:57:27 by hades            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <sys/sysinfo.h>
#include <ncurses.h>
#include "../headers/Rmodule.class.hpp"
#include "../headers/usual_functions.hpp"

Rmodule::Rmodule( int position ) : _position(position), _name("RAM module") { this->findData(); return ; }
Rmodule::~Rmodule( void ) { return ; }


//getter
int			Rmodule::getPosition( void ) const {
	return this->_position;
}

std::string Rmodule::getData( void ) const {
	return this->_data;
}

std::string Rmodule::getName( void ) const {
	return this->_name;
}

//other
void		Rmodule::findData( void ) {
	/* Conversion constants. */
	const long 			minute = 60;
	const long 			hour = minute * 60;
	const long 			day = hour * 24;
	std::string			data;

	/* Obtain system statistics. */
	struct sysinfo si;
	sysinfo (&si);

	/* Summarize interesting values. */
	data = "system uptime : " + static_cast<std::string>(ft_itoa(si.uptime / day)) + " days, " + static_cast<std::string>(ft_itoa((si.uptime % day) / hour)) + static_cast<std::string>(":") + static_cast<std::string>(ft_itoa((si.uptime % hour) / minute)) + static_cast<std::string>(":") + static_cast<std::string>(ft_itoa(si.uptime % minute));
	data = data + " | total RAM : " + static_cast<std::string>(ft_itoa(si.totalram)) + "KB | ";
	data = data + "free RAM : " + static_cast<std::string>(ft_itoa(si.freeram)) + "KB | ";
	data = data + "process count : " + static_cast<std::string>(ft_itoa(si.procs));

	this->_data = data;

}

void		Rmodule::drawNcurses( int maxWidth ) const {
	int i = 26, j = 0, count = 0;
	if (this->_position == 1) {
		attron(COLOR_PAIR(2));
		mvprintw(2, 2, this->getName().c_str());
		attroff(COLOR_PAIR(2));
		while (count < 3) {
			while (i < maxWidth && this->_data[j]) {
				mvaddch(1 + count, i, this->_data[j]);
				j++;
				i++;
			}
			i = 26;
			count++;
		}

	}
	else if (this->_position == 2) {
		attron(COLOR_PAIR(2));
		mvprintw(6, 2, this->getName().c_str());
		attroff(COLOR_PAIR(2));
		while (count < 3) {
			while (i < maxWidth && this->_data[j]) {
				mvaddch(5 + count, i, this->_data[j]);
				j++;
				i++;
			}
			i = 26;
			count++;
		}
	}
	else if (this->_position == 3) {
		attron(COLOR_PAIR(2));
		mvprintw(10, 2, this->getName().c_str());
		attroff(COLOR_PAIR(2));
		while (count < 3) {
			while (i < maxWidth && this->_data[j]) {
				mvaddch(9 + count, i, this->_data[j]);
				j++;
				i++;
			}
			i = 26;
			count++;
		}
	}
	else if (this->_position == 4) {
		attron(COLOR_PAIR(2));
		mvprintw(14, 2, this->getName().c_str());
		attroff(COLOR_PAIR(2));
		while (count < 3) {
			while (i < maxWidth && this->_data[j]) {
				mvaddch(13 + count, i, this->_data[j]);
				j++;
				i++;
			}
			i = 26;
			count++;
		}
	}
	else  {
		attron(COLOR_PAIR(2));
		mvprintw(18, 2, this->getName().c_str());
		attroff(COLOR_PAIR(2));
		while (count < 3) {
			while (i < maxWidth && this->_data[j]) {
				mvaddch(17 + count, i, this->_data[j]);
				j++;
				i++;
			}
			i = 26;
			count++;
		}
	}
}
