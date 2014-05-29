// Texture.cpp.cpp

#include "pch.h"
#include "Texture.h"

void Texture::ReadTexture(ID3D11Device* device, IWICImagingFactory2* wicFactory, LPCWSTR filename)
{
// Create a WIC decoder from the file
IWICBitmapDecoder *pDecoder; 

DX::ThrowIfFailed(wicFactory->CreateDecoderFromFilename(filename,
 nullptr, GENERIC_READ, WICDecodeMetadataCacheOnDemand,
&pDecoder));

// Create a frame, this will always be 0, PNG have only 1 frame
IWICBitmapFrameDecode *pFrame = nullptr;
DX::ThrowIfFailed(pDecoder->GetFrame(0, &pFrame));

// Convert the format to ensure it's 32bpp RGBA
IWICFormatConverter *m_pConvertedSourceBitmap;
DX::ThrowIfFailed(wicFactory->CreateFormatConverter(&m_pConvertedSourceBitmap));

DX::ThrowIfFailed(m_pConvertedSourceBitmap->Initialize(
pFrame, GUID_WICPixelFormat32bppPRGBA, // Pre-multiplied RGBA
 WICBitmapDitherTypeNone, nullptr,
 0.0f, WICBitmapPaletteTypeCustom));

// Create a texture2D from the decoded pixel data
UINT width = 0;
UINT height = 0;
m_pConvertedSourceBitmap->GetSize(&width, &height);
int totalBytes = width * height * 4; // Total bytes in the pixel data

// Set up a rectangle which represents the size of the entire image:
WICRect rect; 
rect.X = 0; rect.Y = 0; rect.Width = width; rect.Height = height;

// Copy the entire decoded bitmap image to a buffer of bytes:
BYTE *buffer = new BYTE[totalBytes];
DX::ThrowIfFailed(m_pConvertedSourceBitmap->CopyPixels(&rect, width *
4, totalBytes, buffer));

// Describe the texture we will create:
D3D11_TEXTURE2D_DESC desc;
ZeroMemory(&desc, sizeof(D3D11_TEXTURE2D_DESC));
desc.Width = width;
desc.Height = height;
desc.MipLevels = 1;
desc.ArraySize = 1;
desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
desc.SampleDesc.Count = 1;
desc.SampleDesc.Quality = 0;
desc.Usage = D3D11_USAGE_IMMUTABLE;
desc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
desc.CPUAccessFlags = 0;
desc.MiscFlags = 0;

// Create the sub resource data which points to our BYTE *buffer
D3D11_SUBRESOURCE_DATA subresourceData;
ZeroMemory(&subresourceData, sizeof(D3D11_SUBRESOURCE_DATA));
subresourceData.pSysMem = buffer;
subresourceData.SysMemPitch = (width * 4);
subresourceData.SysMemSlicePitch = (width * height * 4);

// Create the texture2d
DX::ThrowIfFailed(device->CreateTexture2D(&desc, &subresourceData,
m_texture.GetAddressOf()));

// Create a resource view for the texture:
D3D11_SHADER_RESOURCE_VIEW_DESC rvDesc;
rvDesc.Format = desc.Format; // Use format from the texture
rvDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D; // Resource is a 2D texture
rvDesc.Texture2D.MostDetailedMip = 0;
rvDesc.Texture2D.MipLevels = 1;

// Create resource view:
DX::ThrowIfFailed(device->CreateShaderResourceView(
 m_texture.Get(), &rvDesc,
 m_resourceView.GetAddressOf()));

// Delete the WIC decoder
pDecoder->Release();
pFrame->Release();
m_pConvertedSourceBitmap->Release();

// Delete the pixel buffer
delete[] buffer;

}