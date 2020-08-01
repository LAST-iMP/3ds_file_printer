//
// Created by lenovo on 2020/7/27.
//

#ifndef INC_3DS_PRINTER_CK_TRI_VERTEX_H
#define INC_3DS_PRINTER_CK_TRI_VERTEX_H

#include "../../../../../Chunk.h"

class CK_Tri_Vertex: public Chunk {
private:
    vector<vector<float>>* vertex = nullptr;
public:
    CK_Tri_Vertex(unsigned short id, fstream & fp);
    ~CK_Tri_Vertex() override;
    void readData(fstream & fp);
    vector<vector<float>>& getData();
    unsigned int getRealLength() override;
};
#endif //INC_3DS_PRINTER_CK_TRI_VERTEX_H
