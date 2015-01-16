#pragma once

using namespace Platform;

namespace PEDIY
{
	//
	public ref class WebViewDocument sealed :
		Windows::UI::Xaml::DependencyObject
	{
	public:
		WebViewDocument(void)
		{
		};

		static property Windows::UI::Xaml::DependencyProperty^ HtmlSourceProperty 
		{
			Windows::UI::Xaml::DependencyProperty^ get() 
			{ 
				return _HtmlSourceProperty; 
			}
		}

		static Platform::String^ WebViewDocument::GetHtmlSource(Windows::UI::Xaml::Controls::WebView^ webView)
		{
			return (Platform::String^)(webView->GetValue(HtmlSourceProperty));
		}

		static void WebViewDocument::SetHtmlSource(Windows::UI::Xaml::Controls::WebView^ webView, Platform::String^ value)
		{
			webView->SetValue(HtmlSourceProperty, value);
		}

	private:

		static Windows::UI::Xaml::DependencyProperty^ _HtmlSourceProperty;
		static void OnHtmlSourceChanged(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ e);
	};


	//
	public ref class StatusBarProgressIndicatorControllor sealed :
		Windows::UI::Xaml::DependencyObject
	{
	public:
		StatusBarProgressIndicatorControllor(void)
		{
		};

		static property 
			Windows::UI::Xaml::DependencyProperty^ RunProperty
		{
			Windows::UI::Xaml::DependencyProperty^ get()
			{
				return _RunProperty;
			}
		}

		static Platform::String^ 
			StatusBarProgressIndicatorControllor::GetRun(
			Windows::UI::Xaml::Controls::UserControl^ obj)
		{
			return (Platform::String^)(obj->GetValue(RunProperty));
		}

		static void 
			StatusBarProgressIndicatorControllor::SetRun(
			Windows::UI::Xaml::Controls::UserControl^ obj, Platform::String^ value)
		{
			obj->SetValue(RunProperty, value);
		}

	private:

		static Windows::UI::Xaml::DependencyProperty^ _RunProperty;
		static void OnRunChanged(Windows::UI::Xaml::DependencyObject^ obj, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ e);
	};
}