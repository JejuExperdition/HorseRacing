#include "VertexArray.h"
#include "Error.h"


VertexArray::VertexArray(ID3D11Device* device, float width, float height, float depth):
	m_VertexBuffer(nullptr),
	m_IndexBuffer(nullptr)
{
	HRESULT hr;

	D3D11_BUFFER_DESC vbd;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.ByteWidth = sizeof(VertexInputType) * 4;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	vbd.Usage = D3D11_USAGE_DEFAULT;

	VertexInputType vertices[] = {
		{ { -width / 2, +height / 2, depth, 1.0f}, { 0.0f, 0.0f} },
		{ { +width / 2, +height / 2, depth, 1.0f },{ 1.0f, 0.0f } },
		{ { +width / 2, -height / 2, depth, 1.0f },{ 1.0f, 1.0f } },
		{ { -width / 2, -height / 2, depth, 1.0f },{ 0.0f, 1.0f } },
	};

	D3D11_SUBRESOURCE_DATA vrd;
	vrd.pSysMem = static_cast<void *>(vertices);
	vrd.SysMemPitch = 0;
	vrd.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&vbd, &vrd, &m_VertexBuffer);
	errorByHresult(hr, "Create VertexBuffer Failed");

	D3D11_BUFFER_DESC ibd;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.ByteWidth = sizeof(UINT) * 6;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	ibd.StructureByteStride = 0;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;

	UINT indices[] = { 0, 1, 2, 0, 2, 3 };

	D3D11_SUBRESOURCE_DATA ird;
	ird.pSysMem = static_cast<void *>(indices);
	ird.SysMemPitch = 0;
	ird.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(&ibd, &ird, &m_IndexBuffer);
	errorByHresult(hr, "Create IndexBuffer Failed");
}

VertexArray::~VertexArray()
{
	if (m_VertexBuffer)
	{
		m_VertexBuffer->Release();
		m_VertexBuffer = nullptr;
	}
	if (m_IndexBuffer)
	{
		m_IndexBuffer->Release();
		m_IndexBuffer = nullptr;
	}
}

void VertexArray::draw(ID3D11DeviceContext* deviceContext)
{
	UINT stride = sizeof(VertexInputType);
	UINT offset = 0;

	deviceContext->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	deviceContext->IASetIndexBuffer(m_IndexBuffer, DXGI_FORMAT_R32_UINT, 0);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	deviceContext->DrawIndexed(6, 0, 0);
}