#pragma once
#include <D3D11.h>
#include <xnamath.h>
#include "VertexArray.h"
#include "Sprite.h"

class GameObject
{
public:
	GameObject(ID3D11Device* device, float width, float height, float depth, Sprite* spr);
	GameObject(GameObject&) = delete;
	virtual ~GameObject();

	virtual void updateAll(float deltaTime) final;
	virtual void update(float deltaTime) = 0;
	virtual void draw(ID3D11DeviceContext* deviceContext) final;
protected:
	virtual void setPosition(const XMFLOAT2& pos) final { m_Position = pos; }
	virtual void setPosition(const XMFLOAT2&& pos) final { m_Position = pos; }
	virtual const XMFLOAT2& getPosition() const final { return m_Position; }

	virtual void setSize(const XMFLOAT2& size) final { m_Size = size; }
	virtual void setSize(const XMFLOAT2&& size) final { m_Size = size; }
	virtual const XMFLOAT2& getSize() const final { return m_Size; }

	virtual void setAngle(float angle) final { m_Angle = angle; }
	virtual float getAngle() const final { return m_Angle; }
private:
	VertexArray m_VertexArray;
	Sprite* m_Sprite;
	XMFLOAT2 m_Position;
	XMFLOAT2 m_Size;
	float m_Angle;
	ID3D11Buffer* m_WorldMatrixBuffer;
};