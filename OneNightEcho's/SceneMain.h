#pragma once
#include "Pad.h"
#include <memory>
class player;
class enemy;
class SceneMain
{
public:
	SceneMain();
	~SceneMain();
	void Init();
	void End();
	void Update();
	void Draw();
private:
	std::shared_ptr<player> m_pPlayer;
	std::shared_ptr<enemy> m_pEnemy;
};

