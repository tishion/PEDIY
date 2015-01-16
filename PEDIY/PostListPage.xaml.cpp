//
// PostListPage.xaml.cpp
// Implementation of the PostListPage class
//

#include "pch.h"
#include "PostListPage.xaml.h"

using namespace PEDIY;
using namespace PEDIY::Data;

using namespace Platform;
using namespace Platform::Collections;
using namespace Windows::Foundation;
using namespace Windows::ApplicationModel::Resources;
using namespace Windows::Foundation::Collections;
using namespace Windows::Graphics::Display;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;

// The Basic Page item template is documented at http://go.microsoft.com/fwlink/?LinkID=390556

PostListPage::PostListPage()
{
	InitializeComponent();

	NavigationCacheMode = Navigation::NavigationCacheMode::Enabled;

	_resourceLoader = ResourceLoader::GetForCurrentView(L"Resources");

	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^, Object^>(std::less<String^>()));
	auto navigationHelper = ref new Common::NavigationHelper(this);
	SetValue(_navigationHelperProperty, navigationHelper);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &PostListPage::LoadState);
	navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &PostListPage::SaveState);
}

PEDIY::PostListPage::~PostListPage()
{

}


DependencyProperty^ PostListPage::_defaultViewModelProperty =
DependencyProperty::Register("DefaultViewModel",
TypeName(IObservableMap<String^, Object^>::typeid), TypeName(PostListPage::typeid), nullptr);

/// <summary>
/// Used as a trivial view model.
/// </summary>
IObservableMap<String^, Object^>^ PostListPage::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));
}

DependencyProperty^ PostListPage::_navigationHelperProperty =
DependencyProperty::Register("NavigationHelper",
TypeName(Common::NavigationHelper::typeid), TypeName(PostListPage::typeid), nullptr);

/// <summary>
/// Gets an implementation of <see cref="NavigationHelper"/> designed to be
/// used as a trivial view model.
/// </summary>
Common::NavigationHelper^ PostListPage::NavigationHelper::get()
{
	return safe_cast<Common::NavigationHelper^>(GetValue(_navigationHelperProperty));
}

#pragma region Navigation support

/// The methods provided in this section are simply used to allow
/// NavigationHelper to respond to the page's navigation methods.
/// 
/// Page specific logic should be placed in event handlers for the  
/// <see cref="NavigationHelper::LoadState"/>
/// and <see cref="NavigationHelper::SaveState"/>.
/// The navigation parameter is available in the LoadState method 
/// in addition to page state preserved during an earlier session.

void PostListPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	if (e->NavigationMode != NavigationMode::Back)
	{
		auto stringParameter = safe_cast<String^>(e->Parameter);
		auto jsonParameter = JsonObject::Parse(stringParameter);

		uint32 ThreadId = jsonParameter->GetNamedNumber(L"ThreadId");

		PostListData^ postListData = ref new PostListData(ThreadId);
		DefaultViewModel->Insert(GetPostListDataName(), postListData);

		postListData->GetFirstPageData();
	}

	NavigationHelper->OnNavigatedTo(e);
}

void PostListPage::OnNavigatedFrom(NavigationEventArgs^ e)
{
	NavigationHelper->OnNavigatedFrom(e);
}

#pragma endregion

/// <summary>
/// Populates the page with content passed during navigation. Any saved state is also
/// provided when recreating a page from a prior session.
/// </summary>
/// <param name="sender">
/// The source of the event; typically <see cref="NavigationHelper"/>
/// </param>
/// <param name="e">Event data that provides both the navigation parameter passed to
/// <see cref="Frame::Navigate(Type, Object)"/> when this page was initially requested and
/// a dictionary of state preserved by this page during an earlier
/// session. The state will be null the first time a page is visited.</param>
void PostListPage::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
{
	(void) sender;	// Unused parameter
	(void) e;	// Unused parameter
}

/// <summary>
/// Preserves state associated with this page in case the application is suspended or the
/// page is discarded from the navigation cache.  Values must conform to the serialization
/// requirements of <see cref="SuspensionManager::SessionState"/>.
/// </summary>
/// <param name="sender">The source of the event; typically <see cref="NavigationHelper"/></param>
/// <param name="e">Event data that provides an empty dictionary to be populated with
/// serializable state.</param>
void PostListPage::SaveState(Object^ sender, Common::SaveStateEventArgs^ e){
	(void) sender;	// Unused parameter
	(void) e; // Unused parameter
}


void PEDIY::PostListPage::BottomAppBar_FirstPageButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (DefaultViewModel->HasKey(GetPostListDataName()))
	{
		PostListData^ postListData = safe_cast<PostListData^>(
			DefaultViewModel->Lookup(GetPostListDataName()));
		if (postListData)
		{
			postListData->GetFirstPageData();
		}
	}
}

void PEDIY::PostListPage::BottomAppBar_PageUpButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (DefaultViewModel->HasKey(GetPostListDataName()))
	{
		PostListData^ postListData = safe_cast<PostListData^>(
			DefaultViewModel->Lookup(GetPostListDataName()));
		if (postListData)
		{
			postListData->GetPreviousPageData();
		}
	}
}

void PEDIY::PostListPage::BottomAppBar_PageDownButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (DefaultViewModel->HasKey(GetPostListDataName()))
	{
		PostListData^ postListData = safe_cast<PostListData^>(
			DefaultViewModel->Lookup(GetPostListDataName()));
		if (postListData)
		{
			postListData->GetNextPageData();
		}
	}
}

void PEDIY::PostListPage::BottomAppBar_LastPageButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (DefaultViewModel->HasKey(GetPostListDataName()))
	{
		PostListData^ postListData = safe_cast<PostListData^>(
			DefaultViewModel->Lookup(GetPostListDataName()));
		if (postListData)
		{
			postListData->GetLastPageData();
		}
	}
}