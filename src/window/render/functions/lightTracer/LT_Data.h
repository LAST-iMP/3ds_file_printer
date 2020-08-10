//
// Created by lenovo on 2020/8/8.
//

#ifndef INC_3DS_PRINTER_LT_DATA_H
#define INC_3DS_PRINTER_LT_DATA_H

#include <list>
#include <queue>
#include <cfloat>
#include "../../../../MeshEntity/Mesh.h"

class LT_Data {
public:
    LT_Data(Mesh* mesh, RECT& rect);
    LT_Data(Face* face, float xSize, float ySize, float zSize, RECT& rect);
    virtual ~LT_Data();

    bool operator<(LT_Data& data);
    pair<pair<float, Vector3D>, pair<Vector3D, Face *>> getFirstCross(
            pair<Vector3D, __decay_and_strip<Face *>::__type> start, Vector3D& direction);
private:
    float xLimit;
    float yLimit;
    float zLimit;
    BoundingBox* box;
    list<LT_Data*>* subNodes;
    list<Face*>* faces;
    RECT rect;

    static pair<pair<float, Vector3D>, pair<Vector3D, Face *>> empty;

    bool insert(Face* face);
    bool checkBox(Vector3D& start, Vector3D& direction);
    static pair<float, float> getRange(float dt, float start, float min, float max);
    pair<pair<float, Vector3D>, pair<Vector3D, Face *>> getFaceCross(Face* face, pair<Vector3D, Face *>& start, Vector3D& direction);
};


#endif //INC_3DS_PRINTER_LT_DATA_H
