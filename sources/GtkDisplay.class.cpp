/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   GtkDisplay.class.cpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alex <alex@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/01/18 00:55:22 by alex              #+#    #+#             */
/*   Updated: 2015/01/18 18:38:00 by alex             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <gtk/gtk.h>
#include "../headers/GtkDisplay.class.hpp"
# include "../headers/Refresh.class.hpp"

GtkDisplay::~GtkDisplay()	{ return ; }

void	OnDestroy(GtkWidget *pWidget, gpointer pData)
{
	gtk_main_quit();
	(void)pWidget;
	(void)pData;
}

gboolean	OnTimeout(gpointer data)
{
	(void)data;

	Refresh::datetime_module.refreshLabel();
	Refresh::ram_module.refreshLabel();

	return true;
}

GtkDisplay::GtkDisplay(int argc, char *argv[]) {
	gtk_init (&argc, &argv);

	this->_window = gtk_window_new (GTK_WINDOW_TOPLEVEL);

	gtk_window_set_title (GTK_WINDOW (this->_window), "ft_gkrellm");
	gtk_window_set_default_size(GTK_WINDOW(this->_window), 250, 600);
	gtk_window_set_resizable(GTK_WINDOW(this->_window), false);
	gtk_widget_set_size_request(this->_window, 250, 600);
	gtk_window_set_position(GTK_WINDOW(this->_window), GTK_WIN_POS_CENTER);
	gtk_container_set_border_width(GTK_CONTAINER(this->_window), 5);
	g_signal_connect(this->_window, "destroy", G_CALLBACK(OnDestroy), NULL);

	/* Création de la GtkBox verticale */
	this->_pVBox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
	gtk_container_add(GTK_CONTAINER(this->_window), this->_pVBox);

	Refresh::pWindow = this->_window;
	Refresh::pVBox = this->_pVBox;

	return ;
}

void		GtkDisplay::addModule(IMonitorModule &module)	{ module.addToGtk(this->_pVBox); return ; }

void		GtkDisplay::display() {
	gtk_widget_show_all(Refresh::pWindow);

	g_timeout_add (100, OnTimeout, NULL);

	gtk_main();

	return ;
}