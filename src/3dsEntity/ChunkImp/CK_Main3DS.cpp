#ifndef CK_Main3DS_IMP
#define CK_Main3DS_IMP

#include "CK_Main3DS.h"

CK_Main3DS::CK_Main3DS(unsigned short id, fstream & fp) : Chunk(id, fp) {
    this->readSubChunks(fp);
}

void CK_Main3DS::readSubChunks(fstream & fp) {
    while (getRealLength() < length) {
        unsigned short nextid = readShort(fp);
        Chunk* sub;
        switch (nextid) {
            case EDIT3DS: sub = generate<CK_Edit3DS>(nextid, fp); break;
            default: sub = generate<CK_Unknown>(nextid, fp); break;
        }
        addSubChunk(nextid, sub);
    }
}

#endif