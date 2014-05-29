// GameObject.cpp 

#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
{
m_objectPosition = XMFLOAT3(0.0f, 0.0f, 0.0f);
m_objectMovement = XMFLOAT3(0.0f, 0.0f, 0.0f);
}

void GameObject::LoadModelFileAndTexture(ID3D11Device* device,
IWICImagingFactory2* wicFactory, char* modelFilename, LPCWSTR
texturefilename, float objectSize)
{
// Read the spaceship model
m_model = ModelReader::ReadModel(device, modelFilename);

// Read the texture:
m_texture.ReadTexture(device, wicFactory, texturefilename);

// Record the radius of the the object's bounding sphere
m_objectSize = objectSize;
}

void GameObject::Render(ID3D11DeviceContext1* context)
{
 if(!m_isActive) return; // If the object's not active, return 
 // Set to render triangles
 UINT stride = sizeof(Vertex); // Reset to the frist vertices in the buffer
 UINT offset = 0;
 // Set the vertex buffer
 context->IASetVertexBuffers(0, 1, m_model->GetAddressOfVertexBuffer(), &stride, &offset);



// Set the resource view which points to the texture
 context->PSSetShaderResources(0, 1,
m_texture.GetResourceView().GetAddressOf());
 // Render the vertices
 context->Draw(m_model->GetVertexCount(), 0);
} 


void GameObject::Move()
{
m_objectPosition.x += m_objectMovement.x;
m_objectPosition.y += m_objectMovement.y;
m_objectPosition.z += m_objectMovement.z;
}

void GameObject::Accelerate(float amountX, float amountY, float
amountZ, float max)
{
m_objectMovement.x += amountX;
m_objectMovement.y += amountY;
m_objectMovement.z += amountZ;

if(m_objectMovement.x > max) m_objectMovement.x = max;
if(m_objectMovement.y > max) m_objectMovement.y = max;
if(m_objectMovement.z > max) m_objectMovement.z = max;
if(m_objectMovement.x < -max) m_objectMovement.x = -max;
if(m_objectMovement.y < -max) m_objectMovement.y = -max;
if(m_objectMovement.z < -max) m_objectMovement.z = -max;
}

bool GameObject::Overlapping(GameObject *obj)
{
// If either of the two objects are not active, return false
if(!m_isActive) return false;
if(!obj->m_isActive) return false;

// Find distance in each axis
float distX = m_objectPosition.x - obj->m_objectPosition.x;
float distY = m_objectPosition.y - obj->m_objectPosition.y;
float distZ = m_objectPosition.z - obj->m_objectPosition.z;

// Find total distance from axis distances
float dist = sqrt(distX*distX + distY*distY + distZ * distZ);

// The models overlap if theie distance is less or equal
// to either of the object's sizes
return dist <= (m_objectSize + obj->m_objectSize);
} 