#ifndef VEC3_H
#define VEC3_H

class Vec3 {
public:
    float x, y, z;

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    float dot(const Vec3& other) const;

    Vec3 cross(const Vec3& other) const;

    float magnitude() const;

    float sinBetween(const Vec3& other) const;

    float angleBetween(const Vec3& other) const;

    void print() const;

    const float& operator[](int index) const;

    bool operator==(const Vec3& other) const;
};

#endif  // VEC3_H

