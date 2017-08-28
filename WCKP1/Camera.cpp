#include "Camera.h"
#include "Error.h"
#include <utility>

Camera::Camera(ID3D11Device* device) :
	Camera(device, { 0.0f, 0.0f })
{

}

Camera::~Camera()
{
	if (m_ViewMatrixBuffer)
	{
		m_ViewMatrixBuffer->Release();
		m_ViewMatrixBuffer = nullptr;
	}
}

Camera::Camera(ID3D11Device* device, XMFLOAT2 pos) :
	m_ViewMatrixBuffer(nullptr),
	m_Position(pos),
	m_Angle(XM_PIDIV2)
{
	D3D11_BUFFER_DESC vbd;
	vbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	vbd.ByteWidth = sizeof(XMFLOAT4X4);
	vbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vbd.MiscFlags = 0;
	vbd.StructureByteStride = 0;
	vbd.Usage = D3D11_USAGE_DYNAMIC;

	float x = XMScalarCos(m_Angle);
	XMMATRIX viewMatrix = XMMatrixLookAtLH(XMLoadFloat2(&m_Position), { 0.0f, 0.0f, 1.0f, 0.0f }, { 0.0f, 1.0f, 0.0f, 0.0f });
	XMFLOAT4X4 view;
	XMStoreFloat4x4(&view, viewMatrix);

	D3D11_SUBRESOURCE_DATA vrd;
	vrd.pSysMem = static_cast<void *>(&view);
	vrd.SysMemPitch = 0;
	vrd.SysMemSlicePitch = 0;

	HRESULT hr = device->CreateBuffer(&vbd, &vrd, &m_ViewMatrixBuffer);
	errorByHresult(hr, "Create ViewMatrixBuffer Failed");
}

void Camera::move(const XMFLOAT2& pos)
{
	m_Position.x += pos.x;
	m_Position.y += pos.y;
}

void Camera::move(const XMFLOAT2&& pos)
{
	m_Position.x += pos.x;
	m_Position.y += pos.y;
}

const XMFLOAT2& Camera::getPosition() const
{
	return m_Position;
}

void Camera::setPosition(const XMFLOAT2& pos)
{
	m_Position = pos;
}

void Camera::setPosition(const XMFLOAT2&& pos)
{
	m_Position = pos;
}

float Camera::getAngle() const
{
	return m_Angle;
}

void Camera::setAngle(float angle)
{
	m_Angle = angle;
}

void Camera::spin(float angle)
{
	m_Angle += angle;
}

void Camera::draw(ID3D11DeviceContext* deviceContext)
{
	XMMATRIX viewMatrix = XMMatrixLookToLH(XMLoadFloat2(&m_Position), 
	{ 0.0f, 0.0f, 1.0f, 0.0f }, { XMScalarCos(m_Angle), XMScalarSin(m_Angle), 0.0f, 0.0f });

	D3D11_MAPPED_SUBRESOURCE vmr;
	HRESULT hr = deviceContext->Map(m_ViewMatrixBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &vmr);
	errorByHresult(hr, "Mapping ViewMatrix Failed");

	XMStoreFloat4x4(static_cast<XMFLOAT4X4*>(vmr.pData), XMMatrixTranspose(viewMatrix));

	deviceContext->Unmap(m_ViewMatrixBuffer, 0);

	deviceContext->VSSetConstantBuffers(1, 1, &m_ViewMatrixBuffer);
}