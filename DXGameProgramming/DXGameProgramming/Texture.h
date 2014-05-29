// Texture.h
#pragma once

#include <Windows.h>
#include <string>
#include "Model.h"

using namespace DirectX;

// This class reads an image from a file and creates an
// ID3D11Texure2D and a ID3D11ShaderResourceView from it
class Texture
{
 Microsoft::WRL::ComPtr<ID3D11Texture2D> m_texture;
 Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> m_resourceView;
public:
 // Read a texture and create device resources
 void ReadTexture(ID3D11Device* device, IWICImagingFactory2* wicFactory, LPCWSTR filename);
 
 // Getters
 Microsoft::WRL::ComPtr<ID3D11Texture2D> GetTexure() 
 { 
	 return m_texture; 
 }

 Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>GetResourceView() 
 { 
	 return m_resourceView; 
 }

};