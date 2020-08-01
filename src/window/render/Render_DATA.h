//
// Created by lenovo on 2020/7/29.
//

#ifndef INC_3DS_PRINTER_RENDER_DATA_H
#define INC_3DS_PRINTER_RENDER_DATA_H

#include <unordered_set>
#include "../../MeshEntity/Mesh.h"

using namespace std;

typedef struct DATA {
    unordered_set<Face*>* faces;
    int xMin;
    int xMax;

    explicit DATA(Mesh* mesh) {
        int size = 0;
        for (auto obj : mesh->getMeshes()) size += obj->getFaces().size();
        xMin = mesh->xMin;
        xMax = mesh->xMax;
        faces = new unordered_set<Face*>(size);
        for (auto obj : mesh->getMeshes()) {
            for (auto f : obj->getFaces()) {
                faces->insert(f);
            }
        }
    }

    virtual ~DATA() {
        delete faces;
    }

    int getSize() {
        return faces->size();
    }
} RENDER_DATA, *H_RENDER_DATA;

#endif //INC_3DS_PRINTER_RENDER_DATA_H
