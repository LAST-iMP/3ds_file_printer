//
// Created by lenovo on 2020/7/27.
//

#ifndef INC_3DS_PRINTER_CK_MAIN3DS_H
#define INC_3DS_PRINTER_CK_MAIN3DS_H

#include "Main3DS/CK_Edit3DS.h"

class CK_Main3DS: public Chunk {
public:
    CK_Main3DS(unsigned short id, fstream & fp);
    void readSubChunks(fstream & fp);
};
#endif //INC_3DS_PRINTER_CK_MAIN3DS_H
