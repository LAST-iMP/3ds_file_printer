#include "BoundingBox.h"

BoundingBox::BoundingBox(vector<Vertex*>& vertexes) {
    xMin = min(vertexes[0]->getX(), min(vertexes[1]->getX(), vertexes[2]->getX()));
    xMax = max(vertexes[0]->getX(), max(vertexes[1]->getX(), vertexes[2]->getX()));
    yMin = min(vertexes[0]->getY(), min(vertexes[1]->getY(), vertexes[2]->getY()));
    yMax = max(vertexes[0]->getY(), max(vertexes[1]->getY(), vertexes[2]->getY()));
    zMin = min(vertexes[0]->getZ(), min(vertexes[1]->getZ(), vertexes[2]->getZ()));
    zMax = max(vertexes[0]->getZ(), max(vertexes[1]->getZ(), vertexes[2]->getZ()));
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

BoundingBox::BoundingBox(float xMin, float xMax, float yMin, float yMax, float zMin, float zMax) {
    this->xMax = xMax;
    this->xMin = xMin;
    this->yMax = yMax;
    this->yMin = yMin;
    this->zMax = zMax;
    this->zMin = zMin;
}
