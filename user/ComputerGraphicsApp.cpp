/***************************************************************
 * Name:      ComputerGraphicsApp.cpp
 * Purpose:   Code for Application Class
 * Author:    hyh (hyh199474 @icloud.com)
 * Created:   2016-05-10
 * Copyright: hyh ()
 * License:
 **************************************************************/

#include "ComputerGraphicsApp.h"

//(*AppHeaders
#include "ComputerGraphicsMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(ComputerGraphicsApp);

bool ComputerGraphicsApp::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	ComputerGraphicsFrame* Frame = new ComputerGraphicsFrame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
struct line
{
    int x1;
    int y1;
    int x2;
    int y2;
    COLORREF color;
    struct line* next;
};
struct line* first_line;
struct line* last_line;
int line_count = 0;
struct polygon
{
    struct line* polygon_line;
    struct polygon* next;
};
struct polygon* first_polygon = new polygon;
struct polygon* new_polygon = first_polygon;
struct polygon* last_polygon = first_polygon;
struct line* polygon_line;
int polygon_count = 0;
bool polygon_flag = FALSE;
bool polygon_complete = FALSE;

void Bresenham_line(int x1, int y1, int x2, int y2, COLORREF color)
{
    int i, interchange, s1, s2;
    int x, y;
    int dx, dy, dxy, d;
    HDC ActibeWindow = GetWindowDC(GetActiveWindow());

    x = x1;
    y = y1;
    dx = abs(x2 - x1);
    dy = abs(y2 - y1);
    s1 = (x2 - x1) > 0 ? 1 : -1;
    s2 = (y2 - y1) > 0 ? 1 : -1;

    if(dy > dx)
    {
        dxy = dx;
        dx = dy;
        dy = dxy;
        interchange = 1;
    }
    else
        interchange = 0;
    d = 2 * dy - dx;
    for(i = 1; i <= dx; i++)
    {
        SetPixel(ActibeWindow, x + 8, 650 - y, color);
        while(d >= 0)
        {
            if(interchange == 1)
                x = x + s1;
            else
                y = y + s2;
            d += (-2) * dx;
        }
        if(interchange == 1)
            y = y + s2;
        else
            x = x + s1;
        d += 2 * dy;
    }
}
void refresh()
{
    struct line* print_line = NULL;
    for(int i = 1; i <= line_count; i++)
    {
        if(i == 1)
        {
            Bresenham_line(first_line -> x1,
                           first_line -> y1,
                           first_line -> x2,
                           first_line -> y2,
                           first_line -> color);
            print_line = first_line -> next;
        }
        else
        {
            Bresenham_line(print_line -> x1,
                           print_line -> y1,
                           print_line -> x2,
                           print_line -> y2,
                           print_line -> color);
            print_line = print_line -> next;
        }
    }
    struct polygon* print_polygon = NULL;
    for(int i = 1; i <= polygon_count; i++)
    {
        if(i == 1)
        {
            print_line = first_polygon -> polygon_line;
            while(print_line != NULL)
            {
                Bresenham_line(print_line -> x1,
                               print_line -> y1,
                               print_line -> x2,
                               print_line -> y2,
                               print_line -> color);
                if(print_line -> next== NULL)
                {
                    Bresenham_line(first_polygon -> polygon_line -> x1,
                                   first_polygon -> polygon_line -> y1,
                                   print_line -> x2,
                                   print_line -> y2,
                                   print_line -> color);
                }
                print_line = print_line -> next;
            }
            print_polygon = first_polygon -> next;
        }
        else
        {
            print_line = print_polygon -> polygon_line;
            while(print_line != NULL)
            {
                Bresenham_line(print_line -> x1,
                               print_line -> y1,
                               print_line -> x2,
                               print_line -> y2,
                               print_line -> color);
                if(print_line -> next == NULL)
                {
                    Bresenham_line(print_polygon -> polygon_line -> x1,
                                   print_polygon -> polygon_line -> y1,
                                   print_line -> x2,
                                   print_line -> y2,
                                   print_line -> color);
                }
                print_line = print_line -> next;
            }
            print_polygon = first_polygon -> next;
        }
    }
}

int wxStringtoInt(wxTextCtrl* TextCtrl)
{
    std::string s;
    std::stringstream ss;
    int i;

    s = std::string(TextCtrl -> GetValue());
    ss << s;
    ss >> i;
    return i;
}
void creat_line(int x1, int y1, int x2, int y2, COLORREF color)
{
    if(line_count)
    {
        last_line -> next = new struct line;
        last_line = last_line -> next;
        *last_line = {x1, y1, x2, y2, color, NULL};
        line_count++;
    }
    else
    {
        first_line = new struct line;
        last_line = first_line;
        *first_line = {x1, y1, x2, y2, color, NULL};
        line_count++;
    }
    Bresenham_line(x1, y1, x2, y2, color);
}
void delete_line(int line_num)
{
    struct line* delete_l = NULL;
    struct line* delete_l_pre = NULL;

    if(line_num == 1)
    {
        delete_l = first_line;
        first_line = first_line -> next;
        Bresenham_line(delete_l -> x1,
                       delete_l -> y1,
                       delete_l -> x2,
                       delete_l -> y2,
                       RGB(255, 255, 255));
        delete delete_l;
        line_count--;
    }
    else
    {
        for(int i = 1; i <= line_num; i++)
        {
            if(i == 1)
            {
                delete_l = first_line;
            }
            else
            {
                delete_l_pre = delete_l;
                delete_l = delete_l -> next;
            }
        }
        if(line_num == line_count)
        {
            delete_l_pre -> next = delete_l -> next;
            last_line = delete_l_pre;
            Bresenham_line(delete_l -> x1,
                           delete_l -> y1,
                           delete_l -> x2,
                           delete_l -> y2,
                           RGB(255, 255, 255));
            delete delete_l;
            line_count--;
        }
        else
        {
            delete_l_pre -> next = delete_l -> next;
            Bresenham_line(delete_l -> x1,
                           delete_l -> y1,
                           delete_l -> x2,
                           delete_l -> y2,
                           RGB(255, 255, 255));
            delete delete_l;
            line_count--;
        }
    }
    refresh();
}
POINT GetMousePos()
{
    POINT point;
    GetCursorPos(&point);
    ScreenToClient(GetActiveWindow(),&point);
    return point;
}
void creat_polygon(int x1, int y1, int x2, int y2, COLORREF color)
{
    if(!polygon_flag)
    {
        new_polygon -> polygon_line = new line;
        polygon_line = new_polygon -> polygon_line;
        *polygon_line = {x1, y1, x2, y2, color, NULL};
        Bresenham_line(x1, y1, x2, y2, color);
        polygon_flag = TRUE;
    }
    else
    {
        polygon_line -> next = new line;
        polygon_line = polygon_line -> next;
        *polygon_line = {x1, y1, x2, y2, color, NULL};
        Bresenham_line(x1, y1, x2, y2, color);
        polygon_complete = TRUE;
    }
}
void complete_polygon(COLORREF color)
{
    Bresenham_line(new_polygon -> polygon_line -> x1,
                   new_polygon -> polygon_line -> y1,
                   polygon_line -> x2,
                   polygon_line -> y2,
                   color);
    polygon_flag = FALSE;
    new_polygon -> next = new polygon;
    new_polygon = new_polygon -> next;
    polygon_complete = FALSE;
    polygon_count++;
}
void delete_polygon(int polygon_num)
{
    struct polygon* delete_p = NULL;
    struct polygon* delete_p_pre = NULL;
    struct line* print_line = NULL;

    if(polygon_num == 1)
    {
        delete_p = first_polygon;
        first_polygon = first_polygon -> next;
        print_line = delete_p -> polygon_line;
        while(print_line != NULL)
        {
            Bresenham_line(print_line -> x1,
                           print_line -> y1,
                           print_line -> x2,
                           print_line -> y2,
                           RGB(255, 255, 255));
            if(print_line -> next == NULL)
                {
                    Bresenham_line(delete_p -> polygon_line -> x1,
                                   delete_p -> polygon_line -> y1,
                                   print_line -> x2,
                                   print_line -> y2,
                                   RGB(255, 255, 255));
                }
            print_line = print_line -> next;
        }
        delete delete_p;
        polygon_count--;
    }
    else
    {
        for(int i = 1; i <= polygon_num; i++)
        {
            if(i == 1)
            {
                delete_p = first_polygon;
            }
            else
            {
                delete_p_pre = delete_p;
                delete_p = delete_p -> next;
            }
        }
        if(polygon_num == polygon_count)
        {
            delete_p_pre -> next = delete_p -> next;
            last_polygon = delete_p_pre;
            print_line = delete_p -> polygon_line;
            while(print_line != NULL)
            {
                Bresenham_line(print_line -> x1,
                               print_line -> y1,
                               print_line -> x2,
                               print_line -> y2,
                               RGB(255, 255, 255));
                if(print_line -> next == NULL)
                {
                    Bresenham_line(delete_p -> polygon_line -> x1,
                                   delete_p -> polygon_line -> y1,
                                   print_line -> x2,
                                   print_line -> y2,
                                   RGB(255, 255, 255));
                }
                print_line = print_line -> next;
            }
            delete delete_p;
            polygon_count--;
        }
        else
        {
            delete_p_pre -> next = delete_p -> next;
            print_line = delete_p -> polygon_line;
            while(print_line != NULL)
            {
                Bresenham_line(print_line -> x1,
                               print_line -> y1,
                               print_line -> x2,
                               print_line -> y2,
                               RGB(255, 255, 255));
                if(print_line -> next == NULL)
                {
                    Bresenham_line(delete_p -> polygon_line -> x1,
                                   delete_p -> polygon_line -> y1,
                                   print_line -> x2,
                                   print_line -> y2,
                                   RGB(255, 255, 255));
                }
                print_line = print_line -> next;
            }
            delete delete_p;
            polygon_count--;
        }
    }
    refresh();
}

