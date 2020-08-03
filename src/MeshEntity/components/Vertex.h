#ifndef INC_3DS_PRINTER_VERTEX_H
#define INC_3DS_PRINTER_VERTEX_H

#include <vector>
#include "windows.h"

using namespace std;

class Vertex {
public:
    float x;
    float y;
    float z;


    Vertex(vector<float>& v);
    virtual ~Vertex();

    vector<int> getLocation() {
        vector<int> v = {static_cast<int>(x), static_cast<int>(y), static_cast<int>(z)};
        return v;
    }

    float getTranY(RECT & rect) const {return translate(y, z, rect)[0];}
    float getTranZ(RECT & rect) const {return translate(y, z, rect)[1];}

    int getIntX() const {return x;}
    int getIntY() const {return y;}
    int getIntZ() {return z;}

    static vector<int> translate(int x, int y, RECT & rect);
    vector<float>* getAveNormal() {return aveNormal;}
    void expandAveNormal(vector<float>* n);

private:
    vector<float>* aveNormal = nullptr;
    int faceCount = 0;
};


#endif //INC_3DS_PRINTER_VERTEX_H
