// // App.xaml.h // Declaration of the App class. //  
#pragma once  
#include "App.g.h"
#include "DirectXPage.xaml.h"  
namespace DXGameProgramming 
{  
	/// <summary>  
	/// Provides application-specific behavior to supplement the default
	/// Application class.
	/// </summary>  
	ref class App sealed 
	{  
	public:  
		App();   
		virtual void OnLaunched(Windows::ApplicationModel::Activation::LaunchActivatedEventArgs^ args) override;  
	private:   
	 DirectXPage^ m_directXPage; 
	};
} 