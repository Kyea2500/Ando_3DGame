#pragma once
#include "../../Parts/Transform/transform.h"
#include <memory>

class GameObject
{
private:
	std::shared_ptr<Transform> m_transform;

public:

	std::shared_ptr<Transform> GetTransform() const { return m_transform; }

};