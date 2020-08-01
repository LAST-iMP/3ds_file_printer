//
// Created by lenovo on 2020/7/27.
//

#ifndef INC_3DS_PRINTER_CK_UNKNOWN_H
#define INC_3DS_PRINTER_CK_UNKNOWN_H

#include "../Chunk.h"

class CK_Unknown: public Chunk {
private:
    char* data;
    void readData(fstream & fp);
public:
    CK_Unknown(unsigned short id, fstream &fp);
    ~CK_Unknown() override;
    unsigned int getRealLength() override;
    char* getData();
};
#endif //INC_3DS_PRINTER_CK_UNKNOWN_H
