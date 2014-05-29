// Keyboard.cpp
#include "pch.h"
#include "Keyboard.h"
Keyboard::Keyboard()

{
	Reset();
}
 
void Keyboard::Reset(){
for(int i = 0; i < 256; i++) m_keystates[i] = false; 
}

void Keyboard::KeyDown(Windows::System::VirtualKey key){
m_keystates[(unsigned char) key] = true;
}

void Keyboard::KeyUp(Windows::System::VirtualKey key){
m_keystates[(unsigned char) key] = false;
}

bool Keyboard::IsKeyDown(Windows::System::VirtualKey key){
return m_keystates[(unsigned char) key];
} 