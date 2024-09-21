#pragma once

template <typename T>
class Vector2D
{
public:
    Vector2D(T x, T y) :
        m_x(x),
        m_y(y)
    {
    }

    Vector2D() :
        m_x(T(0)),
        m_y(T(0))
    {
    }

    Vector2D(T value) :
        m_x(value),
        m_y(value)
    {
    }

public:
    const T& GetX() const
    {
        return m_x;
    }

    const T& GetY() const
    {
        return m_y;
    }

    void SetX(const T& value)
    {
        m_x = value;
    }

    void SetY(const T& value)
    {
        m_y = value;
    }

public:
    Vector2D<T> operator+(const Vector2D<T>& rhs)
    {
        return Vector2D<T>(m_x + rhs.m_x, m_y + rhs.m_y);
    }

    Vector2D<T> operator-(const Vector2D<T>& rhs)
    {
        return Vector2D<T>(m_x - rhs.m_x, m_y - rhs.m_y);
    }

    Vector2D<T> operator*(const Vector2D<T>& rhs)
    {
        return Vector2D<T>(m_x * rhs.m_x, m_y * rhs.m_y);
    }

    Vector2D<T> operator/(const Vector2D<T>& rhs)
    {
        return Vector2D<T>(m_x / rhs.m_x, m_y / rhs.m_y);
    }

public:
    Vector2D<T> operator+=(const Vector2D<T>& rhs)
    {
        m_x += rhs.m_x;
        m_y += rhs.m_y;
    }

    Vector2D<T> operator-=(const Vector2D<T>& rhs)
    {
        m_x -= rhs.m_x;
        m_y -= rhs.m_y;
    }

    Vector2D<T> operator*=(const Vector2D<T>& rhs)
    {
        m_x *= rhs.m_x;
        m_y *= rhs.m_y;
    }

    Vector2D<T> operator/=(const Vector2D<T>& rhs)
    {
        m_x /= rhs.m_x;
        m_y /= rhs.m_y;
    }

private:
    T m_x;
    T m_y;
};

using Vector2DF = Vector2D<float>;
using Vector2DI = Vector2D<int>;
using Vector2DUI = Vector2D<unsigned int>;
using Vector2DS = Vector2D<size_t>;