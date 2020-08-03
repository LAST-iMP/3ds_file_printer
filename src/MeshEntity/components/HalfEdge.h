#ifndef INC_3DS_PRINTER_HALFEDGE_H
#define INC_3DS_PRINTER_HALFEDGE_H

#include "Vertex.h"

class Face;

class HalfEdge {
private:
    Vertex* source;
    Vertex* target;
    HalfEdge* next;
    HalfEdge* previous;
    HalfEdge* opposite;
    Face* face;

public:
    HalfEdge(Vertex* source, Vertex* target, Face* master);
    virtual ~HalfEdge();

    void setNext(HalfEdge* _next) { this->next = _next;}
    void setPrevious(HalfEdge* _previous) { this->previous = _previous;}
    void setOpposite(HalfEdge* _opposite) { this->opposite = _opposite;}

    Vertex* getOrigin() {return source;}
    Vertex* getTarget() {return target;}
    HalfEdge* getNext() {return next;}
    HalfEdge* getPrevious() {return previous;}
    HalfEdge* getOpposite() {return opposite;}
    Face* getFace() {return face;}
    float getSlope(bool fromSource);
};


#endif //INC_3DS_PRINTER_HALFEDGE_H
