// // DirectXPage.xaml.cpp // Implementation of the DirectXPage.xaml class. //  
#include "pch.h"
#include "DirectXPage.xaml.h"  
using namespace DXGameProgramming;  
using namespace Platform; 
using namespace Windows::Foundation; 
using namespace Windows::Foundation::Collections; 
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Input; 
using namespace Windows::UI::Core;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;  

DirectXPage::DirectXPage()
{ 
	InitializeComponent();  
	 m_renderer = ref new SimpleTextRenderer();  
	m_renderer->Initialize(   Window::Current->CoreWindow,   SwapChainPanel,   DisplayProperties::LogicalDpi   );  

	Window::Current->CoreWindow->SizeChanged +=    ref new TypedEventHandler<CoreWindow^, WindowSizeChangedEventArgs^>(this, &DirectXPage::OnWindowSizeChanged);  

	DisplayProperties::LogicalDpiChanged +=   ref new DisplayPropertiesEventHandler(this, &DirectXPage::OnLogicalDpiChanged);  

	DisplayProperties::OrientationChanged +=         ref new DisplayPropertiesEventHandler(this, &DirectXPage::OnOrientationChanged);  

	DisplayProperties::DisplayContentsInvalidated +=   ref new DisplayPropertiesEventHandler(this, &DirectXPage::OnDisplayContentsInvalidated);    m_eventToken = CompositionTarget::Rendering::add(ref new EventHandler<Object^>(this, &DirectXPage::OnRendering));  

	m_timer = ref new BasicTimer(); 

	// Attach the keyboard events
	this->KeyUp += ref new KeyEventHandler(this,  &DirectXPage::OnKeyUp);
	this->KeyDown += ref new KeyEventHandler(this,  &DirectXPage::OnKeyDown);

}

void DirectXPage::OnPointerMoved(Object^ sender, PointerRoutedEventArgs^ args) { }  

void DirectXPage::OnPointerReleased(Object^ sender, PointerRoutedEventArgs^ args) { } 

void DirectXPage::OnWindowSizeChanged(CoreWindow^ sender, WindowSizeChangedEventArgs^ args) {  m_renderer->UpdateForWindowSizeChange(); }  

void DirectXPage::OnLogicalDpiChanged(Object^ sender) {  m_renderer->SetDpi(DisplayProperties::LogicalDpi); }  

void DirectXPage::OnOrientationChanged(Object^ sender) {  m_renderer->UpdateForWindowSizeChange(); }  

void DirectXPage::OnDisplayContentsInvalidated(Object^ sender) {  m_renderer->ValidateDevice(); }  

void DirectXPage::OnRendering(Object^ sender, Object^ args) {  
	m_timer->Update();
	m_renderer->Update(m_timer->Total, m_timer->Delta); 
	m_renderer->Render();
	m_renderer->Present(); 
} 

void DirectXPage::OnKeyDown(Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e) {
m_renderer->KeyDown(e->Key);
}

void DirectXPage::OnKeyUp(Object^ sender, Windows::UI::Xaml::Input::KeyRoutedEventArgs^ e) {
m_renderer->KeyUp(e->Key ); 
}

void DirectXPage::OnDownButtonDown(Platform::Object^ sender,Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e) {
 m_renderer->KeyDown(Windows::System::VirtualKey::Down);
 }

void DXGameProgramming::DirectXPage::OnDownButtonPointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if(e->Pointer->PointerDeviceType ==Windows::Devices::Input::PointerDeviceType::Touch)
		m_renderer->KeyDown(Windows::System::VirtualKey::Down);
}

void DXGameProgramming::DirectXPage::OnDownButtonUp(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	m_renderer->KeyUp(Windows::System::VirtualKey::Down);
}

void DXGameProgramming::DirectXPage::OnRightButtonDown(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	m_renderer->KeyDown(Windows::System::VirtualKey::Right);
}

void DXGameProgramming::DirectXPage::OnRightButtonPointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if(e->Pointer->PointerDeviceType ==Windows::Devices::Input::PointerDeviceType::Touch)
		m_renderer->KeyDown(Windows::System::VirtualKey::Right);
}

void DXGameProgramming::DirectXPage::OnRightButtonUp(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	m_renderer->KeyUp(Windows::System::VirtualKey::Right);
}

void DXGameProgramming::DirectXPage::OnUpButtonDown(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	m_renderer->KeyDown(Windows::System::VirtualKey::Up);
}

void DXGameProgramming::DirectXPage::OnUpButtonPointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	if(e->Pointer->PointerDeviceType ==Windows::Devices::Input::PointerDeviceType::Touch)
		m_renderer->KeyDown(Windows::System::VirtualKey::Up);
}

void DXGameProgramming::DirectXPage::OnUpButtonUp(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	m_renderer->KeyUp(Windows::System::VirtualKey::Up);
}

void DXGameProgramming::DirectXPage::OnLeftButtonDown(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	m_renderer->KeyDown(Windows::System::VirtualKey::Left);
}

void DXGameProgramming::DirectXPage::OnLeftButtonPointerEntered(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
		if(e->Pointer->PointerDeviceType ==Windows::Devices::Input::PointerDeviceType::Touch)
			 m_renderer->KeyDown(Windows::System::VirtualKey::Left);
}

void DXGameProgramming::DirectXPage::OnLeftButtonUp(Platform::Object^ sender, Windows::UI::Xaml::Input::PointerRoutedEventArgs^ e)
{
	m_renderer->KeyUp(Windows::System::VirtualKey::Left);
}
