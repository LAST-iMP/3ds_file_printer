#include "Face.h"

Face::Face(vector<unsigned short>& index, vector<Vertex*>& vertex, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges) {
    vertexes = new vector<Vertex*>(3);
    edges = new vector<HalfEdge*>(3);
    init(index, vertex, meshEdges);
}

Face::~Face() {
    delete normalVector;
    delete vertexes;
    delete edges;
}

void Face::init(vector<unsigned short>& index, vector<Vertex*>& vertex, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges) {
    (*vertexes)[0] = vertex[index[0]];
    (*vertexes)[1] = vertex[index[1]];
    (*vertexes)[2] = vertex[index[2]];

    (*edges)[0] = generateEdge((*vertexes)[0], (*vertexes)[1], meshEdges);
    (*edges)[1] = generateEdge((*vertexes)[1], (*vertexes)[2], meshEdges);
    (*edges)[2] = generateEdge((*vertexes)[2], (*vertexes)[0], meshEdges);

    (*edges)[0]->setNext((*edges)[1]);
    (*edges)[0]->setPrevious((*edges)[2]);
    (*edges)[0]->setOpposite(generateEdge((*vertexes)[1], (*vertexes)[0], meshEdges));

    (*edges)[1]->setNext((*edges)[2]);
    (*edges)[1]->setPrevious((*edges)[0]);
    (*edges)[1]->setOpposite(generateEdge((*vertexes)[2], (*vertexes)[1], meshEdges));

    (*edges)[2]->setNext((*edges)[0]);
    (*edges)[2]->setPrevious((*edges)[1]);
    (*edges)[2]->setOpposite(generateEdge((*vertexes)[0], (*vertexes)[2], meshEdges));
}

HalfEdge *Face::generateEdge(Vertex *origin, Vertex *target, unordered_map<Vertex*, unordered_map<Vertex*, HalfEdge*>*>& meshEdges) {
    if (meshEdges.find(origin) == meshEdges.end()) {
        auto subMap = new unordered_map<Vertex*, HalfEdge*>();
        meshEdges.insert(make_pair(origin, subMap));
    }
    auto originMap = meshEdges.find(origin)->second;

    HalfEdge* halfEdge;
    auto iter = originMap->find(target);
    if (iter == originMap->end()) {
        halfEdge = new HalfEdge(origin, target, this);
        originMap->insert(make_pair(target, halfEdge));
    } else {
        halfEdge = iter->second;
    }
    return halfEdge;
}

vector<float>& Face::getNormalVector() {
    if (normalVector != nullptr) return (*normalVector);
    this->normalVector = new vector<float>(3);
    float x1 = (*vertexes)[1]->x - (*vertexes)[0]->x;
    float y1 = (*vertexes)[1]->y - (*vertexes)[0]->y;
    float z1 = (*vertexes)[1]->z - (*vertexes)[0]->z;
    float x2 = (*vertexes)[2]->x - (*vertexes)[0]->x;
    float y2 = (*vertexes)[2]->y - (*vertexes)[0]->y;
    float z2 = (*vertexes)[2]->z - (*vertexes)[0]->z;
    (*normalVector)[0] = y1*z2 - z1*y2;
    (*normalVector)[1] = z1*x2 - x1*z2;
    (*normalVector)[2] = x1*y2 - y1*x2;
    return (*normalVector);
}