//
// Created by lenovo on 2020/7/27.
//

#ifndef INC_3DS_PRINTER_CK_OBJ_TRIMESH_H
#define INC_3DS_PRINTER_CK_OBJ_TRIMESH_H

#include "TriMesh/CK_Tri_Face1.h"
#include "TriMesh/CK_Tri_Vertex.h"
#include "TriMesh/CK_Tri_Local.h"

class CK_Obj_TriMesh: public Chunk {
public:
    CK_Obj_TriMesh(unsigned short id, fstream & fp);
    void readSubChunks(fstream & fp);
};

#endif //INC_3DS_PRINTER_CK_OBJ_TRIMESH_H
