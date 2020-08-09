#include "LightFilter.h"

void LightFilter::fillColor(BYTE* buffer, int index, int r, int g, int b) {
    buffer[index + 2] =  (unsigned char)max(0, min(255, r));
    buffer[index + 1] = (unsigned char)max(0, min(255, g));
    buffer[index] = (unsigned char)max(0, min(255, b));
}

vector<float> LightFilter::localLight(Vector3D& normal, Vector3D& light) {
    float NL = -light*normal;
    auto Id = vector<float>({NL * Ipr, NL * Ipg, NL * Ipb});
    auto Is = mirror(NL, normal, light);
    return {Id[0] * Kdr + Is[0] + Iar, Id[1] * Kdg + Is[1] + Iag, Id[2] * Kdb + Is[2] + Iab};
}

vector<float> LightFilter::mirror(float NL, Vector3D& normal, Vector3D& light) {
    auto R = normal * (2 * NL) - light;
    R.toUnit();
    float RVN = pow(-R.getX(), NS);
    return {Ipr * Ks * RVN, Ipg * Ks * RVN, Ipb * Ks * RVN};
}
