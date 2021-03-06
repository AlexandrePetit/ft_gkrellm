/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Ncurses.class.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hades <hades@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/17 17:20:26 by alex              #+#    #+#             */
/*   Updated: 2015/01/18 14:50:31 by hades            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ncurses.h>
#include <unistd.h>
#include "../headers/Ncurses.class.hpp"
#include "../headers/CPUmodule.class.hpp"
#include "../headers/DTmodule.class.hpp"
#include "../headers/HSmodule.class.hpp"
#include "../headers/OSmodule.class.hpp"
#include "../headers/Rmodule.class.hpp"

Ncurses::Ncurses(void) : _refreshRate(100000)	{ return ; }
Ncurses::~Ncurses()								{ return ; }

Ncurses::Ncurses(Ncurses const & object) {
	*this = object;

	return ;
}

Ncurses&		Ncurses::operator=(Ncurses const & rhs) {
	this->_refreshRate = rhs.getRefreshRate();

	return *this;
}

unsigned int	Ncurses::getRefreshRate() const {
	return this->_refreshRate;
}

void			Ncurses::setRefreshRate(unsigned int newRefreshRate) {
	this->_refreshRate = newRefreshRate;
}

void 			ft_draw_square( int maxHeight, int maxWidth, int i ) {
	int j = 0;

	maxHeight = maxHeight;

	i = i + i;
	while(i >= 0) {
		if ((i % 4) == 0) {
			while ( j < maxWidth - 1 ) {
				mvprintw(i, j, "=");
				j++;
			}
			j = 0;
		}
		else if (i) {
			mvprintw( i, 0, "|");
			mvprintw( i , 25, "|");
			mvprintw( i, maxWidth - 1, "|");
		}
		i--;
	}
	mvprintw(1, 13, "1");
	mvprintw(5, 13, "2");
	mvprintw(9, 13, "3");
	mvprintw(13, 13, "4");
	mvprintw(17, 13, "5");

	return ;
}


void			Ncurses::display() {
	CPUmodule    cpu(1);
	DTmodule	 dt(2);
	HSmodule	 hs(3);
	OSmodule	 os(4);
	Rmodule	 	 r(5);
	int			 maxHeight, maxWidth;
	int			 input = 0;

	initscr();
	keypad(stdscr, true);
	noecho();
	nodelay(stdscr, true);
	curs_set(0);
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_RED, COLOR_WHITE);
	wbkgd(stdscr,COLOR_PAIR(1));
	getmaxyx(stdscr, maxHeight, maxWidth);

	mvprintw(maxHeight - 1, maxWidth - 25, "press esc to exit");

	while ((input = getch()) != 27)
	{
		clear();
		cpu.findData();
		dt.findData();
		hs.findData();
		os.findData();
		r.findData();
		cpu.drawNcurses(maxWidth);
		dt.drawNcurses(maxWidth);
		hs.drawNcurses(maxWidth);
		os.drawNcurses(maxWidth);
		r.drawNcurses(maxWidth);
		mvprintw(maxHeight - 1, maxWidth - 25, "press esc to exit");
		ft_draw_square( maxHeight, maxWidth, 10);
		refresh();
		usleep(this->_refreshRate);
	}

	endwin();

	return ;
}