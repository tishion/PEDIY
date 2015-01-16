#include "pch.h"

using namespace PEDIY;

using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Resources::Core;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml; 
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Storage;
using namespace Windows::Data::Json;
using namespace Windows::Data::Html;
using namespace Windows::Web::Http;


//////////////////////////////////////////////////////////////////////////
DependencyProperty^ PEDIY::WebViewDocument::_HtmlSourceProperty =
DependencyProperty::RegisterAttached("HtmlSource", 
TypeName(String::typeid), TypeName(WebViewDocument::typeid),
ref new PropertyMetadata(nullptr, ref new PropertyChangedCallback(OnHtmlSourceChanged)));


void PEDIY::WebViewDocument::OnHtmlSourceChanged(DependencyObject^ obj, DependencyPropertyChangedEventArgs^ e)
{
	WebView^ webView = safe_cast<WebView^>(obj);
	String^ value = safe_cast<String^>(e->NewValue);

	webView->NavigateToString(value);
}

//////////////////////////////////////////////////////////////////////////
DependencyProperty^ PEDIY::StatusBarProgressIndicatorControllor::_RunProperty =
DependencyProperty::RegisterAttached("Run",
TypeName(double::typeid), TypeName(StatusBarProgressIndicatorControllor::typeid),
ref new PropertyMetadata(nullptr, ref new PropertyChangedCallback(OnRunChanged)));

void PEDIY::StatusBarProgressIndicatorControllor::OnRunChanged(
	Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ e)
{
	double value = safe_cast<double>(e->NewValue);
	if (value)
	{
		StatusBar::GetForCurrentView()->ProgressIndicator->ProgressValue = (double)(0);
	}
	else
	{
		StatusBar::GetForCurrentView()->ProgressIndicator->ProgressValue = nullptr;
	}
}
