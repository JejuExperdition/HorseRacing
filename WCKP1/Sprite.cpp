#include "Sprite.h"

Sprite::Sprite(int count, float speed, std::vector<std::string> names) :
	m_TextureCount(count),
	m_Textures(new Texture*[count]),
	m_Speed(speed),
	m_AcTime(0),
	m_Index(0),
	m_StartIndex(0),
	m_EndIndex(count)
{
	for (int i = 0; i < m_TextureCount; i++)
	{
		m_Textures[i] = &TextureManager::getInstance()->getTexture(names[i].c_str());
	}
}

Sprite::Sprite(int count, std::vector<std::string> names) :
	Sprite(count, 60, names)
{

}

Sprite::Sprite(std::string name) :
	Sprite(1, 60, std::vector<std::string>({ name }))
{

}

Sprite::Sprite(std::string name, float fps) :
	Sprite(1, fps, std::vector<std::string>({ name }))
{

}

Sprite::~Sprite()
{
	delete[] m_Textures;
}

void Sprite::setIndex(int start, int end)
{
	m_StartIndex = start;
	m_EndIndex = end;
}

void Sprite::update(float deltaTime)
{
	m_AcTime += deltaTime;
	while (m_AcTime >= 1 / m_Speed)
	{
		m_Index += 1;
		m_AcTime -= 1 / m_Speed;
	}
	m_Index %= (m_EndIndex - m_StartIndex);
}

void Sprite::bind(ID3D11DeviceContext* deviceContext)
{
	m_Textures[m_Index + m_StartIndex]->bind(deviceContext);
}