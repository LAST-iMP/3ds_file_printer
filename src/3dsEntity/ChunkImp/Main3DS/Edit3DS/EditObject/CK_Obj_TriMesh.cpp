#ifndef CK_OBJ_TRI_MESH_IMP
#define CK_OBJ_TRI_MESH_IMP

#include "CK_Obj_TriMesh.h"

CK_Obj_TriMesh::CK_Obj_TriMesh(unsigned short id, fstream & fp) : Chunk(id, fp) {
    this->readSubChunks(fp);
}

void CK_Obj_TriMesh::readSubChunks(fstream & fp) {
    while (getRealLength() != length) {
        unsigned short nextid = readShort(fp);
        Chunk* sub;
        switch (nextid) {
            case TRI_VERTEX: sub = generate<CK_Tri_Vertex>(nextid, fp); break;
            case TRI_FACE1: sub = generate<CK_Tri_Face1>(nextid, fp); break;
            case TRI_LOCAL: sub = generate<CK_Tri_Local>(nextid, fp); break;
            default: sub = generate<CK_Unknown>(nextid, fp); break;
        }
        addSubChunk(nextid, sub);
    }
}

#endif