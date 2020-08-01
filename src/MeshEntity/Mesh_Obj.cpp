#include "Mesh_Obj.h"

using namespace std;

void Mesh_Obj::initVertex(vector<vector<float>> &vertex_data) {
    vertexes = new vector<Vertex*>(vertex_data.size());
    for (int i = 0; i < vertexes->size(); ++i) {
        (*vertexes)[i] = new Vertex(vertex_data[i]);
        xMin = (i == 0)? (*vertexes)[i]->getIntX() : min(xMin, (*vertexes)[i]->getIntX());
        xMax = (i == 0)? (*vertexes)[i]->getIntX() : max(xMax, (*vertexes)[i]->getIntX());
    }
}

void Mesh_Obj::initFaces(vector<vector<unsigned short>> &face_data) {
    faces = new vector<Face*>(face_data.size());
    edges = new unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>();
    for (int i = 0; i < face_data.size(); ++i) {
        (*faces)[i] = new Face(face_data[i], *vertexes, *edges);
    }
}

Mesh_Obj::Mesh_Obj(CK_Obj_TriMesh *ref) {
    auto* vChunk = reinterpret_cast<CK_Tri_Vertex *>((*ref).getFirstSubChunk(TRI_VERTEX));
    auto* fChunk = reinterpret_cast<CK_Tri_Face1 *>((*ref).getFirstSubChunk(TRI_FACE1));
    initVertex(vChunk->getData());
    initFaces(fChunk->getData());
}

Mesh_Obj::~Mesh_Obj() {
    for (Vertex* v : *vertexes) delete v;
    delete vertexes;
    for (const auto oMap : *edges) {
        for (const auto& tMap : *oMap.second) {
            delete tMap.second;
        }
        delete oMap.second;
    }
    delete edges;
    for (Face* f : *faces) delete f;
    delete faces;
}

HalfEdge* Mesh_Obj::findEdge(Vertex *origin, Vertex *target) {
    auto iter1 = edges->find(origin);
    if (iter1 == edges->end()) return nullptr;
    auto iter2 = iter1->second->find(target);
    if (iter2 == iter1->second->end()) return nullptr;
    return iter2->second;
}
