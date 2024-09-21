#pragma once
#include "Vector2D.h"

class Transform
{
public:
    Transform(const Vector2DF& position = Vector2DF(), const Vector2DF& scale = Vector2DF(1.f, 1.f), float rotation = 0) :
        m_position(position),
        m_scale(scale),
        m_rotation(rotation)
    {
    }

public:
    Vector2DF& GetPositionMut()
    {
        return m_position;
    }
    const Vector2DF& GetPosition() const
    {
        return m_position;
    }

    void SetPosition(const Vector2DF& value)
    {
        m_position = value;
    }

    Vector2DF& GetScaleMut()
    {
        return m_scale;
    }
    const Vector2DF& GetScale() const
    {
        return m_scale;
    }

    void SetScale(const Vector2DF& value)
    {
        m_scale = value;
    }

    float GetRotation() const
    {
        return m_rotation;
    }

    void SetRotation(float value)
    {
        m_rotation = value;
    }

private:
    Vector2DF m_position;
    Vector2DF m_scale;
    float m_rotation;
};