#ifndef INC_3DS_PRINTER_VERTEX_H
#define INC_3DS_PRINTER_VERTEX_H

#include <vector>
#include "windows.h"
#include "../../common/Vector3D.h"

using namespace std;

class Vertex {
public:
    Vertex(vector<float>& v);
    virtual ~Vertex();

    float getX() const {return x;}
    float getY() const {return y;}
    float getZ() const {return z;}
    Vector3D* getAveNormal() {return &aveNormal;}
    void expandAveNormal(Vector3D& n);

    static vector<int> translate(int x, int y, RECT & rect);

private:
    float x;
    float y;
    float z;

    Vector3D aveNormal;
    int faceCount = 0;
};


#endif //INC_3DS_PRINTER_VERTEX_H
