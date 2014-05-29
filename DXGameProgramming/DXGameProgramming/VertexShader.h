// VertexShader.h
#pragma once

#include "DirectXHelper.h"

class VertexShader {
private:
 ID3D11VertexShader*m_vertexShader;
 Microsoft::WRL::ComPtr<ID3D11InputLayout> m_inputLayout;

public:
 // Loads a compiled vertex shader from a CSO file
 void LoadFromFile(ID3D11Device *device,  _In_ Platform::String^ filename);

 // Returns pointer to vertex shader
 ID3D11VertexShader* GetVertexShader() { return m_vertexShader; }

 // Returns pointer to input layout
 ID3D11InputLayout* GetInputLayout() { return m_inputLayout.Get(); }

};