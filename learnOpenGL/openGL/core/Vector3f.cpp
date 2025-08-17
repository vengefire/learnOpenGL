#include "Vector3f.h"
#include <array>
#include <cmath>
#include <stdexcept>

namespace openGL::core
{
  Vector3F::Vector3F(float x, float y, float z) : values_(x, y, z)
  {
  }

  Vector3fTuple Vector3F::values() { return values_; }
  float Vector3F::first() const { return std::get<0>(values_); }
  void Vector3F::first(float x) { std::get<0>(values_) = x; }
  float Vector3F::second() const { return std::get<1>(values_); }
  void Vector3F::second(float y) { std::get<1>(values_) = y; }
  float Vector3F::third() const { return std::get<2>(values_); }
  void Vector3F::third(float z) { std::get<2>(values_) = z; }

  void Vector3F::set(float x, float y, float z)
  {
    first(x);
    second(y);
    third(z);
  }

  void Vector3F::set(const Vector3fTuple& values)
  {
    first(std::get<0>(values));
    second(std::get<1>(values));
    third(std::get<2>(values));
  }

  void Vector3F::set(const Vector3F& other)
  {
    first(other.first());
    second(other.second());
    third(other.third());
  }

  bool Vector3F::operator==(const Vector3F& other) const
  {
    return first() == other.first() && second() == other.second() && third() == other.third();
  }

  bool Vector3F::operator!=(const Vector3F& other) const
  {
    return !(*this == other);
  }

  Vector3F Vector3F::operator+(const Vector3F& other) const
  {
    return Vector3F(first() + other.first(), second() + other.second(), third() + other.third());
  }

  Vector3F Vector3F::operator-(const Vector3F& other) const
  {
    return Vector3F(first() - other.first(), second() - other.second(), third() - other.third());
  }

  Vector3F Vector3F::operator*(float scalar) const
  {
    return Vector3F(first() * scalar, second() * scalar, third() * scalar);
  }

  Vector3F Vector3F::operator/(float scalar) const
  {
    if (scalar == 0.0f) throw std::runtime_error("Division by zero in Vector3F division.");
    return Vector3F(first() / scalar, second() / scalar, third() / scalar);
  }

  Vector3F& Vector3F::operator+=(const Vector3F& other)
  {
    first(first() + other.first());
    second(second() + other.second());
    third(third() + other.third());
    return *this;
  }

  Vector3F& Vector3F::operator-=(const Vector3F& other)
  {
    first(first() - other.first());
    second(second() - other.second());
    third(third() - other.third());
    return *this;
  }

  Vector3F& Vector3F::operator*=(float scalar)
  {
    first(first() * scalar);
    second(second() * scalar);
    third(third() * scalar);
    return *this;
  }

  Vector3F& Vector3F::operator/=(float scalar)
  {
    if (scalar == 0.0f) throw std::runtime_error("Division by zero in Vector3F division.");
    first(first() / scalar);
    second(second() / scalar);
    third(third() / scalar);
    return *this;
  }

  float Vector3F::length() const
  {
    return std::sqrt(first() * first() + second() * second() + third() * third());
  }

  Vector3F Vector3F::normalized() const
  {
    float len = length();
    if (len == 0.0f) throw std::runtime_error("Cannot normalize a zero-length vector.");
    return Vector3F(first() / len, second() / len, third() / len);
  }

  Vector3F Vector3F::cross(const Vector3F& other) const
  {
    return Vector3F(
      second() * other.third() - third() * other.second(),
      third() * other.first() - first() * other.third(),
      first() * other.second() - second() * other.first()
    );
  }

  float Vector3F::dot(const Vector3F& other) const
  {
    return first() * other.first() + second() * other.second() + third() * other.third();
  }

  float Vector3F::distance(const Vector3F& other) const
  {
    return std::sqrt(
      (first() - other.first()) * (first() - other.first()) +
      (second() - other.second()) * (second() - other.second()) +
      (third() - other.third()) * (third() - other.third())
    );
  }

  float Vector3F::distance_squared(const Vector3F& other) const
  {
    return (first() - other.first()) * (first() - other.first()) +
      (second() - other.second()) * (second() - other.second()) +
      (third() - other.third()) * (third() - other.third());
  }

  Vector3fTuple Vector3F::to_tuple() const
  {
    return std::make_tuple(first(), second(), third());
  }

  Vector3F Vector3F::from_tuple(const Vector3fTuple& values)
  {
    return Vector3F(std::get<0>(values), std::get<1>(values), std::get<2>(values));
  }

  Vector3F Vector3F::zero()
  {
    return Vector3F(0.0f, 0.0f, 0.0f);
  }

  Vector3F Vector3F::one()
  {
    return Vector3F(1.0f, 1.0f, 1.0f);
  }

  Vector3F Vector3F::up()
  {
    return Vector3F(0.0f, 1.0f, 0.0f);
  }

  Vector3F Vector3F::down()
  {
    return Vector3F(0.0f, -1.0f, 0.0f);
  }

  Vector3F Vector3F::left()
  {
    return Vector3F(-1.0f, 0.0f, 0.0f);
  }

  Vector3F Vector3F::right()
  {
    return Vector3F(1.0f, 0.0f, 0.0f);
  }

  Vector3F Vector3F::forward()
  {
    return Vector3F(0.0f, 0.0f, -1.0f);
  }

  Vector3F Vector3F::backward()
  {
    return Vector3F(0.0f, 0.0f, 1.0f);
  }

  Vector3F Vector3F::from_array(const float* arr)
  {
    if (arr == nullptr) throw std::runtime_error("Array pointer is null.");
    return Vector3F(arr[0], arr[1], arr[2]);
  }

  void Vector3F::to_array(float* arr) const
  {
    if (arr == nullptr) throw std::runtime_error("Array pointer is null.");
    arr[0] = first();
    arr[1] = second();
    arr[2] = third();
  }
}
