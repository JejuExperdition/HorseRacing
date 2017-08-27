#include "TextureManager.h"
#include "Graphics.h"
#include <string>

TextureManager::TextureManager():
	m_Textures()
{

}

TextureManager::~TextureManager()
{

}

void TextureManager::addTexture(const char* name)
{
	if (m_Textures.count(name) == 0)
	{
		std::string path = "./res/";
		path += name;
		path += ".dds";
		Texture* tex = new Texture(Graphics::getInstance()->getDevice(), path.c_str());
		m_Textures.insert(std::pair<const char*, Texture*>(name, tex));
	}
}

Texture& TextureManager::getTexture(const char* name)
{
	if (m_Textures.count(name) == 1)
	{
		return *m_Textures.at(name);
	}
	else
	{
		addTexture(name);
		return *m_Textures.at(name);
	}
}