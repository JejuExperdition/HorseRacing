#pragma once
#include <D3D11.h>
#include <xnamath.h>

class Camera
{
public:
	Camera(ID3D11Device* device);
	Camera(Camera&) = delete;
	Camera(ID3D11Device* device, XMFLOAT2 pos);
	~Camera();

	void move(const XMFLOAT2& pos);
	void move(const XMFLOAT2&& pos);
	const XMFLOAT2& getPosition() const;
	void setPosition(const XMFLOAT2& pos);
	void setPosition(const XMFLOAT2&& pos);

	float getAngle() const;
	void setAngle(float angle);
	void spin(float angle);

	void draw(ID3D11DeviceContext* deviceContext);
private:
	ID3D11Buffer* m_ViewMatrixBuffer;
	XMFLOAT2 m_Position;
	float m_Angle;
};