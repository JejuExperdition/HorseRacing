#pragma once
#include <D3D11.h>

class Shader
{
public:
	Shader(ID3D11Device* device);
	Shader(Shader&) = delete;
	~Shader();

	void bind(ID3D11DeviceContext* deviceContext);
private:
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11InputLayout* m_InputLayout;
};