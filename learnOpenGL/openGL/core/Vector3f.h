#pragma once

#include <tuple>
#include <vector>

namespace openGL::core
{
  using Vector3fTuple = std::tuple<float, float, float>;

  class Vector3F
  {
  public:
    Vector3F(float x, float y, float z);

    Vector3fTuple values();
    float first() const;
    void first(float x);
    float second() const;
    void second(float y);
    float third() const;
    void third(float z);

    void set(float x, float y, float z);
    void set(const Vector3fTuple& values);
    void set(const Vector3F& other);

    bool operator==(const Vector3F& other) const;
    bool operator!=(const Vector3F& other) const;

    Vector3F operator+(const Vector3F& other) const;
    Vector3F operator-(const Vector3F& other) const;
    Vector3F operator*(float scalar) const;
    Vector3F operator/(float scalar) const;

    Vector3F& operator+=(const Vector3F& other);
    Vector3F& operator-=(const Vector3F& other);
    Vector3F& operator*=(float scalar);
    Vector3F& operator/=(float scalar);

    float length() const;
    Vector3F normalized() const;
    Vector3F cross(const Vector3F& other) const;
    float dot(const Vector3F& other) const;
    float distance(const Vector3F& other) const;
    float distance_squared(const Vector3F& other) const;

    Vector3fTuple to_tuple() const;

    static Vector3F from_tuple(const Vector3fTuple& values);
    static Vector3F zero();
    static Vector3F one();
    static Vector3F up();
    static Vector3F down();
    static Vector3F left();
    static Vector3F right();
    static Vector3F forward();
    static Vector3F backward();
    static Vector3F from_array(const float* arr);

    void to_array(float* arr) const;

  protected:
    Vector3fTuple values_;
  };
}
