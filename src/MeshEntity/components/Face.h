//
// Created by lenovo on 2020/7/26.
//

#ifndef INC_3DS_PRINTER_FACE_H
#define INC_3DS_PRINTER_FACE_H

#include "BoundingBox.h"
#include "HalfEdge.h"
#include <unordered_map>
#include <cmath>

class Face {
private:
    vector<Vertex*>* vertexes;
    vector<HalfEdge*>* edges;
    Vector3D* normalVector = nullptr;

    HalfEdge* generateEdge(Vertex* origin, Vertex* target, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges);
    void init(vector<unsigned short>& index, vector<Vertex*>& vertex, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges);

public:
    Face(vector<unsigned short>& index, vector<Vertex*>& vertex, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges);
    virtual ~Face();

    BoundingBox* boundingBox;

    Vector3D& getNormalVector();
    vector<HalfEdge*>& getEdges() {return *edges;}
    vector<Vertex*>& getVertexes() {return *vertexes;}
    bool operator < (Face& f) const {
        return this->boundingBox->yMin > f.boundingBox->yMin;
    }
};


#endif //INC_3DS_PRINTER_FACE_H
