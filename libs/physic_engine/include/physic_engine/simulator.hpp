#include "body.hpp"

class Simulator
{
public:
    void addBody(const Body& body)
    {
        m_bodies.push_back(body);
    }

    void simulate(double dt);

private:
    std::vector<Body> m_bodies;
};