//
// Created by lenovo on 2020/8/4.
//

#ifndef INC_3DS_PRINTER_Z_BUFFER_H
#define INC_3DS_PRINTER_Z_BUFFER_H

#include <windows.h>
#include "Edge_Node.h"
#include "../LightFilter.h"
#include "../Rasterization_DATA.h"
#include "../../../Render_Param.h"

using namespace std;

class Z_Buffer {
public:
    void doRasterize(RECT* rect, RENDER_DATA * data, BYTE* buffer, Vector3D * light);

private:
    RECT* rect;
    LightFilter * colorFilter;
    vector<vector<int>> distance;
    Vector3D * light;

    void r_Face(BYTE* buffer, Face& f);
};


#endif //INC_3DS_PRINTER_Z_BUFFER_H
