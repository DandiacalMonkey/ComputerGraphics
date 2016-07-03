/***************************************************************
 * Name:      ComputerGraphicsMain.h
 * Purpose:   Defines Application Frame
 * Author:    hyh (hyh199474@icloud.com)
 * Created:   2016-05-10
 * Copyright: hyh ()
 * License:
 **************************************************************/
#include <wx/colour.h>
#include <wx/event.h>
#include <sstream>
#include <string>
#ifndef COMPUTERGRAPHICSMAIN_H
#define COMPUTERGRAPHICSMAIN_H

//(*Headers(ComputerGraphicsFrame)
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/checkbox.h>
#include <wx/sashwin.h>
#include <wx/button.h>
#include <wx/frame.h>
#include <wx/clrpicker.h>
#include <wx/statusbr.h>
//*)

class ComputerGraphicsFrame: public wxFrame
{
    public:

        ComputerGraphicsFrame(wxWindow* parent,wxWindowID id = -1);
        virtual ~ComputerGraphicsFrame();

    private:

        //(*Handlers(ComputerGraphicsFrame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnButton1Click1(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnTextCtrl1Text(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        void OnColourPickerCtrl1ColourChanged(wxColourPickerEvent& event);
        void OnSashWindow1SashDragged(wxSashEvent& event);
        void OnSashWindow1SashDragged2(wxMouseEvent& event);
        void OnCheckBox1Click(wxCommandEvent& event);
        void OnCheckBox1Click1(wxCommandEvent& event);
        void OnButton3Click(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(ComputerGraphicsFrame)
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_STATICTEXT1;
        static const long ID_STATICTEXT2;
        static const long ID_STATICTEXT3;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL1;
        static const long ID_TEXTCTRL2;
        static const long ID_TEXTCTRL3;
        static const long ID_TEXTCTRL4;
        static const long ID_SASHWINDOW1;
        static const long ID_TEXTCTRL5;
        static const long ID_COLOURPICKERCTRL1;
        static const long ID_STATICTEXT5;
        static const long ID_STATICTEXT6;
        static const long ID_TEXTCTRL6;
        static const long ID_CHECKBOX1;
        static const long ID_BUTTON3;
        static const long ID_BUTTON4;
        static const long ID_STATICTEXT7;
        static const long idMenuQuit;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(ComputerGraphicsFrame)
        wxTextCtrl* TextCtrl4;
        wxButton* Button4;
        wxSashWindow* SashWindow1;
        wxStaticText* StaticText2;
        wxButton* Button1;
        wxStaticText* StaticText6;
        wxTextCtrl* TextCtrl6;
        wxStaticText* StaticText1;
        wxColourPickerCtrl* ColourPickerCtrl1;
        wxStaticText* StaticText3;
        wxButton* Button2;
        wxCheckBox* CheckBox1;
        wxButton* Button3;
        wxStaticText* StaticText5;
        wxStaticText* StaticText7;
        wxStatusBar* StatusBar1;
        wxTextCtrl* TextCtrl2;
        wxTextCtrl* TextCtrl1;
        wxTextCtrl* TextCtrl5;
        wxStaticText* StaticText4;
        wxTextCtrl* TextCtrl3;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // COMPUTERGRAPHICSMAIN_H
