#pragma once
#include "TextureManager.h"

class Sprite
{
public:
	Sprite(const char* name);
	Sprite(const char* name, float fps);
	Sprite(int count, const char** names);
	Sprite(int count, float fps, const char** names);
	~Sprite();

	void update(float deltaTime);
	void bind(ID3D11DeviceContext* deviceContext);
private:
	Texture** m_Textures;
	int m_TextureCount;
	float m_Speed;
	float m_AcTime;
	int m_Index;
};