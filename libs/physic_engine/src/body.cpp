#include "physic_engine/body.hpp"

using Eigen::Vector3f;

Body::Body(const Vector3f& position)
    : m_position(position)
    , m_velocity(Vector3f::Zero())
    , m_acceleration({0, 0, -9.81f})
{
}

