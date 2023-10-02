#pragma once
#include <utility>
#include <vector>
#include <string>
#include <iostream>


namespace slib
{
struct vec2;
struct vec3;
struct vec4;
struct mat;



struct texture
{
    int w, h;
    std::vector<unsigned char> data;
    unsigned int bpp;
};

texture DecodePng(const char* filename);

struct zvec2
{
    float x, y, w;
};

struct vec2
{
    float x, y;
    vec2 &operator*=(const vec2& rhs);
    vec2 &operator*=(float rhs);
    vec2 operator-(const vec2& rhs) const;
};

struct vec3
{
    float x, y, z;
    vec3 &operator+=(float rhs);
    vec3 &operator-=(float rhs);
    vec3 &operator*=(float rhs);
    vec3 &operator/=(float rhs);
    vec3 operator-(float rhs) const;
    vec3 operator+(float rhs) const;
    vec3 operator*(float rhs) const;
    vec3 operator/(float rhs) const;
    vec3 &operator+=(const vec3 &rhs);
    vec3 &operator-=(const vec3 &rhs);
    vec3 &operator*=(const vec3 &rhs);
    vec3 &operator/=(const vec3 &rhs);
    vec3 operator-(const vec3 &rhs) const;
    vec3 operator+(const vec3 &rhs) const;
    vec3 operator*(const vec3 &rhs) const;
    vec3 operator/(const vec3 &rhs) const;
    vec3 operator*(const mat &rhs) const;
    vec3 &operator*=(const mat &rhs);
    bool operator==(const vec3 &rhs) const;
    bool operator==(float rhs) const;
    bool operator<(const vec3 &rhs) const;
    bool operator>(const vec3 &rhs) const;
    bool operator<=(const vec3 &rhs) const;
    bool operator>=(const vec3 &rhs) const;
};

struct vec4
{
    float x, y, z, w;
    vec4 operator*(const mat &rhs) const;
    vec4 operator*=(const mat &rhs);
};

struct mat
{
    std::vector<std::vector<float>> data;
    explicit mat(std::vector<std::vector<float>> _data)
        : data(std::move(_data))
    {};

    mat &operator+=(const mat &rhs);
    mat &operator*=(const mat &rhs);
    mat operator*(const mat &rhs) const;
    vec4 operator*(const vec4 &rhs) const;

};

/*
 * Contains the relevant index in the vertices or textureCoordinates vectors of the mesh
 */
struct tri
{
    const int v1, v2, v3;
    const int vt1, vt2, vt3;
    std::string textureName;
};

struct Color
{
    int r, g, b;
};
}
