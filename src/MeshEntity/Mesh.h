//
// Created by lenovo on 2020/7/29.
//

#ifndef INC_3DS_PRINTER_MESH_H
#define INC_3DS_PRINTER_MESH_H

#include "Mesh_Obj.h"

using namespace std;

class Mesh {
public:
    BoundingBox* boundingBox;
    vector<Mesh_Obj*>* meshes;

    explicit Mesh(CK_Edit3DS* edit3DS);
    virtual ~Mesh();
};


#endif //INC_3DS_PRINTER_MESH_H
