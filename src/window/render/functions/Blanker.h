//
// Created by lenovo on 2020/7/29.
//

#ifndef INC_3DS_PRINTER_BLANKER_H
#define INC_3DS_PRINTER_BLANKER_H

#include "windows.h"
#include "../Render_DATA.h"

class Blanker {
public:
    static void blank(RENDER_DATA& data);
    static bool check(Face* f);
};


#endif //INC_3DS_PRINTER_BLANKER_H
