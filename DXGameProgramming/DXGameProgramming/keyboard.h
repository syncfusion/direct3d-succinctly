// Keyboard.h
#pragma once
// This class records the keystates
class Keyboard
{
private:
 bool m_keystates[256];

public:
 // Public constructor
 Keyboard();

 // Set all keys to up
 void Reset();

 // Register keydown event
 void KeyDown(Windows::System::VirtualKey key);
 
 // Register keyup event
 void KeyUp(Windows::System::VirtualKey key);
 
 // Query a keystate
 bool IsKeyDown(Windows::System::VirtualKey key);
}; 
 
