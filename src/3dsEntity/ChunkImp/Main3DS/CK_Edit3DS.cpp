#ifndef CK_EDIT3DS_IMP
#define CK_EDIT3DS_IMP

#include "CK_Edit3DS.h"

CK_Edit3DS::CK_Edit3DS(unsigned short id, fstream & fp) : Chunk(id, fp) {
    this->readSubChunks(fp);
}

void CK_Edit3DS::readSubChunks(fstream & fp) {
    while (getRealLength() < length) {
        unsigned short nextid = readShort(fp);
        Chunk* sub;
        switch (nextid) {
            case EDIT_OBJECT: sub = generate<CK_Edit_Object>(nextid, fp); break;
            default: sub = generate<CK_Unknown>(nextid, fp); break;
        }
        addSubChunk(nextid, sub);
    }
}

#endif