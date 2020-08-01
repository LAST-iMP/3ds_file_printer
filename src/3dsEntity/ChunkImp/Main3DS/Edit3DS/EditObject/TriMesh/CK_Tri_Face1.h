#ifndef INC_3DS_PRINTER_CK_TRI_FACE1_H
#define INC_3DS_PRINTER_CK_TRI_FACE1_H

#include "../../../../CK_Unknown.h"

class CK_Tri_Face1: public Chunk {
private:
    vector<vector<unsigned short>>* faces = nullptr;

public:
    CK_Tri_Face1(unsigned short id, fstream & fp);
    ~CK_Tri_Face1() override;
    void readData(fstream & fp);
    void readSubChunks(fstream & fp);
    vector<vector<unsigned short>>& getData();
    unsigned int getRealLength() override;
};

#endif //INC_3DS_PRINTER_CK_TRI_FACE1_H
