/***************************************************************
 * Name:      ComputerGraphicsMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    hyh (hyh199474@icloud.com)
 * Created:   2016-05-10
 * Copyright: hyh ()
 * License:
 **************************************************************/

#include "ComputerGraphicsMain.h"
#include <wx/msgdlg.h>
#include <wx/colour.h>
//(*InternalHeaders(ComputerGraphicsFrame)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)
extern void Bresenham_line(int x1, int y1, int x2, int y2, COLORREF color);
extern int wxStringtoInt(wxTextCtrl* TextCtrl);
extern void creat_line(int x1, int y1, int x2, int y2, COLORREF color);
extern void delete_line(int line_num);
extern void creat_polygon(int x1, int y1, int x2, int y2, COLORREF color);
extern void delete_polygon(int polygon_num);
extern int line_count;
extern bool polygon_flag;
extern bool polygon_complete;
extern int polygon_count;
extern void complete_polygon(COLORREF color);
extern POINT GetMousePos();
//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(ComputerGraphicsFrame)
const long ComputerGraphicsFrame::ID_BUTTON1 = wxNewId();
const long ComputerGraphicsFrame::ID_BUTTON2 = wxNewId();
const long ComputerGraphicsFrame::ID_STATICTEXT1 = wxNewId();
const long ComputerGraphicsFrame::ID_STATICTEXT2 = wxNewId();
const long ComputerGraphicsFrame::ID_STATICTEXT3 = wxNewId();
const long ComputerGraphicsFrame::ID_STATICTEXT4 = wxNewId();
const long ComputerGraphicsFrame::ID_TEXTCTRL1 = wxNewId();
const long ComputerGraphicsFrame::ID_TEXTCTRL2 = wxNewId();
const long ComputerGraphicsFrame::ID_TEXTCTRL3 = wxNewId();
const long ComputerGraphicsFrame::ID_TEXTCTRL4 = wxNewId();
const long ComputerGraphicsFrame::ID_SASHWINDOW1 = wxNewId();
const long ComputerGraphicsFrame::ID_TEXTCTRL5 = wxNewId();
const long ComputerGraphicsFrame::ID_COLOURPICKERCTRL1 = wxNewId();
const long ComputerGraphicsFrame::ID_STATICTEXT5 = wxNewId();
const long ComputerGraphicsFrame::ID_STATICTEXT6 = wxNewId();
const long ComputerGraphicsFrame::ID_TEXTCTRL6 = wxNewId();
const long ComputerGraphicsFrame::ID_CHECKBOX1 = wxNewId();
const long ComputerGraphicsFrame::ID_BUTTON3 = wxNewId();
const long ComputerGraphicsFrame::ID_BUTTON4 = wxNewId();
const long ComputerGraphicsFrame::ID_STATICTEXT7 = wxNewId();
const long ComputerGraphicsFrame::idMenuQuit = wxNewId();
const long ComputerGraphicsFrame::idMenuAbout = wxNewId();
const long ComputerGraphicsFrame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(ComputerGraphicsFrame,wxFrame)
    //(*EventTable(ComputerGraphicsFrame)
       EVT_LEFT_DOWN(ComputerGraphicsFrame::OnSashWindow1SashDragged2)
    //*)
END_EVENT_TABLE()

ComputerGraphicsFrame::ComputerGraphicsFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(ComputerGraphicsFrame)
    wxMenuItem* MenuItem2;
    wxMenuItem* MenuItem1;
    wxMenu* Menu1;
    wxMenuBar* MenuBar1;
    wxMenu* Menu2;

    Create(parent, wxID_ANY, _("直线与多边形绘制"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(1000,700));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENU));
    Button1 = new wxButton(this, ID_BUTTON1, _("创建"), wxPoint(370,52), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button2 = new wxButton(this, ID_BUTTON2, _("删除直线"), wxPoint(780,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("x1"), wxPoint(20,20), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    StaticText2 = new wxStaticText(this, ID_STATICTEXT2, _("x2"), wxPoint(20,60), wxDefaultSize, 0, _T("ID_STATICTEXT2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("y1"), wxPoint(200,20), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("y2"), wxPoint(200,60), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxPoint(60,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->SetToolTip(_("起始点x坐标"));
    TextCtrl1->SetHelpText(_("起始点x坐标"));
    TextCtrl2 = new wxTextCtrl(this, ID_TEXTCTRL2, wxEmptyString, wxPoint(240,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL2"));
    TextCtrl2->SetToolTip(_("起始点y坐标"));
    TextCtrl2->SetHelpText(_("起始点y坐标"));
    TextCtrl3 = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(60,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    TextCtrl3->SetToolTip(_("终点x坐标"));
    TextCtrl3->SetHelpText(_("终点x坐标"));
    TextCtrl4 = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxPoint(240,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    TextCtrl4->SetToolTip(_("终点y坐标"));
    TextCtrl4->SetHelpText(_("终点y坐标"));
    SashWindow1 = new wxSashWindow(this, ID_SASHWINDOW1, wxPoint(0,100), wxSize(1000,500), wxCLIP_CHILDREN, _T("ID_SASHWINDOW1"));
    SashWindow1->Disable();
    SashWindow1->SetForegroundColour(wxColour(255,255,255));
    SashWindow1->SetBackgroundColour(wxColour(255,255,255));
    SashWindow1->SetSashVisible(wxSASH_TOP,    false);
    SashWindow1->SetSashVisible(wxSASH_BOTTOM, false);
    SashWindow1->SetSashVisible(wxSASH_LEFT,   false);
    SashWindow1->SetSashVisible(wxSASH_RIGHT,  false);
    TextCtrl5 = new wxTextCtrl(this, ID_TEXTCTRL5, wxEmptyString, wxPoint(640,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL5"));
    TextCtrl5->SetToolTip(_("输入要删除第几条直线"));
    TextCtrl5->SetHelpText(_("输入要删除第几条直线"));
    ColourPickerCtrl1 = new wxColourPickerCtrl(this, ID_COLOURPICKERCTRL1, wxColour(0,0,0), wxPoint(365,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_COLOURPICKERCTRL1"));
    StaticText5 = new wxStaticText(this, ID_STATICTEXT5, _("已绘制0条直线"), wxPoint(32,624), wxSize(120,18), 0, _T("ID_STATICTEXT5"));
    StaticText6 = new wxStaticText(this, ID_STATICTEXT6, _("可直接点击画布绘制直线，勾选绘制多边形则绘制多边形"), wxPoint(560,624), wxDefaultSize, 0, _T("ID_STATICTEXT6"));
    TextCtrl6 = new wxTextCtrl(this, ID_TEXTCTRL6, wxEmptyString, wxPoint(640,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_TEXTCTRL6"));
    TextCtrl6->SetToolTip(_("输入要删除第几个多边形"));
    CheckBox1 = new wxCheckBox(this, ID_CHECKBOX1, _("创建多边形"), wxPoint(500,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    CheckBox1->SetValue(false);
    Button3 = new wxButton(this, ID_BUTTON3, _("完成多边形"), wxPoint(500,52), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    Button4 = new wxButton(this, ID_BUTTON4, _("删除多边形"), wxPoint(780,56), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    StaticText7 = new wxStaticText(this, ID_STATICTEXT7, _("已绘制0个多边形"), wxPoint(200,624), wxDefaultSize, 0, _T("ID_STATICTEXT7"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnButton1Click1);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnButton2Click);
    Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnTextCtrl1Text);
    Connect(ID_SASHWINDOW1,wxEVT_SASH_DRAGGED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnSashWindow1SashDragged);
    Connect(ID_COLOURPICKERCTRL1,wxEVT_COMMAND_COLOURPICKER_CHANGED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnColourPickerCtrl1ColourChanged);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnCheckBox1Click1);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnButton3Click);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnButton4Click);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&ComputerGraphicsFrame::OnAbout);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&ComputerGraphicsFrame::OnClose);
    //*)
}

ComputerGraphicsFrame::~ComputerGraphicsFrame()
{
    //(*Destroy(ComputerGraphicsFrame)
    //*)
}

void ComputerGraphicsFrame::OnQuit(wxCommandEvent& event)
{
    Destroy();
}

void ComputerGraphicsFrame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void ComputerGraphicsFrame::OnButton1Click1(wxCommandEvent& event)
{
    int x1, y1, x2, y2;

    x1 = wxStringtoInt(TextCtrl1);
    y1 = wxStringtoInt(TextCtrl2);
    x2 = wxStringtoInt(TextCtrl3);
    y2 = wxStringtoInt(TextCtrl4);
    if(!CheckBox1 -> GetValue())
    {
        if(x1 >=0 && x1 <= 1000
           &&y1 >=0 && y1 <= 500
           &&x2 >=0 && x2 <= 1000
           &&y2 >=0 && y2 <= 500)
        {
            creat_line(x1, y1, x2, y2, ColourPickerCtrl1 -> wxColourPickerCtrl::GetColour().GetRGB());
            std::stringstream ss;
            std::string s;
            ss << "已绘制" << line_count << "条直线";
            ss >> s;
            StaticText5 -> SetLabel(s);
        }
        else
            wxMessageBox("x坐标为0-1000，y坐标为0-500", _("Error"));
    }
    else
    {
        if(x1 >=0 && x1 <= 1000
           &&y1 >=0 && y1 <= 500
           &&x2 >=0 && x2 <= 1000
           &&y2 >=0 && y2 <= 500)
        {
            creat_polygon(x1, y1, x2, y2, ColourPickerCtrl1 -> wxColourPickerCtrl::GetColour().GetRGB());
            std::stringstream ss1;
            std::string s1;
            ss1 << x2;
            ss1 >> s1;
            TextCtrl1 -> SetLabel(s1);
            std::stringstream ss2;
            std::string s2;
            ss2 << y2;
            ss2 >> s2;
            TextCtrl2 -> SetLabel(s2);
            TextCtrl3 -> SetLabel("");
            TextCtrl4 -> SetLabel("");
            TextCtrl1 -> Enable(FALSE);
            TextCtrl2 -> Enable(FALSE);
        }
        else
            wxMessageBox("x坐标为0-1000，y坐标为0-500", _("Error"));
    }
}

void ComputerGraphicsFrame::OnClose(wxCloseEvent& event)
{
}

void ComputerGraphicsFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
}

void ComputerGraphicsFrame::OnButton2Click(wxCommandEvent& event)
{
    int delete_num;

    delete_num = wxStringtoInt(TextCtrl5);
    if(delete_num <= line_count)
    {
        delete_line(delete_num);
        std::stringstream ss;
        std::string s;
        ss << "已绘制" << line_count << "条直线";
        ss >> s;
        StaticText5 -> SetLabel(s);
    }
    else
        wxMessageBox("并没有那么多直线", _("Error"));
}

void ComputerGraphicsFrame::OnColourPickerCtrl1ColourChanged(wxColourPickerEvent& event)
{
}

void ComputerGraphicsFrame::OnSashWindow1SashDragged(wxSashEvent& event)
{
}
POINT point1, point2;
bool ClickCount = FALSE;
void ComputerGraphicsFrame::OnSashWindow1SashDragged2(wxMouseEvent& event)
{
    if(!CheckBox1 -> GetValue())
    {
        if(!ClickCount)
        {
            point1 = GetMousePos();
            if(point1.y >= 100 && point1.y <= 600)
            ClickCount = TRUE;
        }
        else
        {
            point2 = GetMousePos();
            if(point2.y >= 100 && point2.y <= 600)
            {
                creat_line(point1.x,
                           600 - point1.y,
                           point2.x,
                           600 - point2.y,
                           ColourPickerCtrl1 -> wxColourPickerCtrl::GetColour().GetRGB());
                std::stringstream ss;
                std::string s;
                ss << "已绘制" << line_count << "条直线";
                ss >> s;
                StaticText5 -> SetLabel(s);
                ClickCount = FALSE;
            }
        }
    }
    else
    {
        if(!ClickCount)
        {
            point1 = GetMousePos();
            if(point1.y >= 100 && point1.y <= 600)
                ClickCount = TRUE;
        }
        else
        {
            point2 = GetMousePos();
            if(point2.y >= 100 && point2.y <= 600)
            {
                creat_polygon(point1.x,
                              600 - point1.y,
                              point2.x,
                              600 - point2.y,
                              ColourPickerCtrl1 -> wxColourPickerCtrl::GetColour().GetRGB());
                point1.x = point2.x;
                point1.y = point2.y;
            }
        }
    }
}

void ComputerGraphicsFrame::OnCheckBox1Click(wxCommandEvent& event)
{
}

void ComputerGraphicsFrame::OnCheckBox1Click1(wxCommandEvent& event)
{
}

void ComputerGraphicsFrame::OnButton3Click(wxCommandEvent& event)
{
    if(ClickCount && polygon_flag && polygon_complete)
    {
        complete_polygon(ColourPickerCtrl1 -> wxColourPickerCtrl::GetColour().GetRGB());
        std::stringstream ss;
        std::string s;
        ss << "已绘制" << polygon_count << "个多边形";
        ss >> s;
        StaticText7 -> SetLabel(s);
        ClickCount = FALSE;
    }
    else if(polygon_flag && polygon_complete)
    {
        complete_polygon(ColourPickerCtrl1 -> wxColourPickerCtrl::GetColour().GetRGB());
        std::stringstream ss;
        std::string s;
        ss << "已绘制" << polygon_count << "个多边形";
        ss >> s;
        StaticText7 -> SetLabel(s);
        TextCtrl1 -> Enable(TRUE);
        TextCtrl2 -> Enable(TRUE);
    }
    else
    {
        wxMessageBox("至少需要三个点才能完成多边形", _("Error"));
    }
}

void ComputerGraphicsFrame::OnButton4Click(wxCommandEvent& event)
{
    int delete_num;

    delete_num = wxStringtoInt(TextCtrl6);
    if(delete_num <= polygon_count)
    {
        delete_polygon(delete_num);
        std::stringstream ss;
        std::string s;
        ss << "已绘制" << polygon_count << "个多边形";
        ss >> s;
        StaticText7 -> SetLabel(s);
    }
    else
        wxMessageBox("并没有那么多多边形", _("Error"));
}
