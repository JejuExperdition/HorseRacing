#include "Sprite.h"

Sprite::Sprite(int count, float speed, const char** names) :
	m_TextureCount(count),
	m_Textures(new Texture*[count]),
	m_Speed(speed),
	m_AcTime(0),
	m_Index(0)
{
	for (int i = 0; i < m_TextureCount; i++)
	{
		m_Textures[i] = &TextureManager::getInstance()->getTexture(names[i]);
	}
}

Sprite::Sprite(int count, const char** names) :
	Sprite(count, 60, names)
{

}

Sprite::Sprite(const char* name) :
	Sprite(1, 60, &name)
{

}

Sprite::Sprite(const char* name, float fps) :
	Sprite(1, fps, &name)
{

}

Sprite::~Sprite()
{
	delete[] m_Textures;
}

void Sprite::update(float deltaTime)
{
	m_AcTime += deltaTime;
	while (m_AcTime >= 1 / m_Speed)
	{
		m_Index += 1;
		m_AcTime -= 1 / m_Speed;
	}
	m_Index %= m_TextureCount;
}

void Sprite::bind(ID3D11DeviceContext* deviceContext)
{
	m_Textures[m_Index]->bind(deviceContext);
}