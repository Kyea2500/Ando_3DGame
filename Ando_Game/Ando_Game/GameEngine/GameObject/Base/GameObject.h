#pragma once
#include "../../Parts/Transform/transform.h"
#include "../../Parts/Velocity/Velocity.h"
#include <memory>

class GameObject
{
private:
	std::shared_ptr<Transform> m_transform;
	std::shared_ptr<Velocity> m_velocity;
public:

	std::shared_ptr<Transform> GetTransform() const { return m_transform; }
	std::shared_ptr<Velocity> GetVelocity() const { return m_velocity; }
};