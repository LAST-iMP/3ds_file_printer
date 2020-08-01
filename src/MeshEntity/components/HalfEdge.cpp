#include "HalfEdge.h"

HalfEdge::HalfEdge(Vertex * source, Vertex * target, Face * master) {
    this->source = source;
    this->target = target;
    this->face = master;
}

HalfEdge::~HalfEdge() {

}

float HalfEdge::getSlope() {
    Vertex* from = (source->y <= target->y)? source : target;
    Vertex* to = (source->y <= target->y)? target : source;
    return (to->z - from->z) / (to->y - from->y);
}
