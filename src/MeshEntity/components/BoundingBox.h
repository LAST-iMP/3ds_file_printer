#ifndef INC_3DS_PRINTER_BOUNDINGBOX_H
#define INC_3DS_PRINTER_BOUNDINGBOX_H

#include "Vertex.h"
#include <vector>

using namespace std;

class BoundingBox {
public:
    float xMin, xMax, yMin, yMax, zMin, zMax;

    BoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax);
    BoundingBox(BoundingBox* boundingBox);
    explicit BoundingBox(vector<Vertex*>& vertexes);
    virtual ~BoundingBox();

    void expand(BoundingBox* boundingBox);
};


#endif //INC_3DS_PRINTER_BOUNDINGBOX_H
