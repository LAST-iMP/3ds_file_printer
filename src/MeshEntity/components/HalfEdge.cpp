#include "HalfEdge.h"

HalfEdge::HalfEdge(Vertex * source, Vertex * target, Face * master) {
    this->source = source;
    this->target = target;
    this->face = master;
}

HalfEdge::~HalfEdge() {

}

float HalfEdge::getSlope(bool fromSource) {
    if (fromSource) return (target->getZ() - source->getZ()) / (target->getY() - source->getY());
    else return (source->getZ() - target->getZ()) / (source->getY() - target->getY());
}
