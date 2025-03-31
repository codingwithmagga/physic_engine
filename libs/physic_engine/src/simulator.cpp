#include "physic_engine/simulator.hpp"

void Simulator::simulate(double dt)
{
    for (Body& body : m_bodies)
    {
        const auto acc = body.getAcceleration();
        const auto acc_at_dt = body.getAcceleration();

        const Eigen::Vector3f positionShift = body.getVelocity() + 0.5 * acc * dt * dt;
        const Eigen::Vector3f velocityShift = 0.5 * (acc + acc_at_dt) * dt;

        body.shiftPosition(positionShift);
        body.shiftVelocity(velocityShift);
    }
}
