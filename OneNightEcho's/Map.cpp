#include "Map.h"
#include "DxLib.h"

Map::Map(): m_Width(0),
	m_Height(0), 
	m_MapImage(0), 
	m_X(0),
	m_Y(0)
{
}

Map::~Map()
{
}

void Map::Init()
{// �}�b�v�̃T�C�Y��ݒ�
	m_Width = 10;
	m_Height = 10;
	// �}�b�v�̃f�[�^��������
	for (int y = 0; y < m_Height; ++y)
	{
		for (int x = 0; x < m_Width; ++x)
		{
			m_MapData[y][x] = 0; // ��̃}�b�v
		}
	}
	// �}�b�v�̉摜��ǂݍ���
	m_MapImage = LoadGraph("map.png");
	if (m_MapImage == -1)
	{
		// �G���[����
		// �摜�̓ǂݍ��݂Ɏ��s�����ꍇ�A�G���[���b�Z�[�W��\��
		DrawString(0, 0, "Failed to load map image", GetColor(255, 0, 0));
	}
}

void Map::End()
{
	// �}�b�v�̉摜�����
	if (m_MapImage != -1)
	{
		DeleteGraph(m_MapImage);
		m_MapImage = -1;
	}
}

void Map::Update()
{

}

void Map::Draw()
{
}
