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

    static vector<float> getUnit(float x, float y, float z);
    vector<float> globalLight(vector<float>& start, vector<float>& direction, float weight, vector<float>& light);
    static vector<float> getReflectionDirection(vector<float>& normal, vector<float>& direction);

    vector<float> localLight(pair<vector<float>, Face*>& point, vector<float>& light);
    static vector<float> mirror(float NL, vector<float> &normal, vector<float>& light);
};


#endif //INC_3DS_PRINTER_LIGHTTRACER_H
