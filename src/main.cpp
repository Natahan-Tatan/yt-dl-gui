/*
 * Copyright (C) 2021 Natahan Tatan
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
 * \file main.cpp
 * \author Natahan Tatan
 * 
 * \version 1.0
 * \date July 13, 2020, 5:07 PM
 */

/**
 * \mainpage Yt-dl-gui
 * \section intro Introduction
 * This program is a front-end for the youtube-dl script [available here](https://youtube-dl.org/).
 * It support, for the moment, only Linux platform. It requires the wget command (for download lastest youtube-dl program), and python to execute the tool.
 */

#include "MainWindow.hpp"
#include "VideoDL.hpp"

int main(int argc, char **argv) 
{
    chdir("/tmp/");
    Fl::scheme("gtk+");
    Fl::lock();//Init threading in FLTK
    
    MainWindow window;
    
    window.window->show();
    
    return Fl::run();
}