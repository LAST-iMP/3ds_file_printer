#include "HalfEdge.h"

HalfEdge::HalfEdge(Vertex * source, Vertex * target, Face * master) {
    this->source = source;
    this->target = target;
    this->face = master;
}

HalfEdge::~HalfEdge() {

}

float HalfEdge::getSlope(bool fromSource) {
    if (fromSource) return (target->z - source->z) / (target->y - source->y);
    else return (source->z - target->z) / (source->y - target->y);
}
