#pragma once
class Map
{
public:
	Map();
	~Map();
	void Init();
	void End();
	void Update();
	void Draw();
private:
	// �}�b�v�̃f�[�^
	int m_MapData[10][10];
	// �}�b�v�̃T�C�Y
	int m_Width;
	int m_Height;
	// �}�b�v�̉摜
	int m_MapImage;
	// �}�b�v�̈ʒu
	int m_X;
	int m_Y;
};

