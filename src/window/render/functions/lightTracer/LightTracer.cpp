#include "LightTracer.h"

void fillColor(BYTE* buffer, int index, vector<float>& rgb) {
    buffer[index + 2] = (unsigned char)max(0, min(255, (int)rgb[0]));
    buffer[index + 1] = (unsigned char)max(0, min(255, (int)rgb[1]));
    buffer[index] = (unsigned char)max(0, min(255, (int)rgb[2]));
}

void LightTracer::trace(RECT *rect, LT_Data *data, BYTE *buffer, vector<float> *light) {
    this->data = data;
    Vector3D eye = EYE_POINT;
    float offsetY = rect->right/2;
    float offsetZ = rect->bottom/2;
    Vector3D lightDir(*light);
    for (int i = 0, index = 0; i < rect->bottom; ++i) {
        for (int j = 0; j < rect->right; ++j, index += 3) {
            auto direction = getUnit(-eye.getX(), j - offsetY - eye.getY(), i - offsetZ - eye.getZ());
            auto color = globalLight(eye, direction, 1, lightDir);
            fillColor(buffer, index, color);
        }
    }
}

void LightTracer::trace(RECT *rect, LT_Data *data, HDC &hdc, vector<float> *light) {
    this->data = data;
    Vector3D eye = EYE_POINT;
    float offsetY = rect->right/2;
    float offsetZ = rect->bottom/2;
    Vector3D lightDir(*light);
    for (int i = 0, index = 0; i < rect->bottom; ++i) {
        for (int j = 0; j < rect->right; ++j, index += 3) {
            auto direction = getUnit(-eye.getX(), j - offsetY - eye.getY(), i - offsetZ - eye.getZ());
            auto color = globalLight(eye, direction, 1, lightDir);
            SetPixel(hdc, j, rect->bottom-i, RGB((unsigned char)max(0, min(255, (int)color[0])), (unsigned char)max(0, min(255, (int)color[1])), (unsigned char)max(0, min(255, (int)color[2]))));
        }
    }
}

Vector3D LightTracer::getUnit(float x, float y, float z) {
    float length = sqrt(x*x + y*y + z*z);
    return {x/length, y/length, z/length};
}

vector<float> LightTracer::globalLight(Vector3D& start, Vector3D& direction, float weight, Vector3D& light) {
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

Vector3D LightTracer::getReflectionDirection(Vector3D& normal, Vector3D& direction) {
    float ND = normal * direction;
    return direction - normal * (2 * ND);
}

vector<float> LightTracer::localLight(pair<Vector3D, Face*>& point, Vector3D& light) {
    auto direction = -light;
    auto crossPoint = data->getFirstCross(point.first, direction);
    //若有交点
    auto normal = point.second->getNormalVector();
    float NL = normal * direction;
    auto Id = vector<float>({NL * Ipr, NL * Ipg, NL * Ipb});
    if (crossPoint.second.second != nullptr || NL < 0)
        return {Id[0] * BKdr + Iar, Id[1] * BKdg + Iag, Id[2] * BKdb + Iab};

    auto Is = mirror(NL, normal, light);
    return {Id[0] * Kdr + Is[0] + Iar, Id[1] * Kdg + Is[1] + Iag, Id[2] * Kdb + Is[2] + Iab};
}

vector<float> LightTracer::mirror(float NL, Vector3D& normal, Vector3D& light) {
    auto R = normal * (2 * NL) - light;
    R.toUnit();
    float RVN = pow(-R.getX(), NS);
    return {Ipr * Ks * RVN, Ipg * Ks * RVN, Ipb * Ks * RVN};
}
