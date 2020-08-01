#ifndef CHUNK_IMP
#define CHUNK_IMP

#include "Chunk.h"

using namespace std;

Chunk::Chunk(unsigned short id, fstream & fp): id(id), length(Chunk::readInt(fp)) {}

Chunk::~Chunk() {
    auto iter = subChunks.begin();
    while (iter != subChunks.end()) {
        for (Chunk* c : *iter->second) delete c;
        delete(iter->second);
        iter++;
    }
    subChunks.clear();
}

unsigned int Chunk::getRealLength() {
    return getSubChunkLength() + 6;
}

void Chunk::addSubChunk(int id, Chunk *chunk) {
    auto iter = subChunks.find(id);
    if (iter == subChunks.end()) {
        auto newList = new vector<Chunk*>();
        newList->push_back(chunk);
        subChunks.insert(make_pair(id, newList));
    } else {
        iter->second->push_back(chunk);
    }
}

unsigned int Chunk::getSubChunkLength() {
    unsigned int result = 0;
    auto iter  = subChunks.begin();
    while (iter != subChunks.end()) {
        for (Chunk* c : *iter->second) result += c->getRealLength();
        iter++;
    }
    return result;
}

unsigned short Chunk::readShort(fstream & fp) {
    char buffer[2];
    fp.read(buffer, 2);
    return (unsigned char)buffer[0] + ((unsigned char)(buffer[1])<<8u);
}

unsigned int Chunk::readInt(fstream & fp) {
    unsigned int buffer[2] = {readShort(fp), readShort(fp)};
    return buffer[0] + (buffer[1]<<16u);
}

float Chunk::readFloat(fstream &fp) {
    char buffer[4];
    fp.read(buffer, 4);
    return *((float*)buffer);
}

#endif