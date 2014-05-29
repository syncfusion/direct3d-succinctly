// Model.cpp 

#include "pch.h"
#include "Model.h"  


Model::Model(ID3D11Device* device, Vertex* vertices, int vertexCount)
{
	// Save the vertex count 
	this->m_vertexCount = vertexCount;  

	// Create a subresource which points to the data to be copied 
	D3D11_SUBRESOURCE_DATA vertexBufferData = {0}; 
	vertexBufferData.pSysMem = vertices; 
	vertexBufferData.SysMemPitch = sizeof(Vertex); 
	vertexBufferData.SysMemSlicePitch = 0; 

	// Create a description of the buffer we're making on the GPU 
	CD3D11_BUFFER_DESC vertexBufferDesc(sizeof(Vertex)*vertexCount, D3D11_BIND_VERTEX_BUFFER); 

	// Copy the data from *vertices in system RAM to the GPU RAM: 
	DX::ThrowIfFailed(device->CreateBuffer(&vertexBufferDesc, &vertexBufferData, &m_vertexBuffer));

} 