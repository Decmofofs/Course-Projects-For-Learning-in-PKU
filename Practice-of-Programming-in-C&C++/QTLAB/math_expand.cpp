#include "math_expand.h"

Vector2::Vector2(double x, double y): x(x), y(y) {  }
Vector2::Vector2(const Vector2& V): x(V.x), y(V.y) {  }

double Vector2::area() {
    return x * y;
}

Vector2::operator bool() const {
    return x || y;
}

Vector2& Vector2::operator += (const Vector2& v){
    x += v.x;
    y += v.y;
    return *this;
}
Vector2& Vector2::operator -= (const Vector2& v){
    x -= v.x;
    y -= v.y;
    return *this;
}
Vector2& Vector2::operator *= (const double& k){
    x *= k;
    y *= k;
    return *this;
}
Vector2& Vector2::operator /= (const double& k){
    if (k == 0) return *this;
    x /= k;
    y /= k;
    return *this;
}
Vector2& Vector2::operator = (const Vector2& v){
    x = v.x;
    y = v.y;
    return *this;
}

Vector2 Vector2::operator + (const Vector2& v){
    return Vector2(x + v.x, y + v.y);
}
Vector2 Vector2::operator - (const Vector2& v){
    return Vector2(x - v.x, y - v.y);
}
Vector2 Vector2::operator * (const double& k){
    return Vector2(x * k, y * k);
}
Vector2 Vector2::operator / (const double& k){
    if (k == 0) return *this;
    return Vector2(x / k, y / k);
}
