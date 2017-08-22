#include "Texture.h"
#include "Error.h"
#include <D3DX11.h>

Texture::Texture(ID3D11Device* device, const char* path):
	m_Image(nullptr)
{
	HRESULT hr;

	hr = D3DX11CreateShaderResourceViewFromFileA(device, path, nullptr, nullptr, &m_Image, nullptr);
	errorByHresult(hr, "CreateShaderResource Failed");
}

Texture::~Texture()
{
	if (m_Image)
	{
		m_Image->Release();
		m_Image = nullptr;
	}
}

void Texture::bind(ID3D11DeviceContext* deviceContext)
{
	deviceContext->PSSetShaderResources(0, 1, &m_Image);
}