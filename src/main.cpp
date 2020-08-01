
#include <Windows.h>
#include "window/MainFrame.h"

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE hPreInstance, char* ipCmdLine, int nShowCmd) {
    MainFrame mainFrame(hinstance, hPreInstance, ipCmdLine, nShowCmd);
//    mainFrame.show("D:/program/c/3ds_printer/stairs4.3DS");
    mainFrame.show("C:/Users/lenovo/Documents/3dsMax/export/bridge1.3DS");
    return 0;
}

