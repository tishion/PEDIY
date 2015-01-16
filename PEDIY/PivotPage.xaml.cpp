//
// PivotPage.xaml.cpp
// Implementation of the PivotPage class.
//

#include "pch.h"
#include "PivotPage.xaml.h"
#include "ItemPage.xaml.h"

using namespace PEDIY;
using namespace PEDIY::Common;
using namespace PEDIY::Data;

using namespace concurrency;
using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Resources;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Pivot Application template is documented at http://go.microsoft.com/fwlink/?LinkID=391641
DependencyProperty^ PivotPage::_defaultViewModelProperty = DependencyProperty::Register(
	"DefaultViewModel",
	IObservableMap<String^, Object^>::typeid,
	PivotPage::typeid,
	nullptr);

DependencyProperty^ PivotPage::_navigationHelperProperty = DependencyProperty::Register(
	"NavigationHelper",
	NavigationHelper::typeid,
	PivotPage::typeid,
	nullptr);

PivotPage::PivotPage()
{
	InitializeComponent();

	NavigationCacheMode = Navigation::NavigationCacheMode::Enabled;

	_resourceLoader = ResourceLoader::GetForCurrentView(L"Resources");

	auto defaultViewModel = ref new Platform::Collections::Map<String^, Object^>(std::less<String^>());
	SetValue(_defaultViewModelProperty, defaultViewModel);

	RelayCommand^ goBackCommand = ref new RelayCommand(
		[this](Object^) -> bool
	{
		return true;
	},
		[this](Object^) -> void
	{
		Application::Current->Exit();
	}
	);

	auto navigationHelper = ref new Common::NavigationHelper(this, goBackCommand);
	navigationHelper->LoadState += ref new LoadStateEventHandler(this, &PivotPage::NavigationHelper_LoadState);
	navigationHelper->SaveState += ref new SaveStateEventHandler(this, &PivotPage::NavigationHelper_SaveState);
	SetValue(_navigationHelperProperty, navigationHelper);
}

PEDIY::PivotPage::~PivotPage()
{

}

IObservableMap<String^, Object^>^ PivotPage::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

NavigationHelper^ PivotPage::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

void PivotPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	if (e->NavigationMode != NavigationMode::Back)
	{
		HomeData^ homeData = ref new HomeData();

		DefaultViewModel->Insert(GetHomePageDataName(), homeData);

		homeData->GetHomePageData();
	}
	NavigationHelper->OnNavigatedTo(e);
}

void PivotPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

/// <summary>
/// Populates the page with content passed during navigation. Any saved state is also
/// provided when recreating a page from a prior session.
/// </summary>
/// <param name="sender">
/// The source of the event; typically <see cref="NavigationHelper"/>.
/// </param>
/// <param name="e">Event data that provides both the navigation parameter passed to
/// <see cref="Frame->Navigate(Type, Object)"/> when this page was initially requested and
/// a dictionary of state preserved by this page during an earlier
/// session. The state will be null the first time a page is visited.</param>
void PivotPage::NavigationHelper_LoadState(Object^ sender, LoadStateEventArgs^ e)
{
	(void) sender;	// Unused parameter
	(void) e;		// Unused parameter
}

/// <summary>
/// Preserves state associated with this page in case the application is suspended or the
/// page is discarded from the navigation cache. Values must conform to the serialization
/// requirements of <see cref="SuspensionManager.SessionState"/>.
/// </summary>
/// <param name="sender">
/// The source of the event; typically <see cref="NavigationHelper"/>.
/// </param>
/// <param name="e">
/// Event data that provides an empty dictionary to be populated with serializable state.
/// </param>
void PivotPage::NavigationHelper_SaveState(Object^ sender, SaveStateEventArgs^ e)
{
	// TODO: Save the unique state of the page here.
}

void PivotPage::PivotItemHome_Loaded(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	(void)sender;	// Unused parameter
	(void)e;		// Unused parameter
}

/// <summary>
/// Loads the content for the second pivot item when it is scrolled into view.
/// </summary>
void PivotPage::PivotItemProfile_Loaded(Object^ sender, RoutedEventArgs ^e)
{
	(void)sender;	// Unused parameter
	(void)e;		// Unused parameter
}

/// <summary>
/// Adds an item to the list when the app bar button is clicked.
/// </summary>
void PivotPage::BottomCmdBar_Refresh_Click(Object^ sender, RoutedEventArgs ^e)
{
	if (m_PivotControl->SelectedIndex == 0)
	{
		if (DefaultViewModel->HasKey(GetHomePageDataName()))
		{
			HomeData^ homeData = safe_cast<HomeData^>(
				DefaultViewModel->Lookup(GetHomePageDataName()));
			homeData->GetHomePageData();
		}
	}
	else if (m_PivotControl->SelectedIndex == 1)
	{
		GetProfilePageDataName();
	}
}

void PivotPage::BottomCmdBar_About_Click(Object^ sender, RoutedEventArgs ^e)
{
	aboutDialog->ShowAsync();
	return;
}

void PEDIY::PivotPage::ForumListView_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e)
{
	auto forumItem = safe_cast<ForumItem^>(e->ClickedItem);

	auto jsonParameter = ref new JsonObject;
	jsonParameter->Insert(L"ForumId", JsonValue::CreateNumberValue(forumItem->ForumId));
	jsonParameter->Insert(L"ForumName", JsonValue::CreateStringValue(forumItem->ForumName));

	auto stringParameter = jsonParameter->Stringify();
	if (!Frame->Navigate(ThreadListPage::typeid, stringParameter))
	{
		throw ref new FailureException(_resourceLoader->GetString(L"NavigationFailedExceptionMessage"));
	}
}

/// <summary>
/// Invoked when an item within a section is clicked.
/// </summary>
void PivotPage::ItemView_ItemClick(Object^ sender, ItemClickEventArgs ^e)
{

}

