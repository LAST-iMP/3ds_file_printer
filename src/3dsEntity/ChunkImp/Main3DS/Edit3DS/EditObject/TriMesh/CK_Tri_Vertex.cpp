#ifndef CK_TRI_VERTEX_IMP
#define CK_TRI_VERTEX_IMP

#include "CK_Tri_Vertex.h"

CK_Tri_Vertex::CK_Tri_Vertex(unsigned short id, fstream & fp) : Chunk(id, fp) {
    readData(fp);
}

CK_Tri_Vertex::~CK_Tri_Vertex() {
delete vertex;
}

void CK_Tri_Vertex::readData(fstream & fp) {
    unsigned short n = readShort(fp);
    vertex = new vector<vector<float>>(n);
    for (int i = 0; i < n; ++i) {
        auto* v = new vector<float>({readFloat(fp), readFloat(fp), readFloat(fp)});
        (*vertex)[i] = *v;
    }
};

vector<vector<float>>& CK_Tri_Vertex::getData() {
    return *vertex;
}

unsigned int CK_Tri_Vertex::getRealLength() {
    return length;
}

#endif