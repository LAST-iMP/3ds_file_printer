//
// Created by lenovo on 2020/8/9.
//

#ifndef INC_3DS_PRINTER_VECTOR3D_H
#define INC_3DS_PRINTER_VECTOR3D_H

#include <vector>
#include <cmath>

class Vector3D {
public:
    Vector3D(): x(0), y(0), z(0), init(false) {}
    Vector3D(const Vector3D &vector3D): x(vector3D.x), y(vector3D.y), z(vector3D.z), init(true){}
    Vector3D(std::vector<float> v): x(v[0]), y(v[1]), z(v[2]), init(true){}
    Vector3D(float x, float y, float z): x(x), y(y), z(z), init(true){}
    virtual ~Vector3D() {}

    Vector3D operator+(const Vector3D& vector3D);
    Vector3D operator-();
    Vector3D operator-(const Vector3D& vector3D);
    Vector3D operator*(const int value);
    Vector3D operator*(const float value);
    Vector3D operator/(const float value);
    float operator*(const Vector3D& vector3D);
    void operator+=(const Vector3D& vector3D);
    void operator-=(const Vector3D& vector3D);
    void operator*=(const float value);
    void operator/=(const float value);

    Vector3D cross(const Vector3D& vector3D);
    float getX() {return x;}
    float getY() {return y;}
    float getZ() {return z;}
    void set(const float& x, const float& y, const float& z);
    bool isSet() {return init;}
    void toUnit();
private:
    float x;
    float y;
    float z;
    bool init;
};


#endif //INC_3DS_PRINTER_VECTOR3D_H
