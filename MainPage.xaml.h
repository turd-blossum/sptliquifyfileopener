﻿//
// MainPage.xaml.h
// Declaration of the MainPage class.
//

#pragma once

#include "MainPage.g.h"

namespace BlankAppUniversalWindowsApplication
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	public ref class MainPage sealed
	{
	public:
		MainPage();

	private:
		void Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void updatebutton2(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
