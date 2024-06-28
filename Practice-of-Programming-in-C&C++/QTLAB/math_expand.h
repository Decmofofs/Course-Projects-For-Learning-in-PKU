#ifndef MATH_EXPAND_H
#define MATH_EXPAND_H

class Vector2{
public:
    double x;
    double y;

    Vector2(double x = 0, double y = 0);
    Vector2(const Vector2& V);

    double area();

    operator bool () const;

    Vector2& operator += (const Vector2& v);
    Vector2& operator -= (const Vector2& v);
    Vector2& operator *= (const double& k);
    Vector2& operator /= (const double& k);
    Vector2& operator = (const Vector2& v);

    Vector2 operator + (const Vector2& v);
    Vector2 operator - (const Vector2& v);
    Vector2 operator * (const double& k);
    Vector2 operator / (const double& k);

};


#endif // MATH_EXPAND_H
