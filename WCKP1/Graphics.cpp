#include "Graphics.h"
#include "GameWindow.h"
#include "Error.h"

Graphics::Graphics():
	m_Device(nullptr),
	m_DeviceContext(nullptr),
	m_SwapChain(nullptr),
	m_RenderTargetView(nullptr),
	m_DepthStencilBuffer(nullptr),
	m_DepthStencilView(nullptr),
	m_OrthoMatrixBuffer(nullptr),
	m_SamplerState(nullptr),
	m_Shader(nullptr)
{
	HRESULT hr;

	DXGI_SWAP_CHAIN_DESC sd;
	sd.BufferCount = 2;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.Height = 1080;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.BufferDesc.Width = 1920;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.Flags = 0;
	sd.OutputWindow = GameWindow::getInstance()->getWindowHandle();
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Windowed = true;

	UINT createDeviceFlags = D3D11_CREATE_DEVICE_SINGLETHREADED;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	hr = D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, createDeviceFlags, 
		nullptr, 0, D3D11_SDK_VERSION, &sd, &m_SwapChain, &m_Device, &m_FeatureLevel, &m_DeviceContext);
	errorByHresult(hr, "CreateDeviceAndSwapChain Failed");

	ID3D11Texture2D *backBuffer = nullptr;
	hr = m_SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void **>(&backBuffer));
	errorByHresult(hr, "Get BackBuffer Failed");

	hr = m_Device->CreateRenderTargetView(backBuffer, nullptr, &m_RenderTargetView);
	errorByHresult(hr, "CreateRenderTargetView Failed");

	D3D11_TEXTURE2D_DESC dsd;
	dsd.ArraySize = 1;
	dsd.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	dsd.CPUAccessFlags = 0;
	dsd.Format = DXGI_FORMAT_D32_FLOAT_S8X24_UINT;
	dsd.Height = 1080;
	dsd.MipLevels = 1;
	dsd.MiscFlags = 0;
	dsd.SampleDesc.Count = 1;
	dsd.SampleDesc.Quality = 0;
	dsd.Usage = D3D11_USAGE_DEFAULT;
	dsd.Width = 1920;

	hr = m_Device->CreateTexture2D(&dsd, nullptr, &m_DepthStencilBuffer);
	errorByHresult(hr, "Create DepthStencilBuffer Failed");

	m_Device->CreateDepthStencilView(m_DepthStencilBuffer, nullptr, &m_DepthStencilView);

	m_DeviceContext->OMSetRenderTargets(1, &m_RenderTargetView, m_DepthStencilView);

	D3D11_VIEWPORT vp;
	vp.Height = 1080;
	vp.MaxDepth = 1;
	vp.MinDepth = 0;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
	vp.Width = 1920;

	m_DeviceContext->RSSetViewports(1, &vp);

	XMMATRIX orthoMatrix = XMMatrixOrthographicLH(1920, 1080, 0, 11);
	XMFLOAT4X4 ortho;
	XMStoreFloat4x4(&ortho, XMMatrixTranspose(orthoMatrix));

	D3D11_BUFFER_DESC obd;
	obd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	obd.ByteWidth = sizeof(XMFLOAT4X4);
	obd.CPUAccessFlags = 0;
	obd.MiscFlags = 0;
	obd.StructureByteStride = 0;
	obd.Usage = D3D11_USAGE_DEFAULT;
	
	D3D11_SUBRESOURCE_DATA ord;
	ord.pSysMem = static_cast<void *>(&ortho);
	ord.SysMemPitch = 0;
	ord.SysMemSlicePitch = 0;

	hr = m_Device->CreateBuffer(&obd, &ord, &m_OrthoMatrixBuffer);
	errorByHresult(hr, "Create OrthoMatrixBuffer Failed");

	D3D11_SAMPLER_DESC ssd;
	ssd.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	ssd.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	ssd.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	ssd.BorderColor[0] = 1.0f;
	ssd.BorderColor[1] = 1.0f;
	ssd.BorderColor[2] = 1.0f;
	ssd.BorderColor[3] = 1.0f;
	ssd.ComparisonFunc = D3D11_COMPARISON_LESS_EQUAL;
	ssd.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	ssd.MaxAnisotropy = 1;
	ssd.MaxLOD = D3D11_FLOAT32_MAX;
	ssd.MinLOD = 0;
	ssd.MipLODBias = 0;

	m_Device->CreateSamplerState(&ssd, &m_SamplerState);

	m_Shader = new Shader(m_Device);
}

Graphics::~Graphics()
{
	if (m_Shader)
	{
		delete m_Shader;
		m_Shader = nullptr;
	}
	if (m_DepthStencilView)
	{
		m_DepthStencilView->Release();
		m_DepthStencilView = nullptr;
	}
	if (m_DepthStencilBuffer)
	{
		m_DepthStencilBuffer->Release();
		m_DepthStencilBuffer = nullptr;
	}
	if (m_RenderTargetView)
	{
		m_RenderTargetView->Release();
		m_RenderTargetView = nullptr;
	}
	if (m_SwapChain)
	{
		m_SwapChain->Release();
		m_SwapChain = nullptr;
	}
	if (m_DeviceContext)
	{
		m_DeviceContext->Release();
		m_DeviceContext = nullptr;
	}
	if (m_Device)
	{
		m_Device->Release();
		m_Device = nullptr;
	}
}

ID3D11Device* Graphics::getDevice() const
{
	return m_Device;
}

ID3D11DeviceContext* Graphics::getDeviceContext() const
{
	return m_DeviceContext;
}

void Graphics::drawLevel(GameLevel* level)
{
	float bg[4] = { 0.0f, 1.0f, 1.0f, 0.0f };
	m_DeviceContext->ClearRenderTargetView(m_RenderTargetView, bg);
	m_DeviceContext->ClearDepthStencilView(m_DepthStencilView, D3D11_CLEAR_DEPTH, 1.0f, 0);

	m_Shader->bind(m_DeviceContext);

	m_DeviceContext->PSSetSamplers(0, 1, &m_SamplerState);
	m_DeviceContext->VSSetConstantBuffers(2, 1, &m_OrthoMatrixBuffer);

	level->draw(m_DeviceContext);

	m_SwapChain->Present(1, 0);
}