#include "LightTracer.h"

float getMatrixMulti(float x1, float y1, float z1, float x2, float y2, float z2) {
    return x1*x2 + y1*y2 + z1*z2;
}

void fillColor(BYTE* buffer, int index, vector<float>& rgb) {
    buffer[index + 2] = (unsigned char)max(0, min(255, (int)rgb[0]));
    buffer[index + 1] = (unsigned char)max(0, min(255, (int)rgb[1]));
    buffer[index] = (unsigned char)max(0, min(255, (int)rgb[2]));
}

void LightTracer::trace(RECT *rect, LT_Data *data, BYTE *buffer, vector<float> *light) {
    this->data = data;
    vector<float> eye = EYE_POINT;
    float offsetY = rect->right/2;
    float offsetZ = rect->bottom/2;
    for (int i = 0, index = 0; i < rect->bottom; ++i) {
        for (int j = 0; j < rect->right; ++j, index += 3) {
            auto direction = getUnit(-eye[0], j - offsetY - eye[1], i - offsetZ - eye[2]);
            auto color = globalLight(eye, direction, 1, *light);
            fillColor(buffer, index, color);
        }
    }
}

void LightTracer::trace(RECT *rect, LT_Data *data, HDC &hdc, vector<float> *light) {
    this->data = data;
    vector<float> eye = EYE_POINT;
    float offsetY = rect->right/2;
    float offsetZ = rect->bottom/2;
    for (int i = 0, index = 0; i < rect->bottom; ++i) {
        for (int j = 0; j < rect->right; ++j, index += 3) {
            if (i == offsetZ && j==offsetY){
                int a = 1+1;
            }
            auto direction = getUnit(-eye[0], j - offsetY - eye[1], i - offsetZ - eye[2]);
            auto color = globalLight(eye, direction, 1, *light);
            SetPixel(hdc, j, rect->bottom-i, RGB((unsigned char)max(0, min(255, (int)color[0])), (unsigned char)max(0, min(255, (int)color[1])), (unsigned char)max(0, min(255, (int)color[2]))));
        }
    }
}

vector<float> LightTracer::getUnit(float x, float y, float z) {
    float length = sqrt(x*x + y*y + z*z);
    return {x/length, y/length, z/length};
}

vector<float> LightTracer::globalLight(vector<float>& start, vector<float>& direction, float weight, vector<float>& light) {
    if (weight < MinWeight) return vector<float>({0, 0, 0});
    auto crossPoint = data->getFirstCross(start, direction);
    //若没有交点
    if (crossPoint.second.second == nullptr) return vector<float>({0, 0, 0});
    //计算局部光照
    auto local = localLight(crossPoint.second, light);
    //计算反射方向
    auto newDirection = getReflectionDirection(crossPoint.second.second->getNormalVector(), direction);
    //计算反射光强
    auto refLight = globalLight(crossPoint.second.first, newDirection, weight * RefWeight, light);
    return {local[0] + refLight[0] * Ks, local[1] + refLight[1] * Ks, local[2] + refLight[2] * Ks};
}

vector<float> LightTracer::getReflectionDirection(vector<float> &normal, vector<float> &direction) {
    float ND = getMatrixMulti(normal[0], normal[1], normal[2], direction[0], direction[1], direction[2]);
    return {direction[0] - 2 * ND * normal[0], direction[1] - 2 * ND * normal[1], direction[2] - 2 * ND * normal[2]};
}

vector<float> LightTracer::localLight(pair<vector<float>, Face*>& point, vector<float>& light) {
    vector<float> direction = {-light[0], -light[1], -light[2]};
    auto crossPoint = data->getFirstCross(point.first, direction);
    //若有交点
    auto normal = point.second->getNormalVector();
    float NL = getMatrixMulti(direction[0], direction[1], direction[2], normal[0], normal[1], normal[2]);
    auto Id = vector<float>({NL * Ipr, NL * Ipg, NL * Ipb});
    if (crossPoint.second.second != nullptr || NL < 0)
        return {Id[0] * BKdr + Iar, Id[1] * BKdg + Iag, Id[2] * BKdb + Iab};

    auto Is = mirror(NL, normal, light);
    return {Id[0] * Kdr + Is[0] + Iar, Id[1] * Kdg + Is[1] + Iag, Id[2] * Kdb + Is[2] + Iab};
}

vector<float> LightTracer::mirror(float NL, vector<float> &normal, vector<float>& light) {
    float Rx = 2 * normal[0] * NL - light[0];
    float Ry = 2 * normal[1] * NL - light[1];
    float Rz = 2 * normal[2] * NL - light[2];
    float RLength = sqrt(Rx*Rx + Ry*Ry + Rz*Rz);
    float RVN = pow(-Rx / RLength, NS);
    return {Ipr * Ks * RVN, Ipg * Ks * RVN, Ipb * Ks * RVN};
}
