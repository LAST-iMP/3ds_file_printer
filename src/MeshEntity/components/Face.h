//
// Created by lenovo on 2020/7/26.
//

#ifndef INC_3DS_PRINTER_FACE_H
#define INC_3DS_PRINTER_FACE_H

#include "HalfEdge.h"
#include <unordered_map>

class Face {
private:
    vector<Vertex*>* vertexes;
    vector<HalfEdge*>* edges;
    vector<float>* normalVector = nullptr;

    HalfEdge* generateEdge(Vertex* origin, Vertex* target, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges);
    void init(vector<unsigned short>& index, vector<Vertex*>& vertex, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges);

public:
    Face(vector<unsigned short>& index, vector<Vertex*>& vertex, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges);
    virtual ~Face();

    vector<float>& getNormalVector();
    vector<HalfEdge*>& getEdges() {return *edges;}
};


#endif //INC_3DS_PRINTER_FACE_H
