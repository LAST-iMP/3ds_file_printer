//
// Created by lenovo on 2020/7/28.
//

#ifndef INC_3DS_PRINTER_RENDER_H
#define INC_3DS_PRINTER_RENDER_H

#include <iostream>
#include <string>
#include <Windows.h>
#include "Render_DATA.h"
#include "../WindowInfo.h"
#include "../../3dsEntity/Chunks.h"
#include "functions/Blanker.h"
#include "functions/Cutter.h"
#include "functions/Rasterize.h"

using namespace std;

class Render {
public:
    Render(const string& filePath);
    virtual ~Render();

    void draw(HWND hwnd);

private:
    Mesh* mesh;

    static CK_Main3DS* load(const string& filePath);
    static CK_Main3DS* startRead(fstream &fp);
    static Mesh* transform(CK_Main3DS* m);

    void doubleBuffer(HDC hdc,RECT *rect);
    void fillBuffer(BYTE* buffer, RECT& rect, int length);
};


#endif //INC_3DS_PRINTER_RENDER_H
