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
#include "../../../../common/Vector3D.h"

using namespace std;

class LightFilter {
public:
    void fillColor(BYTE* buffer, int index, int r, int g, int b);
    vector<float> localLight(Vector3D& normal, Vector3D& light);

private:
    vector<float> mirror(float NL, Vector3D& normal, Vector3D& light);
};


#endif //INC_3DS_PRINTER_LIGHTFILTER_H
