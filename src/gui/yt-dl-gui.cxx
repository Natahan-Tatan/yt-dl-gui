// generated by Fast Light User Interface Designer (fluid) version 1.0304

#include "yt-dl-gui.hpp"

Fl_Menu_Item MainWindowUI::menu_[] = {
 {"File", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Get youtube-dl executable", 0,  0, 0, 128, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Quit    ", 0x40071,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {"Help", 0,  0, 0, 64, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"Help", 0xffbe,  0, 0, 128, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {"About...", 0,  0, 0, 0, (uchar)FL_NORMAL_LABEL, 0, 14, 0},
 {0,0,0,0,0,0,0,0,0},
 {0,0,0,0,0,0,0,0,0}
};
Fl_Menu_Item* MainWindowUI::menu_get_ytdl = MainWindowUI::menu_ + 1;
Fl_Menu_Item* MainWindowUI::menu_quit = MainWindowUI::menu_ + 2;
Fl_Menu_Item* MainWindowUI::menu_help = MainWindowUI::menu_ + 5;
Fl_Menu_Item* MainWindowUI::menu_about = MainWindowUI::menu_ + 6;

MainWindowUI::MainWindowUI() {
  { window = new Fl_Double_Window(535, 155, "Youtube downloader GUI");
    window->user_data((void*)(this));
    window->align(Fl_Align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE));
    { Fl_Group* o = new Fl_Group(30, 45, 495, 105);
      { setup_gui = new Fl_Group(30, 45, 485, 90);
        { in_url = new Fl_Input(65, 45, 350, 25, "URL:");
          in_url->tooltip("The full video URL");
        } // Fl_Input* in_url
        { pb_download = new Fl_Button(420, 45, 85, 25, "Download");
          pb_download->align(Fl_Align(FL_ALIGN_CENTER|FL_ALIGN_INSIDE));
          pb_download->deactivate();
        } // Fl_Button* pb_download
        { Fl_Group* o = new Fl_Group(30, 80, 480, 50);
          { chk_audio_only = new Fl_Check_Button(65, 80, 95, 25, "Audio only");
            chk_audio_only->down_box(FL_DOWN_BOX);
          } // Fl_Check_Button* chk_audio_only
          { Fl_Box* o = new Fl_Box(30, 108, 470, 17);
            Fl_Group::current()->resizable(o);
          } // Fl_Box* o
          o->end();
        } // Fl_Group* o
        { Fl_Group* o = new Fl_Group(145, 80, 370, 50);
          { cb_audio_type = new Fl_Choice(180, 80, 145, 25);
            cb_audio_type->tooltip("Audio type (need ffmpeg)");
            cb_audio_type->down_box(FL_BORDER_BOX);
            cb_audio_type->labeltype(FL_NO_LABEL);
            cb_audio_type->align(Fl_Align(FL_ALIGN_RIGHT));
            cb_audio_type->deactivate();
          } // Fl_Choice* cb_audio_type
          { Fl_Box* o = new Fl_Box(145, 113, 360, 17);
            Fl_Group::current()->resizable(o);
          } // Fl_Box* o
          o->end();
        } // Fl_Group* o
        { Fl_Box* o = new Fl_Box(30, 103, 470, 17);
          Fl_Group::current()->resizable(o);
        } // Fl_Box* o
        setup_gui->end();
      } // Fl_Group* setup_gui
      { download_gui = new Fl_Group(30, 115, 475, 35);
        download_gui->hide();
        { progress = new Fl_Progress(30, 120, 475, 25);
          progress->box(FL_GLEAM_UP_BOX);
          progress->selection_color((Fl_Color)70);
        } // Fl_Progress* progress
        download_gui->end();
      } // Fl_Group* download_gui
      { Fl_Box* o = new Fl_Box(30, 103, 470, 17);
        Fl_Group::current()->resizable(o);
      } // Fl_Box* o
      o->end();
      Fl_Group::current()->resizable(o);
    } // Fl_Group* o
    { Fl_Menu_Bar* o = new Fl_Menu_Bar(-5, 0, 545, 25);
      o->box(FL_ENGRAVED_BOX);
      o->selection_color((Fl_Color)184);
      o->menu(menu_);
    } // Fl_Menu_Bar* o
    window->set_non_modal();
    window->end();
  } // Fl_Double_Window* window
}

AboutWindowUI::AboutWindowUI() {
  { window = new Fl_Double_Window(365, 310, "About Youtube downloader GUI");
    window->user_data((void*)(this));
    window->align(Fl_Align(FL_ALIGN_CLIP|FL_ALIGN_INSIDE));
    { br_about = new Fl_Help_View(25, 125, 315, 130);
      br_about->labelfont(8);
    } // Fl_Help_View* br_about
    { pb_close = new Fl_Button(105, 275, 145, 25, "Close");
    } // Fl_Button* pb_close
    { box_title = new Fl_Box(25, 5, 305, 25, "Youtube downloader GUI");
      box_title->labelfont(1);
    } // Fl_Box* box_title
    { Fl_Box* o = new Fl_Box(25, 30, 305, 25, "A GUI for the youtube downloader tool youtube-dl");
      o->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Box* o
    { pb_link = new Fl_Button(70, 95, 205, 25, "https://youtube-dl.org/");
      pb_link->box(FL_NO_BOX);
      pb_link->labelcolor((Fl_Color)217);
    } // Fl_Button* pb_link
    { Fl_Box* o = new Fl_Box(25, 65, 305, 25, "You can find the offical website for the youtube-dl tool");
      o->align(Fl_Align(FL_ALIGN_WRAP));
    } // Fl_Box* o
    window->set_modal();
    window->end();
  } // Fl_Double_Window* window
}
