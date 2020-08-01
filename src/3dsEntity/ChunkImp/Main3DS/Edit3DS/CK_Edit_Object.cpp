#ifndef CK_EDIT_OBJECT_IMP
#define CK_EDIT_OBJECT_IMP

#include "CK_Edit_Object.h"

CK_Edit_Object::CK_Edit_Object(unsigned short id, fstream & fp) : Chunk(id, fp) {
    this->readData(fp);
    this->readSubChunks(fp);
}

CK_Edit_Object::~CK_Edit_Object(){
    delete name;
}

void CK_Edit_Object::readSubChunks(fstream & fp) {
    while (getRealLength() != length) {
        unsigned short nextid = readShort(fp);
        Chunk* sub;
        switch (nextid) {
            case OBJ_TRIMESH: sub = generate<CK_Obj_TriMesh>(nextid, fp); break;
            default: sub = generate<CK_Unknown>(nextid, fp); break;
        }
        addSubChunk(nextid, sub);
    }
}

void CK_Edit_Object::readData(fstream & fp) {
    name = new vector<char>();
    char buffer;
    do {
        fp.read(&buffer, 1);
        (*name).push_back(buffer);
    } while (buffer != 0);
};

vector<char>& CK_Edit_Object::getData() {
    return (*name);
}

unsigned int CK_Edit_Object::getRealLength() {
    unsigned int result = 6 + name->size();
    return result + getSubChunkLength();
}

#endif