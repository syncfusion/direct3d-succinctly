// GameObject.h
#pragma once

#include "pch.h"
#include "Model.h"
#include "ModelReader.h"
#include "Texture.h"

using namespace DirectX;

class GameObject {
 XMFLOAT3 m_objectPosition; // Object's position
 XMFLOAT3 m_objectMovement; // Object's movement
 Model *m_model; // Object's model
 Texture m_texture; // Object's texture
 float m_objectSize; // Object's size in units
 bool m_isActive; // Is the object active?

public:
 GameObject();

 // For use when multiple objects use the sme texture and model
 void SetModelAndTexture(Model* model, Texture* texture)
  {
  m_model = model;
  m_texture = *texture;
  }

 void SetObjectSize(float size) { this->m_objectSize = size; }

 void SetActive( bool active) { m_isActive = active; }
 
 bool IsActive() { return m_isActive; } 

 

 

 void LoadModelFileAndTexture(ID3D11Device* device,
  IWICImagingFactory2* wicFactory, char* modelFilename,
  LPCWSTR texturefilename, float objectSize);

 XMMATRIX GetTranslationMatrix() {
  return XMMatrixTranslation(m_objectPosition.x,
   m_objectPosition.y, m_objectPosition.z);
  }

 // Reverse the direction of the object's movement
 void ReverseDirection() {
  m_objectMovement.x = -m_objectMovement.x;
  m_objectMovement.y = -m_objectMovement.y;
  m_objectMovement.z = -m_objectMovement.z;
  }

 void SetPosition(float x, float y, float z) {
  m_objectPosition.x = x;
  m_objectPosition.y = y;
  m_objectPosition.z = z;
  }

 XMFLOAT3 GetPosition() { return m_objectPosition; }

 XMFLOAT3 GetSpeed() { return m_objectMovement; }

 void SetSpeed(float x, float y, float z) {
  m_objectMovement.x = x; m_objectMovement.y = y;
  m_objectMovement.z = z; }

 void SetPosition(XMFLOAT3 pos) { m_objectPosition = pos; }

 void SetYPosition(float y) { m_objectPosition.y = y; }

 void Move();

 void Accelerate(float amountX, float amountY, float amountZ,
float max);

 void Render(ID3D11DeviceContext1* context);

 bool Overlapping(GameObject *obj);
}; 

 


