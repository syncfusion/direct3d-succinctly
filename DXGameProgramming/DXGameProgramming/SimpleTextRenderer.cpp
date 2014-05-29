// SimpleTextRenderer.cpp 
#include "pch.h" 
#include "SimpleTextRenderer.h"

using namespace D2D1; 
using namespace DirectX;
using namespace Microsoft::WRL; 
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections; 
using namespace Windows::UI::Core;

SimpleTextRenderer::SimpleTextRenderer() { } 

void SimpleTextRenderer::CreateDeviceIndependentResources() 
{ 
	DirectXBase::CreateDeviceIndependentResources();

	
 m_playerScore = 0;

 DX::ThrowIfFailed(
 m_dwriteFactory->CreateTextFormat(L"Segoe UI",
  nullptr, DWRITE_FONT_WEIGHT_NORMAL,
  DWRITE_FONT_STYLE_NORMAL,
  DWRITE_FONT_STRETCH_NORMAL,
  42.0f,L"en-US",
  &m_textFormat)); 

}  

void SimpleTextRenderer::CreateDeviceResources() 
{  
	DirectXBase::CreateDeviceResources(); 
		
 // Read the baddie model and texture
 Model *baddieModel = ModelReader::ReadModel(m_d3dDevice.Get(),"baddie.obj");
 m_baddieTexture.ReadTexture(m_d3dDevice.Get(),m_wicFactory.Get(), L"baddie.png");

 for(int i = 0; i < 5; i++)
  {
  m_baddies[i].SetModelAndTexture(baddieModel,&m_baddieTexture); 
    m_baddies[i].SetPosition((float)(i-2.5f)* 3.0f, 0.0f, 5.0f);
	m_baddies[i].SetObjectSize(1.0f);
    m_baddies[i].SetActive(true);
  }
	
 // Load the spaceship model and texture
 m_spaceship.LoadModelFileAndTexture(m_d3dDevice.Get(),	 m_wicFactory.Get(), "spaceship.obj", L"spaceship.png", 1.0f);
 m_spaceship.SetPosition(0.0f,0.0f,5.0f);
 m_spaceship.SetActive(true);

 // Load the bullet
 m_bullet.LoadModelFileAndTexture(m_d3dDevice.Get(), m_wicFactory.Get(), "bullet.obj", L"bullet.png", 0.09f);
 m_bullet.SetActive(false);
 
 // Load the background file
 m_bitmapbackground.CreateDeviceDependentResources(m_d2dContext,m_wicFactory.Get(), L"starfieldbackground.png");
 
	/*// Define the vertices with the CPU in system RAM  
	Vertex triangleVertices[] =   
	{   
		{ XMFLOAT3(-1.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f) },  
		{ XMFLOAT3(0.0f, 1.0f, 0.0f), XMFLOAT3(0.0f, 1.0f, 0.0f) },   
		{ XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f) }   
	};  

	// Create the model instance from the vertices: 
	m_model = new Model(m_d3dDevice.Get(), triangleVertices, 3 );*/

	// Read the spaceship model
	m_model = ModelReader::ReadModel(m_d3dDevice.Get(),"spaceship.obj");

	 // Read the texture:
 m_texture.ReadTexture(m_d3dDevice.Get(), m_wicFactory.Get(), L"spaceship.png ");
 

	// Create the constant buffer on the device  
	CD3D11_BUFFER_DESC constantBufferDesc(sizeof(ModelViewProjectionConstantBuffer), 
		D3D11_BIND_CONSTANT_BUFFER);  
	DX::ThrowIfFailed(m_d3dDevice->CreateBuffer(&constantBufferDesc, nullptr, &m_constantBufferGPU));

	// Load the shaders from files (note the CSO extension, nothlsl!):
	m_vertexShader.LoadFromFile(m_d3dDevice.Get(),"VertexShader.cso");
	m_pixelShader.LoadFromFile(m_d3dDevice.Get(), "PixelShader.cso");

	 // Create the sampler state
 D3D11_SAMPLER_DESC samplerDesc;
 ZeroMemory(&samplerDesc, sizeof(D3D11_SAMPLER_DESC));
 samplerDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
 samplerDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
 samplerDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
 samplerDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
 samplerDesc.MipLODBias = 0.0f;
 samplerDesc.MaxAnisotropy = 1;
 samplerDesc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
 samplerDesc.BorderColor[0] = 0;
 samplerDesc.BorderColor[1] = 0;
 samplerDesc.BorderColor[2] = 0;
 samplerDesc.BorderColor[3] = 0;
 samplerDesc.MinLOD = 0;
 samplerDesc.MaxLOD = D3D11_FLOAT32_MAX;

 DX::ThrowIfFailed(m_d3dDevice->CreateSamplerState 
  (&samplerDesc, &m_samplerState )); 

 
// Create the solid brush for the text 

  DX::ThrowIfFailed(m_d2dContext->CreateSolidColorBrush(ColorF(ColorF::Yellow),&m_scoreBrush));

}  

void SimpleTextRenderer::CreateWindowSizeDependentResources()
{ 
	DirectXBase::CreateWindowSizeDependentResources();

	
 m_bitmapbackground.CreateWindowSizeDependentResources(m_d2dContext);



	// Store the projection matrix  
	float aspectRatio = m_windowBounds.Width / m_windowBounds.Height;  
	float fovAngleY = 70.0f * XM_PI / 180.0f;  
	XMStoreFloat4x4(&m_constantBufferCPU.projection,   XMMatrixTranspose(XMMatrixPerspectiveFovRH   (fovAngleY,aspectRatio,0.01f,500.0f)));

}  

void SimpleTextRenderer::Update(float timeTotal, float timeDelta) 
{  
	(void) timeTotal; 	// Unused parameter.  
	(void) timeDelta; // Unused parameter.

	// View matrix defines where the camera is and what direction it looks in  
	XMStoreFloat4x4(&m_constantBufferCPU.view, XMMatrixTranspose(   
		XMMatrixLookAtRH(    
		XMVectorSet(0.0f, 10.0f, 0.01f, 0.0f),// Position    
	XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f),// Look at    
	XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f) // Up vector   
	)));

	 
// Accelerate player left and right when the keys are down
if(m_keyboard.IsKeyDown(Windows::System::VirtualKey::Left)) 
 m_spaceship.Accelerate(-2.0f * timeDelta, 0.0f, 0.0f, 0.25f); 
else if(m_keyboard.IsKeyDown(Windows::System::VirtualKey::Right))
 m_spaceship.Accelerate(2.0f * timeDelta, 0.0f, 0.0f, 0.25f); 


// Check if the ship hit the side of the screen:
if(m_spaceship.GetPosition().x < -10.0f && m_spaceship.GetSpeed().x <
0.0f)
 m_spaceship.ReverseDirection();
if(m_spaceship.GetPosition().x > 10.0f && m_spaceship.GetSpeed().x >
0.0f)
 m_spaceship.ReverseDirection();
 
// Move the spaceship
m_spaceship.Move();
// Store the ship's model buffer
XMStoreFloat4x4(&m_constantBufferCPU.model,
 XMMatrixTranspose(m_spaceship.GetTranslationMatrix()));

// Check if the player is shooting:
if( m_keyboard.IsKeyDown(Windows::System::VirtualKey::Up)) {
 // If the bullet's not active, fire it
 if(!m_bullet.IsActive()) {
  m_bullet.SetPosition(m_spaceship.GetPosition());
  m_bullet.SetSpeed(0.0f, 0.0f, -20.0f * timeDelta);
  m_bullet.SetActive(true);
  }
 }


// If the bullet's active, move it
if(m_bullet.IsActive()) {
 m_bullet.SetSpeed(0.0f, 0.0f, -20.0f * timeDelta);
 m_bullet.Move();
  
 // If the bullet goes out of the screen, deactivate it
 if(m_bullet.GetPosition().z < -10.0f)
  m_bullet.SetActive(false);
 }
 
// Move the baddies
for(int i = 0; i < 5; i++) {
 // Make the baddies bob up and down like real aliens
 m_baddies[i].SetYPosition(1.0f * sin(timeTotal*5 + i));

 if(m_baddies[i].GetSpeed().x == 0.0f) // Set the initial speed if the baddie is not moving
  m_baddies[i].SetSpeed(4.0f*timeDelta, 0.0f, 0.0f);
   
  // If they hit the side of the screen, reverse their direction
 if(m_baddies[i].GetSpeed().x < 0.0f &&
m_baddies[i].GetPosition().x < -10.0f)
  m_baddies[i].ReverseDirection();
 if(m_baddies[i].GetPosition().x > 10.0f && 
m_baddies[i].GetSpeed().x > 0.0f)
  m_baddies[i].ReverseDirection();

 // Move this baddie
 m_baddies[i].Move();

 // If the bullet hits a baddie, set it as inactive
 if(m_baddies[i].Overlapping(&m_bullet)) {
  m_baddies[i].SetActive(false);
  m_bullet.SetActive(false);
  m_playerScore += 100;
  }
}


	// Position the triangle model
	XMStoreFloat4x4(&m_constantBufferCPU.model,
		XMMatrixTranspose(
		XMMatrixTranslation(0.0f, 0.0f, 0.0f)));

}  
	
/*void SimpleTextRenderer::Render() 
{ 
		m_d3dContext->ClearRenderTargetView(m_d3dRenderTargetView.Get(),   (float*) &XMFLOAT3(0.39f, 0.58f, 0.93f)); // Clear to cornflower blue

		m_d2dContext->BeginDraw();  
		//m_d2dContext->Clear(ColorF(ColorF::CornflowerBlue)); // 2D Clear

 // Clear the depth stencil
 m_d3dContext->ClearDepthStencilView(m_d3dDepthStencilView.Get(),D3D11_CLEAR_DEPTH, 1.0f, 0);

 // Set the render target
 m_d3dContext->OMSetRenderTargets(1,m_d3dRenderTargetView.GetAddressOf(), m_d3dDepthStencilView.Get());

 // Set to render triangles
 UINT stride = sizeof(Vertex); // Reset to the frist verticesin the buffer
 UINT offset = 0;
 m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

 // Set the input layout
 m_d3dContext->IASetInputLayout(m_vertexShader.GetInputLayout());

 // Set the vertex shader
 m_d3dContext->VSSetShader(m_vertexShader.GetVertexShader(),nullptr, 0);

 // Set the sampler state for the pixel shader
 m_d3dContext->PSSetSamplers(0, 1, &m_samplerState);
 
 // Set the resource view which points to the texture
 m_d3dContext->PSSetShaderResources(0, 1,m_texture.GetResourceView().GetAddressOf());


 // Set the vertex shader's constant buffer
 m_d3dContext->VSSetConstantBuffers(0, 1, m_constantBufferGPU.GetAddressOf());

 // Set the pixel shader
 m_d3dContext->PSSetShader(m_pixelShader.GetPixelShader(),
nullptr, 0);

 // Load the data from the CPU into the GPU's constant buffer
 m_d3dContext->UpdateSubresource(m_constantBufferGPU.Get(), 0,NULL, &m_constantBufferCPU, 0, 0);
  
 // Set the vertex buffer
 m_d3dContext->IASetVertexBuffers(0, 1, m_model->GetAddressOfVertexBuffer(),&stride, &offset);

 // Render the vertices
 m_d3dContext->Draw(m_model->GetVertexCount(), 0);

	// Ignore D2DERR_RECREATE_TARGET. This error indicates that the device 
	// is lost. It will be handled during the next call to Present.

	HRESULT hr = m_d2dContext->EndDraw();  
	if (hr != D2DERR_RECREATE_TARGET)  
	{   DX::ThrowIfFailed(hr);  
	} 

}*/


void SimpleTextRenderer::Render()

{
 m_d3dContext->ClearRenderTargetView(m_d3dRenderTargetView.Get(), (float*) &XMFLOAT3(0.39f, 0.58f, 0.93f)); // Clear to cornflower blue
 
 // Render 2-D background so it appears behind everything
 m_d2dContext->BeginDraw();
 m_bitmapbackground.Render(m_d2dContext);

 HRESULT hr = m_d2dContext->EndDraw();
 if (hr != D2DERR_RECREATE_TARGET) DX::ThrowIfFailed(hr);
  
 // Clear the depth stencil
 m_d3dContext->ClearDepthStencilView(m_d3dDepthStencilView.Get(),D3D11_CLEAR_DEPTH, 1.0f, 0);

 // Set the render target 
 m_d3dContext->OMSetRenderTargets(1,m_d3dRenderTargetView.GetAddressOf(), m_d3dDepthStencilView.Get());// Set to render a triangle list
 m_d3dContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

//Set the input layout
 m_d3dContext->IASetInputLayout(m_vertexShader.GetInputLayout());
//Set the vertex shader
 m_d3dContext->VSSetShader(m_vertexShader.GetVertexShader(),nullptr,0);

//Set the vertex shader's constant buffer
 m_d3dContext->VSSetConstantBuffers(0,1,m_constantBufferGPU.GetAddressOf());

//Set the pixel shader
 m_d3dContext->PSSetShader(m_pixelShader.GetPixelShader(),nullptr,0);

 //Set the sampler state for the pixel shader
 m_d3dContext->PSSetSamplers(0,1, &m_samplerState);

//Load the data from the CPU into the GPU's constant buffer
m_d3dContext->UpdateSubresource(m_constantBufferGPU.Get(),0,NULL,&m_constantBufferCPU, 0, 0);

 // Render the spaceship
 m_spaceship.Render(m_d3dContext.Get());

 // Render the baddies
 for(int i = 0; i < 5; i++) {
  XMStoreFloat4x4(&m_constantBufferCPU.model,
   XMMatrixTranspose(
    m_baddies[i].GetTranslationMatrix()
    ));
  m_d3dContext->UpdateSubresource(m_constantBufferGPU.Get(),0, NULL, &m_constantBufferCPU, 0, 0);
  m_baddies[i].Render(m_d3dContext.Get());
  }

 // Render the bullet
   XMStoreFloat4x4(&m_constantBufferCPU.model,
  XMMatrixTranspose(
   m_bullet.GetTranslationMatrix()
   ));
 m_d3dContext->UpdateSubresource(m_constantBufferGPU.Get(), 0,NULL, &m_constantBufferCPU, 0, 0);
 m_bullet.Render(m_d3dContext.Get());
 
 // Render 2-D background so it appears behind everything
 m_d2dContext->BeginDraw();

 // Print the player's score:
 m_d2dContext->SetTransform(m_orientationTransform2D);
 // Set up the string to print:
 std::wstring s = std::wstring( L"Score: ") + std::to_wstring(m_playerScore);
 // Render the string in the top left corner
 m_d2dContext->DrawText(s.c_str(), s.length(), m_textFormat.Get(), D2D1::RectF(0, 0, 600, 32), m_scoreBrush.Get());

 hr = m_d2dContext->EndDraw();
 if (hr != D2DERR_RECREATE_TARGET) DX::ThrowIfFailed(hr); 

} 


void SimpleTextRenderer::KeyDown(Windows::System::VirtualKey key)
{
m_keyboard.KeyDown(key);
}

void SimpleTextRenderer::KeyUp(Windows::System::VirtualKey key) {
m_keyboard.KeyUp(key); 
} 