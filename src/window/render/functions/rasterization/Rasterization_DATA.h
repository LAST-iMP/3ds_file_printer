#ifndef INC_3DS_PRINTER_RASTERIZATION_DATA_H
#define INC_3DS_PRINTER_RASTERIZATION_DATA_H

#include <unordered_set>
#include <queue>
#include "../../../../MeshEntity/Mesh.h"

using namespace std;

typedef struct DATA {
    priority_queue<Face*, vector<Face*>, less<Face*>>* fk;
    unordered_set<Face*>* faces;
    BoundingBox* boundingBox;

    explicit DATA(Mesh* mesh) {
        int size = 0;
        for (auto obj : *mesh->meshes) size += obj->getFaces().size();
        faces = new unordered_set<Face*>(size);
        for (auto obj : *mesh->meshes) {
            for (auto f : obj->getFaces()) {
                faces->insert(f);
            }
        }
        boundingBox = new BoundingBox(mesh->boundingBox);
    }

    virtual ~DATA() {
        delete faces;
        delete boundingBox;
    }

    int getSize() {
        return faces->size();
    }
} RENDER_DATA, *H_RENDER_DATA;

#endif //INC_3DS_PRINTER_RASTERIZATION_DATA_H
