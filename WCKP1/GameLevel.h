#pragma once
#include <D3D11.h>
#include <xnamath.h>
#include <set>
#include "Camera.h"
#include "BackGround.h"
#include "Texture.h"
#include "GameObject.h"

class GameLevel
{
public:
	GameLevel(ID3D11Device* device, const char* bgTexturePath);
	virtual ~GameLevel();
	virtual void update(float deltaTime) = 0;
	virtual void draw(ID3D11DeviceContext* deviceContext) final;

protected:
	virtual void moveCamera(XMFLOAT2& pos) final { m_Camera.move(pos); }
	virtual void moveCamera(XMFLOAT2&& pos) final { m_Camera.move(pos); }
	virtual const XMFLOAT2& getCameraPos() const final { return m_Camera.getPosition(); }
	
	virtual void addObject(GameObject* obj) final { if(!isIncludeObject(obj)) m_ObjectSet.insert(obj); }
	virtual void removeObject(GameObject* obj) final { if (m_ObjectSet.count(obj) == 1) m_ObjectSet.erase(obj); }
	virtual bool isIncludeObject(GameObject* obj) const final { return m_ObjectSet.count(obj) == 1 ? true : false; }
private:
	Camera m_Camera;
	Texture m_BGTexture;
	BackGround m_Background;
	std::set<GameObject*> m_ObjectSet;
};