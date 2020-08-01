#ifndef CK_TRI_FACE1_IMP
#define CK_TRI_FACE1_IMP

#include "CK_Tri_Face1.h"

CK_Tri_Face1::CK_Tri_Face1(unsigned short id, fstream & fp) : Chunk(id, fp) {
    readData(fp);
    readSubChunks(fp);
}

CK_Tri_Face1::~CK_Tri_Face1() {
    delete faces;
}

void CK_Tri_Face1::readData(fstream & fp) {
    unsigned short n = readShort(fp);
    faces = new vector<vector<unsigned short>>(n);
    for (int i = 0; i < n; ++i) {
        auto* v = new vector<unsigned short>({readShort(fp), readShort(fp), readShort(fp), readShort(fp)});
        (*faces)[i] = (*v);
    }
};

void CK_Tri_Face1::readSubChunks(fstream & fp) {
    while (getRealLength() < length) {
        unsigned short nextid = readShort(fp);
        Chunk* sub = generate<CK_Unknown>(nextid, fp);
        addSubChunk(nextid, sub);
    }
}

vector<vector<unsigned short>>& CK_Tri_Face1::getData() {
    return *faces;
}

unsigned int CK_Tri_Face1::getRealLength() {
    unsigned int result = 6 + (*faces).size() * 4 * 2 + 2;
    return result + getSubChunkLength();
}

#endif