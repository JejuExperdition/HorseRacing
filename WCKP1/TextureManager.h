#pragma once
#include "Texture.h"
#include "Singleton.h"
#include <map>

class TextureManager : public Singleton<TextureManager>
{
public:
	TextureManager();
	~TextureManager();

	void addTexture(const char* name);
	Texture& getTexture(const char* name);

private:
	std::map<const char*, Texture*> m_Textures;
};