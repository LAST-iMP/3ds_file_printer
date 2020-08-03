//
// Created by lenovo on 2020/7/29.
//

#ifndef INC_3DS_PRINTER_RASTERIZE_H
#define INC_3DS_PRINTER_RASTERIZE_H

#include <ctime>
#include "iostream"
#include "windows.h"
#include "../Render_DATA.h"
#include "../Render_Param.h"

using namespace std;

typedef struct ACT_EDGE {
    //坐标及坐标增量
    float y;
    float x;
    float dy;
    float dx;
    //最大z值
    float z_max;
    //法向量及法向量增量
    vector<float> normal;
    vector<float> dN;

    explicit ACT_EDGE(HalfEdge* e);
    void next();
} ActiveEdge, *HActiveEdge;

class Rasterize {
public:
    explicit Rasterize(RECT* rect, RENDER_DATA * data);
    virtual ~Rasterize();

    void rasterize(BYTE* buffer, vector<float>& light);

private:
    RECT* rect;
    RENDER_DATA * data;
    void r_Face(BYTE* buffer, Face& f, vector<vector<int>>& distance, float xMin, float xMax, vector<float>& light);
    vector<float> getLightColor(float dw, float x, float y, float z, vector<float>& normal);
    float getNL(float x, float y, float z, vector<float>& normal);
    float getMatrixMulti(float, float, float, float, float, float);
    vector<float> mirrorRate(float NL);
    vector<float> diffuse(float NL);
    vector<float> mirror(float NL, float x, float y, float z, vector<float>& normal);
};


#endif //INC_3DS_PRINTER_RASTERIZE_H
