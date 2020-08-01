#ifndef CK_Unknown_IMP
#define CK_Unknown_IMP

#include "CK_Unknown.h"

void CK_Unknown::readData(fstream & fp) {
    fp.read(this->data, length - 6);
}

CK_Unknown::CK_Unknown(unsigned short id, fstream &fp) : Chunk(id, fp) {
    this->data = new char[this->length-6];
    this->readData(fp);
}

CK_Unknown::~CK_Unknown() {
    delete (this->data);
}

unsigned int CK_Unknown::getRealLength() {
    return length;
}

char* CK_Unknown::getData() {
    return data;
}

#endif