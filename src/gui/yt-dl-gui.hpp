// generated by Fast Light User Interface Designer (fluid) version 1.0304

#ifndef yt_dl_gui_h
#define yt_dl_gui_h
#include <FL/Fl.H>
#include <FL/Fl_Double_Window.H>
#include <FL/Fl_Group.H>
#include <FL/Fl_Input.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_Check_Button.H>
#include <FL/Fl_Box.H>
#include <FL/Fl_Choice.H>
#include <FL/Fl_Progress.H>
#include <FL/Fl_Menu_Bar.H>

/**
 The main window of the program
*/
class MainWindowUI {
public:
  MainWindowUI();
  Fl_Double_Window *window;
  Fl_Group *setup_gui;
  Fl_Input *in_url;
  Fl_Button *pb_download;
  Fl_Check_Button *chk_audio_only;
  Fl_Choice *cb_audio_type;
  Fl_Group *download_gui;
  Fl_Progress *progress;
  static Fl_Menu_Item menu_[];
  static Fl_Menu_Item *menu_get_ytdl;
  static Fl_Menu_Item *menu_quit;
  static Fl_Menu_Item *menu_help;
  static Fl_Menu_Item *menu_about;
};
#include <FL/Fl_Help_View.H>

class AboutWindowUI {
public:
  AboutWindowUI();
  Fl_Double_Window *window;
  Fl_Help_View *br_about;
  Fl_Button *pb_close;
  Fl_Box *box_title;
  Fl_Button *pb_link;
};
#endif
