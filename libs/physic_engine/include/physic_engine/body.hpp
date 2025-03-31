#include "Eigen/Dense"

class Body
{
public:
    Body(const Eigen::Vector3f& position);

    Eigen::Vector3f getPosition() const
    {
        return m_position;
    }

    Eigen::Vector3f getVelocity() const
    {
        return m_velocity;
    }

    Eigen::Vector3f getAcceleration() const
    {
        return m_acceleration;
    }

    void setPosition(const Eigen::Vector3f& position)
    {
        m_position = position;
    }
    void setVelocity(const Eigen::Vector3f& velocity)
    {
        m_velocity = velocity;
    }

    void shiftPosition(const Eigen::Vector3f& shift)
    {
        m_position += shift;
    }

    void shiftVelocity(const Eigen::Vector3f& shift)
    {
        m_velocity += shift;
    }

private:
    Eigen::Vector3f m_position;
    Eigen::Vector3f m_velocity;
    Eigen::Vector3f m_acceleration;
};