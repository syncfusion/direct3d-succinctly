// VertexShader.cpp

#include "pch.h"
#include "VertexShader.h"

void VertexShader::LoadFromFile(ID3D11Device *device, _In_ Platform::String^ filename)
{
	// Read the file
	Platform::Array<unsigned char, 1U>^ fileDataVS =DX::ReadData(filename);

	// Crreate the vertex shader from the file's data
	DX::ThrowIfFailed(device->CreateVertexShader(fileDataVS->Data, fileDataVS->Length, nullptr, &m_vertexShader));

	// Describe the layout of the data
	const D3D11_INPUT_ELEMENT_DESC vertexDesc[] =  {
		{
			"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,
		D3D11_INPUT_PER_VERTEX_DATA, 0
		},
		
		{ "NORMAL",  0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12,
  D3D11_INPUT_PER_VERTEX_DATA, 0 },

		{
			"TEXCOORD",    0, DXGI_FORMAT_R32G32_FLOAT, 0, 24,
			D3D11_INPUT_PER_VERTEX_DATA, 0 
		},
	};

	DX::ThrowIfFailed(device->CreateInputLayout (vertexDesc,ARRAYSIZE(vertexDesc), fileDataVS->Data, fileDataVS->Length, &m_inputLayout));

} 