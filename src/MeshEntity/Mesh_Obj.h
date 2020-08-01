//
// Created by lenovo on 2020/7/26.
//

#ifndef INC_3DS_PRINTER_MESH_OBJ_H
#define INC_3DS_PRINTER_MESH_OBJ_H

#include <vector>
#include "../3dsEntity/Chunks.h"
#include "components/Vertex.h"
#include "components/Face.h"

using namespace std;

class Mesh_Obj {
private:
    vector<Face*>* faces = nullptr;
    unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>* edges = nullptr;
    vector<Vertex*>* vertexes = nullptr;

    void initVertex(vector<vector<float>>& vertex_data);
    void initFaces(vector<vector<unsigned short>>& face_data);

public:
    int xMin;
    int xMax;

    explicit Mesh_Obj(CK_Obj_TriMesh* ref);
    virtual ~Mesh_Obj();

    HalfEdge* findEdge(Vertex* origin, Vertex* target);

    vector<Face*>& getFaces() {return *faces;}
    unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& getEdges() {return *edges;}
};


#endif //INC_3DS_PRINTER_MESH_OBJ_H
