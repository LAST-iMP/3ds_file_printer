//
// Created by lenovo on 2020/7/29.
//

#ifndef INC_3DS_PRINTER_RASTERIZE_H
#define INC_3DS_PRINTER_RASTERIZE_H

#include <ctime>
#include "iostream"
#include "windows.h"
#include "../Render_DATA.h"

#define DRAW_EDGE false;

using namespace std;

typedef struct ACT_EDGE {
    float y;
    float x;
    float dy;
    float dx;
    float z_max;
    ACT_EDGE(HalfEdge* e) {
        Vertex* vL = (e->getTarget()->z < e->getOrigin()->z)? e->getTarget() : e->getOrigin();
        Vertex* vH = (e->getTarget()->z < e->getOrigin()->z)? e->getOrigin() : e->getTarget();
        x = vL->x;
        y = vL->y;
        dx = (vH->x - vL->x) / ((int)vH->z - (int)vL->z);
        dy = (vH->y - vL->y) / ((int)vH->z - (int)vL->z);
        z_max = vH->z;
    }

    void next() {
        y += dy;
        x += dx;
    }
} ActiveEdge, *HActiveEdge;

class Rasterize {
public:
    static void rasterize(BYTE* buffer, RECT& rect, RENDER_DATA& data);

private:
    static void r_Face(BYTE* buffer, RECT rect, Face& f, vector<vector<int>>& distance, int xMin, int xMax);
};


#endif //INC_3DS_PRINTER_RASTERIZE_H
