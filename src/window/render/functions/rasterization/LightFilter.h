//
// Created by lenovo on 2020/7/29.
//

#ifndef INC_3DS_PRINTER_LIGHTFILTER_H
#define INC_3DS_PRINTER_LIGHTFILTER_H

#include <vector>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <iostream>
#include "../../Render_Param.h"

using namespace std;

class LightFilter {
public:
    void fillColor(BYTE* buffer, int index, int r, int g, int b);
    vector<float> localLight(vector<float>& normal, vector<float>& light);

private:
    vector<float> mirror(float NL, vector<float> &normal, vector<float>& light);

    float getMatrixMulti(float, float, float, float, float, float);
};


#endif //INC_3DS_PRINTER_LIGHTFILTER_H
