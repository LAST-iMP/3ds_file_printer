//
// Created by lenovo on 2020/7/28.
//

#ifndef INC_3DS_PRINTER_MAINFRAME_H
#define INC_3DS_PRINTER_MAINFRAME_H

#include <iostream>
#include <tchar.h>
#include <Windows.h>
#include "render/Render.h"
#include "WindowInfo.h"

#define WINDOW_NAME "3dsReader"

class MainFrame {
public:

    MainFrame(HINSTANCE hinstance, HINSTANCE hPreInstance, char* ipCmdLine, int nShowCmd);
    virtual ~MainFrame();
    void show(const string& filePath);

private:
    HWND hwnd;
    HINSTANCE hinstance;
    HINSTANCE hPreInstance;
    static Render* render;

    static LRESULT CALLBACK wndProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam);
    bool registerWindow();
    int startListen(HWND hwnd);
};


#endif //INC_3DS_PRINTER_MAINFRAME_H
