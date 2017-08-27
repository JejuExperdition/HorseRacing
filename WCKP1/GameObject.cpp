#include "GameObject.h"
#include "Error.h"

GameObject::GameObject(ID3D11Device* device, float width, float height, float depth, Sprite* spr):
	m_VertexArray(device, width, height, depth),
	m_Sprite(spr),
	m_Position({ 0.0f, 0.0f }),
	m_Size({ 1.0f, 1.0f }),
	m_Angle( 0 )
{
	D3D11_BUFFER_DESC mbd;
	mbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	mbd.ByteWidth = sizeof(XMFLOAT4X4);
	mbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	mbd.MiscFlags = 0;
	mbd.StructureByteStride = 0;
	mbd.Usage = D3D11_USAGE_DYNAMIC;

	XMMATRIX translate = XMMatrixTranslation(m_Position.x, m_Position.y, 0);
	XMMATRIX rotate = XMMatrixRotationAxis({ 0.0, 0.0f, 1.0f, 0.0f }, m_Angle);
	XMMATRIX scale = XMMatrixScaling(m_Size.x, m_Size.y, 1.0f);

	XMMATRIX world = scale * rotate * translate;
	XMFLOAT4X4 worldMatrix;
	XMStoreFloat4x4(&worldMatrix, XMMatrixTranspose(world));

	D3D11_SUBRESOURCE_DATA mrd;
	mrd.pSysMem = static_cast<void *>(&worldMatrix);
	mrd.SysMemPitch = 0;
	mrd.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateBuffer(&mbd, &mrd, &m_WorldMatrixBuffer);
	errorByHresult(hr, "Create WorldMatrixBuffer Failed");
}

GameObject::~GameObject()
{
	if (m_WorldMatrixBuffer)
	{
		m_WorldMatrixBuffer->Release();
		m_WorldMatrixBuffer = nullptr;
	}
}

void GameObject::updateAll(float deltaTime)
{
	m_Sprite->update(deltaTime);
	update(deltaTime);
}

void GameObject::draw(ID3D11DeviceContext* deviceContext)
{
	XMMATRIX translate = XMMatrixTranslation(m_Position.x, m_Position.y, 0);
	XMMATRIX rotate = XMMatrixRotationAxis({ 0.0, 0.0f, 1.0f, 0.0f }, m_Angle);
	XMMATRIX scale = XMMatrixScaling(m_Size.x, m_Size.y, 1.0f);

	XMMATRIX world = scale * rotate * translate;
	
	D3D11_MAPPED_SUBRESOURCE mmr;

	HRESULT hr = deviceContext->Map(m_WorldMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mmr);
	errorByHresult(hr, "Map WorldMatrixBuffer Failed");

	XMStoreFloat4x4(static_cast<XMFLOAT4X4*>(mmr.pData), XMMatrixTranspose(world));

	deviceContext->Unmap(m_WorldMatrixBuffer, 0);

	deviceContext->VSSetConstantBuffers(0, 1, &m_WorldMatrixBuffer);

	m_Sprite->bind(deviceContext);
	m_VertexArray.draw(deviceContext);
}