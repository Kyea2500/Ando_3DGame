#pragma once
#include <memory>
class SceneTitle;
class SceneMain;
class SceneGameClera;
class SceneManager
{
public:
	SceneManager();
	~SceneManager();
	void Init();
	void End();
	void Update();
	void Draw();
public:
	enum SceneKind
	{
		kSceneTitle,
		kSceneMain,
		kSceneGameClear,
		kSceneNum
	};private:
		SceneKind m_Kind;
		// 各シーンのポインタ
		SceneTitle* m_pSceneTitle;
		SceneMain* m_pSceneMain;
		SceneGameClera* m_pSceneClera;

};

