//
// Created by lenovo on 2020/8/4.
//

#include "Edge_Node.h"

Edge_Node::Edge_Node(HalfEdge *e) {
    edge = e;
    Vertex* vL = (e->getTarget()->getZ() < e->getOrigin()->getZ())? e->getTarget() : e->getOrigin();
    Vertex* vH = (e->getTarget()->getZ() < e->getOrigin()->getZ())? e->getOrigin() : e->getTarget();
    x = vL->getX();
    y = vL->getY();
    int dz = ((int)vH->getZ() - (int)vL->getZ());
    dx = (vH->getX() - vL->getX()) / dz;
    dy = (vH->getY() - vL->getY()) / dz;
    zMin = vL->getZ();
    zMax = vH->getZ();

    auto targetNormal = vH->getAveNormal();
    normal = vector<float>(*vL->getAveNormal());
    dN = vector<float>(3);
    dN[0] = ((*targetNormal)[0] - normal[0]) / dz;
    dN[1] = ((*targetNormal)[1] - normal[1]) / dz;
    dN[2] = ((*targetNormal)[2] - normal[2]) / dz;
}

void Edge_Node::next() {
    y += dy;
    x += dx;
    normal[0] += dN[0];
    normal[1] += dN[1];
    normal[2] += dN[2];
}
