#include "LightFilter.h"

void LightFilter::fillColor(BYTE* buffer, int index, int r, int g, int b) {
    buffer[index + 2] =  (unsigned char)max(0, min(255, r));
    buffer[index + 1] = (unsigned char)max(0, min(255, g));
    buffer[index] = (unsigned char)max(0, min(255, b));
}

vector<float> LightFilter::localLight(vector<float>& normal, vector<float>& light) {
    float NL = getMatrixMulti(-light[0], -light[1], -light[2], normal[0], normal[1], normal[2]);
    auto Id = vector<float>({NL * Kdr * Ipr, NL * Kdg * Ipg, NL * Kdb * Ipb});
    auto Is = mirror(NL, normal, light);
    return {Id[0] + Is[0] + Iar, Id[1] + Is[1] + Iag, Id[2] + Is[2] + Iab};
}

vector<float> LightFilter::mirror(float NL, vector<float> &normal, vector<float>& light) {
    float Rx = 2 * normal[0] * NL - light[0];
    float Ry = 2 * normal[1] * NL - light[1];
    float Rz = 2 * normal[2] * NL - light[2];
    float RLength = sqrt(Rx*Rx + Ry*Ry + Rz*Rz);
    float RVN = pow(-Rx / RLength, NS);
    return {Ipr * Ks * RVN, Ipg * Ks * RVN, Ipb * Ks * RVN};
}

float LightFilter::getMatrixMulti(float x1, float y1, float z1, float x2, float y2, float z2) {
    return x1*x2 + y1*y2 + z1*z2;
}
