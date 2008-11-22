/*
 *  gtkmm-utils - page-navigator.cc
 *
 *  Copyright (C) 2007 Marko Anastasov
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <gtkmm/alignment.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/image.h>
#include <gtkmm/label.h>
#include <gtkmm/stock.h>
#include "page-navigator.h"

namespace Gtk {

namespace Util {

/* PageNavigator::Private */

class PageNavigator::Private
{
public:
    Private();
    ~Private() {}

    void connect_signals();
    void on_button_first_clicked();
    void on_button_previous_clicked();
    void on_button_next_clicked();
    void on_button_last_clicked();

    PageNavigator::SignalNavigation signal_first;
    PageNavigator::SignalNavigation signal_previous;
    PageNavigator::SignalNavigation signal_next;
    PageNavigator::SignalNavigation signal_last;

    Glib::ustring  title;

    Gtk::HBox      root_box;
    Gtk::Alignment align_box;
    Gtk::HBox      label_box;
    Gtk::Label     label_title;
    Gtk::Label     label_page_info;
    Gtk::Button    button_first;
    Gtk::Image     image_first;
    Gtk::Button    button_previous;
    Gtk::Image     image_previous;
    Gtk::Button    button_next;
    Gtk::Image     image_next;
    Gtk::Button    button_last;
    Gtk::Image     image_last;
};

PageNavigator::Private::Private()
    :
    title(),
    root_box(),
    align_box(0.0, 1.0, 1.0, 1.0),
    label_box(false, 0),
    label_title(title),
    label_page_info(),
    button_first(),
    image_first(Gtk::Stock::GOTO_FIRST, Gtk::ICON_SIZE_SMALL_TOOLBAR),
    button_previous(),
    image_previous(Gtk::Stock::GO_BACK, Gtk::ICON_SIZE_SMALL_TOOLBAR),
    button_next(),
    image_next(Gtk::Stock::GO_FORWARD, Gtk::ICON_SIZE_SMALL_TOOLBAR),
    button_last(),
    image_last(Gtk::Stock::GOTO_LAST, Gtk::ICON_SIZE_SMALL_TOOLBAR)
{
    align_box.set_padding(18, 3, 0, 0);
    root_box.pack_start(align_box, false, true, 0);
    
    align_box.add(label_box);
    label_box.set_spacing(5);
    label_box.pack_start(label_title, false, true, 0);
    label_title.set_justify(Gtk::JUSTIFY_LEFT);
    label_box.pack_start(label_page_info, false, true, 0);
    label_page_info.set_justify(Gtk::JUSTIFY_LEFT);
    
    button_last.set_relief(Gtk::RELIEF_NONE);
    button_last.add(image_last);
    root_box.pack_end(button_last, false, true, 0);

    button_next.set_relief(Gtk::RELIEF_NONE);
    button_next.add(image_next);
    root_box.pack_end(button_next, false, true, 0);

    button_previous.set_relief(Gtk::RELIEF_NONE);
    button_previous.add(image_previous);
    root_box.pack_end(button_previous, false, true, 0);
    
    button_first.set_relief(Gtk::RELIEF_NONE);
    button_first.add(image_first);
    root_box.pack_end(button_first, false, true, 0);
    
    connect_signals();
}

void
PageNavigator::Private::on_button_first_clicked()
{
    signal_first.emit();
}

void
PageNavigator::Private::on_button_previous_clicked()
{
    signal_previous.emit();
}

void
PageNavigator::Private::on_button_next_clicked()
{
    signal_next.emit();
}

void
PageNavigator::Private::on_button_last_clicked()
{
    signal_last.emit();
}

void
PageNavigator::Private::connect_signals()
{
    button_first.signal_clicked().connect(
        sigc::mem_fun(*this,
                      &PageNavigator::Private::on_button_first_clicked));

    button_previous.signal_clicked().connect(
        sigc::mem_fun(*this,
                      &PageNavigator::Private::on_button_previous_clicked));

    button_next.signal_clicked().connect(
        sigc::mem_fun(*this,
                      &PageNavigator::Private::on_button_next_clicked));
    
    button_last.signal_clicked().connect(
        sigc::mem_fun(*this,
                      &PageNavigator::Private::on_button_last_clicked));
}

/* PageNavigator */

PageNavigator::PageNavigator()
{
    priv_.reset(new Private());

    add(priv_->root_box);
    show_all();
    
    show_all();
}

PageNavigator::~PageNavigator()
{
}

void
PageNavigator::set_title(const Glib::ustring& title)
{
    priv_->label_title.set_text(title);
}

void
PageNavigator::set_title_markup(const Glib::ustring& marked_up_title)
{
    priv_->label_title.set_markup(marked_up_title);
}

void
PageNavigator::set_page_info(const Glib::ustring& info)
{
    priv_->label_page_info.set_text(info);
}

PageNavigator::SignalNavigation&
PageNavigator::signal_first()
{
    return priv_->signal_first;
}

PageNavigator::SignalNavigation&
PageNavigator::signal_previous()
{
    return priv_->signal_previous;
}

PageNavigator::SignalNavigation&
PageNavigator::signal_next()
{
    return priv_->signal_next;
}

PageNavigator::SignalNavigation&
PageNavigator::signal_last()
{
    return priv_->signal_last;
}

Gtk::Button&
PageNavigator::get_button_first()
{
    return priv_->button_first;
}

Gtk::Button&
PageNavigator::get_button_previous()
{
    return priv_->button_previous;
}

Gtk::Button&
PageNavigator::get_button_next()
{
    return priv_->button_next;
}

Gtk::Button&
PageNavigator::get_button_last()
{
    return priv_->button_last;
}

bool
PageNavigator::on_scroll_event(GdkEventScroll* event)
{
    if (event->direction == GDK_SCROLL_UP)
        priv_->signal_previous.emit();
    else if (event->direction == GDK_SCROLL_DOWN)
        priv_->signal_next.emit();

    return false;
}

} // namespace Util

} // namespace Gtk
