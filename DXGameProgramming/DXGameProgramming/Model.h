// Model.h 
#pragma once

#include "pch.h"  

// Constant buffer which will hold the matrices
struct ModelViewProjectionConstantBuffer 
{  
	DirectX::XMFLOAT4X4 model;  
	DirectX::XMFLOAT4X4 view;  
	DirectX::XMFLOAT4X4 projection; 
};  

// Definition of our vertex types
struct Vertex 
{  
	DirectX::XMFLOAT3 position; 
	//DirectX::XMFLOAT3 color; 
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT2 uv; 
};  

class Model 
{  
	// GPU buffer which will hold the vertices 
	Microsoft::WRL::ComPtr<ID3D11Buffer> m_vertexBuffer;

	// Record of the vertex count 
	uint32 m_vertexCount; 

	public: 
		// Constructor creates the vertices for the model  
		Model(ID3D11Device* device, Vertex* vertices, int vertexCount);    
		
		// Getters  
		ID3D11Buffer** GetAddressOfVertexBuffer() { return m_vertexBuffer.GetAddressOf(); } 
		uint32 GetVertexCount() 
		{ 
			return m_vertexCount; 
		} 
};