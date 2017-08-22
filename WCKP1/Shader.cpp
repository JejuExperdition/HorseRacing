#include "Shader.h"
#include "Error.h"
#include <D3DX11.h>

Shader::Shader(ID3D11Device* device)
{
	HRESULT hr;

	ID3D10Blob* vertexShaderBuffer = nullptr;
	ID3D10Blob* pixelShaderBuffer = nullptr;
	ID3D10Blob* errorMessageBuffer = nullptr;

	hr = D3DX11CompileFromFileA("./VertexShader.hlsl", nullptr, nullptr, "main", "vs_5_0", 0, NULL, nullptr, &vertexShaderBuffer, &errorMessageBuffer, nullptr);
	if (errorMessageBuffer)
	{
		errorByHresult(hr, static_cast<char *>(errorMessageBuffer->GetBufferPointer()));
	}
	else
	{
		errorByHresult(hr, "No Vertex Shader File");
	}

	hr = D3DX11CompileFromFileA("./PixelShader.hlsl", nullptr, nullptr, "main", "ps_5_0", 0, NULL, nullptr, &pixelShaderBuffer, &errorMessageBuffer, nullptr);
	if (errorMessageBuffer)
	{
		errorByHresult(hr, static_cast<char *>(errorMessageBuffer->GetBufferPointer()));
	}
	else
	{
		errorByHresult(hr, "No Pixel Shader File");
	}

	D3D11_INPUT_ELEMENT_DESC ied[2];
	ied[0].AlignedByteOffset = 0;
	ied[0].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
	ied[0].InputSlot = 0;
	ied[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	ied[0].InstanceDataStepRate = 0;
	ied[0].SemanticIndex = 0;
	ied[0].SemanticName = "POSITION";

	ied[1].AlignedByteOffset = D3D11_APPEND_ALIGNED_ELEMENT;
	ied[1].Format = DXGI_FORMAT_R32G32_FLOAT;
	ied[1].InputSlot = 0;
	ied[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
	ied[1].InstanceDataStepRate = 0;
	ied[1].SemanticIndex = 0;
	ied[1].SemanticName = "TEXCOORD";

	hr = device->CreateInputLayout(ied, 2, vertexShaderBuffer->GetBufferPointer(),
		vertexShaderBuffer->GetBufferSize(), &m_InputLayout);
	errorByHresult(hr, "Create InputLayout Failed");

	hr = device->CreateVertexShader(vertexShaderBuffer->GetBufferPointer(), vertexShaderBuffer->GetBufferSize(),
		nullptr, &m_VertexShader);
	errorByHresult(hr, "Create VertexShader Failed");

	hr = device->CreatePixelShader(pixelShaderBuffer->GetBufferPointer(), pixelShaderBuffer->GetBufferSize(),
		nullptr, &m_PixelShader);
	errorByHresult(hr, "Create PixelShader Failed");

	vertexShaderBuffer->Release();
	pixelShaderBuffer->Release();
	if (errorMessageBuffer)
	{
		errorMessageBuffer->Release();
	}
}

Shader::~Shader()
{
	if (m_InputLayout)
	{
		m_InputLayout->Release();
		m_InputLayout = nullptr;
	}
	if (m_VertexShader)
	{
		m_VertexShader->Release();
		m_VertexShader = nullptr;
	}
	if (m_PixelShader)
	{
		m_PixelShader->Release();
		m_PixelShader = nullptr;
	}
}

void Shader::bind(ID3D11DeviceContext* deviceContext)
{
	deviceContext->IASetInputLayout(m_InputLayout);
	deviceContext->VSSetShader(m_VertexShader, nullptr, 0);
	deviceContext->PSSetShader(m_PixelShader, nullptr, 0);
}