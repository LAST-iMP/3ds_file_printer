//
// Created by lenovo on 2020/7/28.
//

#ifndef INC_3DS_PRINTER_RENDER_H
#define INC_3DS_PRINTER_RENDER_H

#include <string>
#include <Windows.h>
#include "functions/rasterization/Rasterization_DATA.h"
#include "functions/lightTracer/LT_Data.h"
#include "../WindowInfo.h"
#include "../../3dsEntity/Chunks.h"
#include "functions/rasterization/Blanker.h"
#include "functions/rasterization/Cutter.h"
#include "functions/rasterization/components/Z_Buffer.h"
#include "functions/lightTracer/LightTracer.h"

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
    void rasterization(BYTE* buffer, RECT& rect, int length);
    void lightTracer(BYTE* buffer, RECT& rect);
    void lightTracer(HDC& hdc, RECT &rect);
};


#endif //INC_3DS_PRINTER_RENDER_H
