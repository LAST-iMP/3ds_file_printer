//
// Created by lenovo on 2020/7/29.
//

#include "Mesh.h"

Mesh::Mesh(CK_Edit3DS* edit3DS) {
    auto editObject = edit3DS->getSubChunk(EDIT_OBJECT);
    this->meshes = new vector<Mesh_Obj*>(editObject->size());
    for (int i = 0; i < editObject->size(); ++i) {
        Chunk* mesh = (*editObject)[i]->getFirstSubChunk(OBJ_TRIMESH);
        (*meshes)[i] = (new Mesh_Obj(dynamic_cast<CK_Obj_TriMesh* >(mesh)));
        xMin = (i == 0)? (*meshes)[i]->xMin : min(xMin, (*meshes)[i]->xMin);
        xMax = (i == 0)? (*meshes)[i]->xMax : max(xMax, (*meshes)[i]->xMax);
    }
}

Mesh::~Mesh() {
    for (auto obj : *meshes) delete obj;
    delete meshes;
}
