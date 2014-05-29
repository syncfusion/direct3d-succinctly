#pragma once

#include "DirectXBase.h"
#include "Model.h" 
#include "VertexShader.h"
#include "PixelShader.h"
#include "ModelReader.h"
#include "Texture.h"
#include "Keyboard.h"
#include "GameObject.h"
#include "BitmapBackground.h"
#include <string>

// This class renders simple text with a colored background.
ref class SimpleTextRenderer sealed : public DirectXBase
{
public:
	SimpleTextRenderer();

	// DirectXBase methods.
	virtual void CreateDeviceIndependentResources() override;
	virtual void CreateDeviceResources() override;
	virtual void CreateWindowSizeDependentResources() override;
	virtual void Render() override;

	// Method for updating time-dependent objects.
	void Update(float timeTotal, float timeDelta);

	// Keyboard methods:
	void KeyDown(Windows::System::VirtualKey key);
	void KeyUp(Windows::System::VirtualKey key);

	private:  
		Model *m_model;

		Microsoft::WRL::ComPtr<ID3D11Buffer> m_constantBufferGPU;  
		ModelViewProjectionConstantBuffer m_constantBufferCPU;
		Texture m_texture;
		ID3D11SamplerState *m_samplerState;

		// Shaders
		VertexShader m_vertexShader;
		PixelShader m_pixelShader;

		// Keyboard member variable
		Keyboard m_keyboard;

		// Game objects and background
		GameObject m_spaceship;
		GameObject m_baddies[5];
		GameObject m_bullet;
		BitmapBackground  m_bitmapbackground;
		Texture m_baddieTexture;
		
		// Variables for printing the user's score
		int m_playerScore; // The player's score
		Microsoft::WRL::ComPtr<IDWriteTextFormat> m_textFormat;
		Microsoft::WRL::ComPtr<ID2D1SolidColorBrush> m_scoreBrush;

};
