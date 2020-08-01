#ifndef CK_TRI_LOCAL_IMP
#define CK_TRI_LOCAL_IMP

#include "CK_Tri_Local.h"

CK_Tri_Local::CK_Tri_Local(unsigned short id, fstream & fp) : Chunk(id, fp) {
    readData(fp);
}

CK_Tri_Local::~CK_Tri_Local() {
    delete vertex;
}

void CK_Tri_Local::readData(fstream & fp) {
    vertex = new vector<vector<float>>(4);
    for (int i = 0; i < 4; ++i) {
        auto* v = new vector<float>({readFloat(fp), readFloat(fp), readFloat(fp)});
        (*vertex)[i] = (*v);
    }
};

vector<vector<float>>& CK_Tri_Local::getData() {
    return *vertex;
}

unsigned int CK_Tri_Local::getRealLength() {
    return length;
}

#endif