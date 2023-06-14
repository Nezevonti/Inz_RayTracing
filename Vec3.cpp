#include "vec3.h"
#include <iostream>
#include <cmath>

Vec3::Vec3(float x, float y, float z)
    : x(x), y(y), z(z) {}

float Vec3::dot(const Vec3& other) const {
    return x * other.x + y * other.y + z * other.z;
}

Vec3 Vec3::cross(const Vec3& other) const {
    float cross_x = y * other.z - z * other.y;
    float cross_y = z * other.x - x * other.z;
    float cross_z = x * other.y - y * other.x;
    return Vec3(cross_x, cross_y, cross_z);
}

float Vec3::magnitude() const {
    return std::sqrt(x * x + y * y + z * z);
}

bool Vec3::operator==(const Vec3& other) const {
    return x == other.x && y == other.y && z == other.z;
}

void Vec3::print() const {
    std::cout << "(" << x << ", " << y << ", " << z << ")" << std::endl;
}

const float& Vec3::operator[](int index) const{
    if (index == 0) return x;
    if (index == 1) return y;
    if (index == 2) return z;
    throw std::out_of_range("Vec3 index out of range");
}

Vec3 Vec3::operator+(const Vec3& other) const{
    return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3& other) const{
    return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(float scalar) const {
    return Vec3(x * scalar, y * scalar, z * scalar);
}

float Vec3::angleBetween(const Vec3& other) const {
    float dotProduct = dot(other);
    float magnitudesProduct = magnitude() * other.magnitude();

    // Avoid division by zero
    if (magnitudesProduct == 0.0f) {
        return 0.0f;
    }

    return std::acos(dotProduct / magnitudesProduct);
}

float Vec3::sinBetween(const Vec3& other) const {
    Vec3 crossProduct = cross(other);
    float magnitudeCrossProduct = crossProduct.magnitude();
    float magnitudesProduct = magnitude() * other.magnitude();

    // Avoid division by zero
    if (magnitudesProduct == 0.0f) {
        return 0.0f;
    }

    return magnitudeCrossProduct / magnitudesProduct;
}

Vec3 Vec3::normalize() const {
    float magnitude = this->magnitude();
    if (magnitude != 0.0f)
        return Vec3(x / magnitude, y / magnitude, z / magnitude);
    else
        return Vec3();
}

Vec3 Vec3::mapToUnitRange()
{
    // Map the x, y, and z components individually
    float mappedX = (x + 1.0f) * 0.5f;
    float mappedY = (y + 1.0f) * 0.5f;
    float mappedZ = (z + 1.0f) * 0.5f;

    return Vec3(mappedX, mappedY, mappedZ);
}