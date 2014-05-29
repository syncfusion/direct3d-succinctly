// PixelShader.h
#pragma once

#include "DirectXHelper.h"

class PixelShader
{
private:
 ID3D11PixelShader* m_pixelShader;

public:
 // Loads a compiled pixel shader from a CSO file
 void LoadFromFile(ID3D11Device *device, _In_ Platform::String^ filename);

 // Returns pointer to pixel shader
 ID3D11PixelShader* GetPixelShader() { return m_pixelShader; }

};