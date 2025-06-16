#pragma once
#include <memory>
class Player;
class enemy;
class Camera;
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
	void DrawGrid() const;
private:
	int m_playerHandle;
	//int m_enemyHandle; // 敵のモデルハンドル

	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<enemy> m_pEnemy;
	std::shared_ptr<Camera> m_pCamera; // カメラのポインタ
};

