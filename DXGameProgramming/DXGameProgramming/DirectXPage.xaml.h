// 
// BlankPage.xaml.h
// Declaration of the BlankPage.xaml class. 
//  

#pragma once

#include "DirectXPage.g.h" 
#include "SimpleTextRenderer.h" 
#include "BasicTimer.h"  

namespace DXGameProgramming {  
	/// <summary>  
	/// A DirectX page that can be used on its own.  Note that it may not be used within a Frame. 
	/// </summary>     
	[Windows::Foundation::Metadata::WebHostHidden]  
	public ref class DirectXPage sealed  
	{  
	public:   DirectXPage();  
	private:   void OnPointerMoved(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);   
			   void OnPointerReleased(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ args);   
			   void OnWindowSizeChanged(Windows::UI::Core::CoreWindow^ sender, Windows::UI::Core::WindowSizeChangedEventArgs^ args);   
			   void OnLogicalDpiChanged(Platform::Object^ sender);  
			   void OnOrientationChanged(Platform::Object^ sender);  
			   void OnDisplayContentsInvalidated(Platform::Object^ sender);
			   void OnRendering(Object^ sender, Object^ args);  

			   // Keyboard events
	void OnKeyDown(Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);
	void OnKeyUp(Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e);

  Windows::Foundation::EventRegistrationToken m_eventToken;  
  SimpleTextRenderer^ m_renderer;     
  BasicTimer^ m_timer;  
  void OnDownButtonDown(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnDownButtonPointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnDownButtonUp(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnRightButtonDown(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnRightButtonPointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnRightButtonUp(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnUpButtonDown(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnUpButtonPointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnUpButtonUp(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnLeftButtonDown(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnLeftButtonPointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
  void OnLeftButtonUp(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e);
	}; 
} 