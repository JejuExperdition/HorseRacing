#pragma once
#include "Singleton.h"
#include "GameLevel.h"
#include "Shader.h"
#include <D3D11.h>
#include <xnamath.h>

const class Graphics : public Singleton<Graphics>
{
public:
	Graphics();
	Graphics(Graphics&) = delete;
	~Graphics();

	ID3D11Device* getDevice() const;
	ID3D11DeviceContext* getDeviceContext() const;

	void drawLevel(GameLevel* level);
private:
	ID3D11Device* m_Device;
	ID3D11DeviceContext* m_DeviceContext;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	IDXGISwapChain* m_SwapChain;
	ID3D11RenderTargetView* m_RenderTargetView;
	ID3D11Texture2D* m_DepthStencilBuffer;
	ID3D11DepthStencilView* m_DepthStencilView;
	ID3D11SamplerState* m_SamplerState;
	ID3D11Buffer* m_OrthoMatrixBuffer;
	Shader* m_Shader;
};