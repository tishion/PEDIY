//
// PostListPage.xaml.h
// Declaration of the PostListPage class
//

#pragma once

#include "PostListPage.g.h"
#include "Common\NavigationHelper.h"

namespace PEDIY
{
	[Windows::UI::Xaml::Data::Bindable]
	public ref class HTMLData sealed :
		Windows::UI::Xaml::Data::ICustomPropertyProvider
	{
	public:
		HTMLData() {}
		HTMLData(Platform::String^ _Name, Platform::String^ _HTML)
		{
			Name = _Name;
			HTML = _HTML;
		}

		property Platform::String^ Name
		{
			Platform::String^ get() { return _Name; }
			void set(Platform::String^ _value) { _Name = _value; }
		}

		property Platform::String^ HTML
		{
			Platform::String^ get() { return _HTML; }
			void set(Platform::String^ _value) { _HTML = _value; }
		}

		virtual Windows::UI::Xaml::Data::ICustomProperty^ GetCustomProperty(Platform::String^ name) { return nullptr; }
		virtual Windows::UI::Xaml::Data::ICustomProperty^ GetIndexedProperty(Platform::String^ name, Windows::UI::Xaml::Interop::TypeName type) { return nullptr; }
		virtual Platform::String^ GetStringRepresentation() { return Name; }


		property Windows::UI::Xaml::Interop::TypeName Type
		{
			virtual Windows::UI::Xaml::Interop::TypeName get() { return this->GetType(); }
		}

	private:
		Platform::String^ _Name;
		Platform::String^ _HTML;
	};

	/// <summary>
	/// A basic page that provides characteristics common to most applications.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class PostListPage sealed
	{
		Platform::String^ GetPostListDataName() const
		{
			return ref new Platform::String(L"PostListData");
		}

	public:
		PostListPage();
		virtual ~PostListPage();
		/// <summary>
		/// Gets the view model for this <see cref="Page"/>. 
		/// This can be changed to a strongly typed view model.
		/// </summary>
		property Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^ DefaultViewModel
		{
			Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^  get();
		}

		/// <summary>
		/// Gets the <see cref="NavigationHelper"/> associated with this <see cref="Page"/>.
		/// </summary>
		property Common::NavigationHelper^ NavigationHelper
		{
			Common::NavigationHelper^ get();
		}



	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		void LoadState(Platform::Object^ sender, Common::LoadStateEventArgs^ e);
		void SaveState(Platform::Object^ sender, Common::SaveStateEventArgs^ e);

		static Windows::UI::Xaml::DependencyProperty^ _defaultViewModelProperty;
		static Windows::UI::Xaml::DependencyProperty^ _navigationHelperProperty;

		Windows::ApplicationModel::Resources::ResourceLoader^ _resourceLoader;

		void BottomAppBar_FirstPageButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void BottomAppBar_PageUpButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void BottomAppBar_PageDownButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void BottomAppBar_LastPageButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};

}
