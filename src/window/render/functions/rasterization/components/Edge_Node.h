//
// Created by lenovo on 2020/8/4.
//

#ifndef INC_3DS_PRINTER_EDGE_NODE_H
#define INC_3DS_PRINTER_EDGE_NODE_H

#include <vector>
#include "../Rasterization_DATA.h"

using namespace std;

class Edge_Node {
public:
    float x;
    float dx;
    float y;
    float dy;
    int zMin;
    int zMax;
    vector<float> normal;
    vector<float> dN;
    HalfEdge* edge;

    explicit Edge_Node(HalfEdge* e);
    void next();

    bool operator< (Edge_Node& e) {
        return this->y + dy > e.y + e.dy;
    }
};


#endif //INC_3DS_PRINTER_EDGE_NODE_H
