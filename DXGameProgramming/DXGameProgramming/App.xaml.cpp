﻿// // App.xaml.cpp // Implementation of the App class. //  
#include "pch.h" 
#include "DirectXPage.xaml.h" 

using namespace DXGameProgramming;  

using namespace Platform; 
using namespace Windows::ApplicationModel; 
using namespace Windows::ApplicationModel::Activation; 
using namespace Windows::Foundation; 
using namespace Windows::Foundation::Collections; 
using namespace Windows::Storage; 
using namespace Windows::UI::Xaml; 
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;  

/// <summary> /// Initializes the singleton application object.  This is the first line of authored code /// executed, and as such is the logical equivalent of main() or WinMain(). /// </summary>
App::App() 
{  InitializeComponent(); 
}  
/// <summary> /// Invoked when the application is launched normally by the end user.  Other entry points /// will be used when the application is launched to open a specific file, to display /// search results, and so forth. /// </summary> /// <param name="args">Details about the launch request and process.</param> 
void App::OnLaunched(LaunchActivatedEventArgs^ args) 
{  m_directXPage = ref new DirectXPage();  
 // Place the page in the current window and ensure that it is active.  
Window::Current->Content = m_directXPage;  
Window::Current->Activate();
}