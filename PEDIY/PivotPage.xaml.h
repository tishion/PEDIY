//
// PivotPage.xaml.h
// Declaration of the PivotPage class.
//

#pragma once

#include "PivotPage.g.h"
#include <mutex>

namespace PEDIY
{
	public ref class PivotPage sealed
	{
		Platform::String^ GetHomePageDataName() const
		{
			return ref new Platform::String(L"HomePageData");
		}

		Platform::String^ GetProfilePageDataName() const
		{
			return ref new Platform::String(L"ProfilePageData");
		}

	public:
		PivotPage();
		virtual ~PivotPage();

		/// <summary>
		/// Gets the <see cref="NavigationHelper"/> associated with this <see cref="Page"/>.
		/// </summary>
		property Common::NavigationHelper^ NavigationHelper
		{
			Common::NavigationHelper^ get();
		}

		/// <summary>
		/// Gets the view model for this <see cref="Page"/>.
		/// This can be changed to a strongly typed view model.
		/// </summary>
		property Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^ DefaultViewModel
		{
			Windows::Foundation::Collections::IObservableMap<Platform::String^, Platform::Object^>^  get();
		}

	protected:
		virtual void OnNavigatedTo(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;
		virtual void OnNavigatedFrom(Windows::UI::Xaml::Navigation::NavigationEventArgs^ e) override;

	private:
		static Windows::UI::Xaml::DependencyProperty^	_defaultViewModelProperty;
		static Windows::UI::Xaml::DependencyProperty^	_navigationHelperProperty;

		Windows::ApplicationModel::Resources::ResourceLoader^ _resourceLoader;


		void NavigationHelper_LoadState(Platform::Object^ sender, Common::LoadStateEventArgs^ e);
		void NavigationHelper_SaveState(Platform::Object^ sender, Common::SaveStateEventArgs^ e);

		void PivotItemHome_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void PivotItemProfile_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);

		void ItemView_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);
		void ForumListView_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e);

		void BottomCmdBar_Refresh_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void BottomCmdBar_About_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
