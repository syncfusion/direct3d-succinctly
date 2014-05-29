// PixelShader.cpp
#include "pch.h"
#include "PixelShader.h"

void PixelShader::LoadFromFile(ID3D11Device *device,
 _In_ Platform::String^ filename)
{

// Read the file
Platform::Array<unsigned char, 1U>^  fileDataPS = DX::ReadData(filename);

// Create a pixel shader from the data in the file:
DX::ThrowIfFailed(device->CreatePixelShader(fileDataPS->Data, fileDataPS->Length, nullptr, &m_pixelShader));

}