#ifndef INC_3DS_PRINTER_VERTEX_H
#define INC_3DS_PRINTER_VERTEX_H

#include <vector>
#include "windows.h"

using namespace std;

class Vertex {
public:
    Vertex(vector<float>& v);
    virtual ~Vertex();

    vector<int> getLocation();

    float getX() const {return x;}
    float getY() const {return y;}
    float getZ() const {return z;}
    vector<float>* getAveNormal() {return aveNormal;}
    void expandAveNormal(vector<float>* n);

    static vector<int> translate(int x, int y, RECT & rect);

private:
    float x;
    float y;
    float z;

    vector<float>* aveNormal = nullptr;
    int faceCount = 0;
};


#endif //INC_3DS_PRINTER_VERTEX_H
