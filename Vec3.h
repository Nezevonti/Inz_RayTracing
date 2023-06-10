#ifndef VEC3_H
#define VEC3_H

class Vec3 {
public:
    float x, y, z;

    Vec3(float x = 0.0f, float y = 0.0f, float z = 0.0f);

    float dot(const Vec3& other) const;

    Vec3 cross(const Vec3& other) const;

    void print() const;

    float& operator[](int index);

    bool operator==(const Vec3& other) const;
};

#endif  // VEC3_H
