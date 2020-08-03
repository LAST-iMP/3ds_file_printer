//
// Created by lenovo on 2020/7/29.
//

#ifndef INC_3DS_PRINTER_CUTTER_H
#define INC_3DS_PRINTER_CUTTER_H

#include "windows.h"
#include "../Render_DATA.h"

class Cutter {
public:
    static void cut(RECT & rect, RENDER_DATA & data);

private:
    static void checkLocation(unordered_set<Face*>& faces, RECT& rect);
};


#endif //INC_3DS_PRINTER_CUTTER_H
