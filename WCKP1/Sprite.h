#pragma once
#include "TextureManager.h"
#include <string>
#include <vector>

class Sprite
{
public:
	Sprite(std::string name);
	Sprite(std::string name, float fps);
	Sprite(int count, std::vector<std::string> names);
	Sprite(int count, float fps, std::vector<std::string> names);
	~Sprite();

	void setIndex(int start, int end);
	void update(float deltaTime);
	void bind(ID3D11DeviceContext* deviceContext);

private:
	Texture** m_Textures;
	int m_TextureCount;
	float m_Speed;
	float m_AcTime;
	int m_Index;
	int m_StartIndex;
	int m_EndIndex;
};