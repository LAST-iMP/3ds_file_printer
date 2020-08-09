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
    normal = Vector3D(*vL->getAveNormal());
    targetNormal->toUnit();
    normal.toUnit();
    dN = (*targetNormal - normal)/dz;
}

void Edge_Node::next() {
    y += dy;
    x += dx;
    normal += dN;
}
