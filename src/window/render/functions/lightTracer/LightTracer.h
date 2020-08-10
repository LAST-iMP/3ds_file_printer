//
// Created by lenovo on 2020/8/7.
//

#ifndef INC_3DS_PRINTER_LIGHTTRACER_H
#define INC_3DS_PRINTER_LIGHTTRACER_H

#include <vector>
#include <cmath>
#include <windows.h>
#include "../../Render_Param.h"
#include "LT_Data.h"

using namespace std;

class LightTracer {
public:
    void trace(RECT *rect, LT_Data *data, BYTE *buffer, vector<float> * light);
    void trace(RECT *rect, LT_Data *data, HDC& hdc, vector<float> * light);

private:
    LT_Data *data;

    static Vector3D getUnit(float x, float y, float z);
    vector<float> globalLight(Vector3D& start, Vector3D& direction, float weight, Vector3D& light);
    static Vector3D getReflectionDirection(Vector3D& normal, Vector3D& direction);

    vector<float> localLight(pair<pair<float, Vector3D>, pair<Vector3D, Face *>>& point, Vector3D& light);
    static vector<float> mirror(float NL, Vector3D& normal, Vector3D& light);
};


#endif //INC_3DS_PRINTER_LIGHTTRACER_H
