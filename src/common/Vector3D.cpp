//
// Created by lenovo on 2020/8/9.
//

#include "Vector3D.h"

Vector3D Vector3D::operator+(const Vector3D &vector3D) {
    return Vector3D(
            this->x + vector3D.x,
            this->y + vector3D.y,
            this->z + vector3D.z);
}

Vector3D Vector3D::operator-() {
    return Vector3D(
            -this->x,
            -this->y,
            -this->z);
}

Vector3D Vector3D::operator-(const Vector3D &vector3D) {
    return Vector3D(
            this->x - vector3D.x,
            this->y - vector3D.y,
            this->z - vector3D.z);
}

Vector3D Vector3D::operator*(const int value) {
    return Vector3D(
            this->x * value,
            this->y * value,
            this->z * value);
}

Vector3D Vector3D::operator*(const float value) {
    return Vector3D(
            this->x * value,
            this->y * value,
            this->z * value);
}

float Vector3D::operator*(const Vector3D &vector3D) {
    return this->x * vector3D.x + this->y * vector3D.y + this->z * vector3D.z;
}

Vector3D Vector3D::operator/(const float value) {
    return Vector3D(this->x / value, this->y / value, this->z / value);
}

void Vector3D::operator+=(const Vector3D &vector3D) {
    this->x += vector3D.x;
    this->y += vector3D.y;
    this->z += vector3D.z;
}

void Vector3D::operator-=(const Vector3D &vector3D) {
    this->x -= vector3D.x;
    this->y -= vector3D.y;
    this->z -= vector3D.z;
}

void Vector3D::operator*=(const float value) {
    this->x *=value;
    this->y *=value;
    this->z *=value;
}

void Vector3D::operator/=(const float value) {
    this->x /=value;
    this->y /=value;
    this->z /=value;
}

Vector3D Vector3D::cross(const Vector3D &vector3D) {
    return Vector3D(
            this->y * vector3D.z - this->z * vector3D.y,
            this->z * vector3D.x - this->x * vector3D.z,
            this->x * vector3D.y - this->y * vector3D.x);
}

void Vector3D::set(const float& x, const float& y, const float& z) {
    this->x = x;
    this->y = y;
    this->z = z;
    this->init = true;
}

void Vector3D::toUnit() {
    float length = sqrt(x*x + y*y + z*z);
    this->x/=length;
    this->y/=length;
    this->z/=length;
}
