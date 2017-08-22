#pragma once
#include <D3D11.h>
#include <xnamath.h>

class VertexArray
{
private:
	struct VertexInputType
	{
		XMFLOAT4 pos;
		XMFLOAT2 tex;
	};
public:
	VertexArray(ID3D11Device* device, float width, float height, float depth);
	VertexArray(VertexArray&) = delete;
	~VertexArray();

	void draw(ID3D11DeviceContext* deviceContext);
private:
	ID3D11Buffer* m_VertexBuffer;
	ID3D11Buffer* m_IndexBuffer;
};