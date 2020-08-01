#include "Vertex.h"

Vertex::Vertex(vector<float>& v) {
    x = v[0];
    y = v[1];
    z = v[2];
}

vector<int> Vertex::translate(int x, int y, RECT &rect) {
    vector<int> result(2);
    result[0] = x + rect.right/2;
    result[1] = y + rect.bottom/2;
    return result;
}
