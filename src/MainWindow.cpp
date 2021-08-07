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
 * \file   MainWindow.cpp
 * \author Natahan Tatan
 * 
 * \version 1.0
 * \date July 13, 2020, 6:21 PM
 */

#include <FL/Fl_Menu_Item.H>
#include <FL/Fl_Widget.H>

#include "MainWindow.hpp"
#include "VideoDL.hpp"

std::vector<std::string> MainWindow::audioTypes = {
    "vorbis",
    "aac",
    "flac",
    "mp3",
    "m4a",
    "opus",
    "wav"
};

MainWindow::~MainWindow()
{
    if(window)
    {
        delete window;
    }
}

MainWindow::MainWindow(): MainWindowUI(), _current_vdl(nullptr)
{
    progress->maximum(100);
    progress->minimum(0);
    
    //Fill the "Audio type" combo
    for(std::string const& s: audioTypes)
    {
        cb_audio_type->add(s.c_str());
    }
    
    cb_audio_type->value(0);
    
    //Set callback for "Audio only" checkbox
    chk_audio_only->when(FL_WHEN_CHANGED);
    chk_audio_only->callback([](Fl_Widget* w, void* u){
        
        MainWindow* window = static_cast<MainWindow*>(u);
        if(window->chk_audio_only->value())
        {
            window->cb_audio_type->activate();
        }
        else
        {
            window->cb_audio_type->deactivate();
        }
        
    }, this);
    
    //Set callback for button "Download"
    pb_download->when(FL_WHEN_RELEASE);
    pb_download->callback([](Fl_Widget* w, void* u){
       
        Fl_Native_File_Chooser fch;
        fch.title("Choose a output dir");
        fch.type(Fl_Native_File_Chooser::BROWSE_DIRECTORY);
        fch.options(Fl_Native_File_Chooser::NEW_FOLDER);
      
        switch ( fch.show() ) 
        {
            case -1: 
                printf("ERROR: %s\n", fch.errmsg()); // ERROR
            case  1: 
                return; 
                break;  // CANCEL
                
            default: 
                break;  // FILE CHOSEN
        }
        
        std::cout << fch.filename() << std::endl;
        
        MainWindow* window = static_cast<MainWindow*>(u);
        window->_current_vdl = new VideoDL(fch.filename(), window->in_url->value(), window->chk_audio_only->value(), MainWindow::audioTypes[window->cb_audio_type->value()]);

        window->download_gui->show();
        window->setup_gui->deactivate();
     
        Fl::add_idle(UpdateProgress, window);
        
    }, this);
    
    //Set callback for url input
    in_url->when(FL_WHEN_CHANGED);
    in_url->callback([](Fl_Widget* w, void* u){
    
        Fl_Button* button = static_cast<Fl_Button*>(u);
        Fl_Input* in = static_cast<Fl_Input*>(w);
        
        if(!std::string(in->value()).empty())
        {
            button->activate();
        }
        else
        {
            button->deactivate();
        }
    
    }, pb_download);
    
    menu_quit->callback([](Fl_Widget* w, void* u){
        exit(0);
    });
    
    menu_get_ytdl->callback([](Fl_Widget* w, void* u){
        
        MainWindow* window = static_cast<MainWindow*>(u);
        window->setup_gui->deactivate();
        Fl::wait(); //Make deactivate take effect
        
        VideoDL::DownloadLastYoutubeDl();
        window->setup_gui->activate();
    },this);
    
    menu_about->callback([](Fl_Widget*w, void* u){
        AboutWindowUI* about = new AboutWindowUI();
        
        std::string title_label = std::string(about->box_title->label()) + " v" + VERSION;
        about->box_title->copy_label(title_label.c_str());
        
        about->br_about->textfont(FL_HELVETICA);
        about->br_about->value("<BODY><CENTER>Youtube downloader GUI Copyright (C) 2021 Natahan Tatan</CENTER> \
<P> \
This program is free software; you can redistribute it and/or modify it \
under the terms of the GNU General Public License as published by the Free \
Software Foundation; either version 3 of the License, or (at your option) \
any later version. \
</P> \
<P> \
This program is distributed in the hope that it will be useful, but WITHOUT \
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or \
FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for \
more details. \
</P> \
<P> \
You should have received a copy of the GNU General Public License along with this program. If not, see <A HREF='http://www.gnu.org/licenses/'>http://www.gnu.org/licenses/</A>. \
</P> \
</BODY>");
        
        about->pb_link->callback([](Fl_Widget*w, void* u){
            fl_open_uri("https://youtube-dl.org/");
        });
        
        about->pb_close->callback([](Fl_Widget*w, void* u){
            Fl::delete_widget(static_cast<Fl_Widget*>(u));
        }, about->window);
        
        about->window->callback([](Fl_Widget*w, void* u){
            Fl::delete_widget(static_cast<Fl_Widget*>(u));
        }, about->window);
        
        about->window->show();
    });
}

void MainWindow::UpdateProgress(void* u)
{
    MainWindow* window = static_cast<MainWindow*>(u);
    if(!window->_current_vdl)
        return;
    
    float p = window->_current_vdl->GetProgress();
    std::ostringstream oss;
    oss << p << "%";
       
    if(p < 100)
    {
        Fl::lock();
        window->progress->value(p);
        window->progress->copy_label(oss.str().c_str());
        Fl::unlock();
    }
    else if(p == 100)
    {
        Fl::lock();
        window->progress->value(100);
        window->progress->copy_label("Processing...");
        Fl::unlock();    
    }
    else if(p >= 101)
    {       
        Fl::lock();
        window->progress->copy_label("Ended !");
        window->setup_gui->activate();
        Fl::unlock();  
        
        Fl::remove_idle(UpdateProgress, u);
    }
}


