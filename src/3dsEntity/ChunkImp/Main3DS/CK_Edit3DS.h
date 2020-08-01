//
// Created by lenovo on 2020/7/27.
//

#ifndef INC_3DS_PRINTER_CK_EDIT3DS_H
#define INC_3DS_PRINTER_CK_EDIT3DS_H

#include "Edit3DS/CK_Edit_Object.h"

class CK_Edit3DS: public Chunk {
public:
    CK_Edit3DS(unsigned short id, fstream & fp);
    void readSubChunks(fstream & fp);
};
#endif //INC_3DS_PRINTER_CK_EDIT3DS_H
