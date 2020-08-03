#include "Vertex.h"

Vertex::Vertex(vector<float>& v) {
    x = v[0];
    y = v[1];
    z = v[2];
}

Vertex::~Vertex() {
    delete aveNormal;
}

vector<int> Vertex::translate(int x, int y, RECT &rect) {
    vector<int> result(2);
    result[0] = x + rect.right/2;
    result[1] = y + rect.bottom/2;
    return result;
}

void Vertex::expandAveNormal(vector<float> *n) {
    if (aveNormal == nullptr)
        aveNormal = new vector<float>(*n);
    (*aveNormal)[0] = ((*aveNormal)[0] * faceCount + (*n)[0]) / (faceCount+1);
    (*aveNormal)[1] = ((*aveNormal)[1] * faceCount + (*n)[1]) / (faceCount+1);
    (*aveNormal)[2] = ((*aveNormal)[2] * faceCount + (*n)[2]) / (faceCount+1);
    faceCount++;
}

vector<int> Vertex::getLocation() {
    vector<int> v = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(z)};
    return v;
}
