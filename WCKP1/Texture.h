#pragma once
#include <D3D11.h>

class Texture
{
public:
	Texture(ID3D11Device* device, const char* path);
	Texture(Texture&) = delete;
	~Texture();

	void bind(ID3D11DeviceContext* deviceContext);
private:
	ID3D11ShaderResourceView* m_Image;
};