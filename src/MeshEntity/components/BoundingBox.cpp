#include "BoundingBox.h"

BoundingBox::BoundingBox(vector<Vertex*>& vertexes) {
    xMin = min(vertexes[0]->x, min(vertexes[1]->x, vertexes[2]->x));
    xMax = max(vertexes[0]->x, max(vertexes[1]->x, vertexes[2]->x));
    yMin = min(vertexes[0]->y, min(vertexes[1]->y, vertexes[2]->y));
    yMax = max(vertexes[0]->y, max(vertexes[1]->y, vertexes[2]->y));
    zMin = min(vertexes[0]->z, min(vertexes[1]->z, vertexes[2]->z));
    zMax = max(vertexes[0]->z, max(vertexes[1]->z, vertexes[2]->z));
}

BoundingBox::BoundingBox(BoundingBox* boundingBox) {
    xMin = boundingBox->xMin;
    xMax = boundingBox->xMax;
    yMin = boundingBox->yMin;
    yMax = boundingBox->yMax;
    zMin = boundingBox->zMin;
    zMax = boundingBox->zMax;
}

BoundingBox::~BoundingBox() = default;

void BoundingBox::expand(BoundingBox *boundingBox) {
    xMin = min(xMin, boundingBox->xMin);
    xMax = max(xMax, boundingBox->xMax);
    yMin = min(yMin, boundingBox->yMin);
    yMax = max(yMax, boundingBox->yMax);
    zMin = min(zMin, boundingBox->zMin);
    zMax = max(zMax, boundingBox->zMax);
}
