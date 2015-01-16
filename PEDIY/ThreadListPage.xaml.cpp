//
// ThreadListPage.xaml.cpp
// Implementation of the ThreadListPage class
//

#include "pch.h"
#include "ThreadListPage.xaml.h"

using namespace PEDIY;
using namespace PEDIY::Common;
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
DependencyProperty^ ThreadListPage::_defaultViewModelProperty =
DependencyProperty::Register("DefaultViewModel",
TypeName(IObservableMap<String^, Object^>::typeid), TypeName(ThreadListPage::typeid), nullptr);

DependencyProperty^ ThreadListPage::_navigationHelperProperty =
DependencyProperty::Register("NavigationHelper",
TypeName(Common::NavigationHelper::typeid), TypeName(ThreadListPage::typeid), nullptr);

ThreadListPage::ThreadListPage()
{
	InitializeComponent();

	NavigationCacheMode = Navigation::NavigationCacheMode::Enabled;

	_resourceLoader = ResourceLoader::GetForCurrentView(L"Resources");

	SetValue(_defaultViewModelProperty, ref new Platform::Collections::Map<String^, Object^>(std::less<String^>()));

	auto navigationHelper = ref new Common::NavigationHelper(this);
	navigationHelper->LoadState += ref new Common::LoadStateEventHandler(this, &ThreadListPage::LoadState);
	navigationHelper->SaveState += ref new Common::SaveStateEventHandler(this, &ThreadListPage::SaveState);
	SetValue(_navigationHelperProperty, navigationHelper);

	//_grHandler = ref new GestureRecognizerHandler(rootListView);
}

PEDIY::ThreadListPage::~ThreadListPage()
{

}

/// <summary>
/// Used as a trivial view model.
/// </summary>
IObservableMap<String^, Object^>^ ThreadListPage::DefaultViewModel::get()
{
	return safe_cast<IObservableMap<String^, Object^>^>(GetValue(_defaultViewModelProperty));

}
/// <summary>
/// Gets an implementation of <see cref="NavigationHelper"/> designed to be
/// used as a trivial view model.
/// </summary>
Common::NavigationHelper^ ThreadListPage::NavigationHelper::get()
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

void ThreadListPage::OnNavigatedTo(NavigationEventArgs^ e)
{
	if (e->NavigationMode != NavigationMode::Back)
	{
		auto stringParameter = safe_cast<String^>(e->Parameter);
		auto jsonParameter = JsonObject::Parse(stringParameter);

		uint32 ForumId = jsonParameter->GetNamedNumber(L"ForumId");
		String^ ForumName = jsonParameter->GetNamedString(L"ForumName");

		ThreadListData^ threadListData = ref new ThreadListData(ForumId, ForumName);

		DefaultViewModel->Insert(GetThreadListDataName(), threadListData);

		threadListData->GetFirstPageData();
	}
	NavigationHelper->OnNavigatedTo(e);
}

void ThreadListPage::OnNavigatedFrom(NavigationEventArgs^ e)
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
void ThreadListPage::LoadState(Object^ sender, Common::LoadStateEventArgs^ e)
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
void ThreadListPage::SaveState(Object^ sender, Common::SaveStateEventArgs^ e){
	(void) sender;	// Unused parameter
	(void) e; // Unused parameter
}

void PEDIY::ThreadListPage::BottomAppBar_FirstPageButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (DefaultViewModel->HasKey(GetThreadListDataName()))
	{
		ThreadListData^ threadListData = safe_cast<ThreadListData^>(
			DefaultViewModel->Lookup(GetThreadListDataName()));
		if (threadListData)
		{
			threadListData->GetFirstPageData();
		}
	}
}

void PEDIY::ThreadListPage::BottomAppBar_PageUpButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (DefaultViewModel->HasKey(GetThreadListDataName()))
	{
		ThreadListData^ threadListData = safe_cast<ThreadListData^>(
			DefaultViewModel->Lookup(GetThreadListDataName()));
		if (threadListData)
		{
			threadListData->GetPreviousPageData();
		}
	}
}

void PEDIY::ThreadListPage::BottomAppBar_PageDownButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (DefaultViewModel->HasKey(GetThreadListDataName()))
	{
		ThreadListData^ threadListData = safe_cast<ThreadListData^>(
			DefaultViewModel->Lookup(GetThreadListDataName()));
		if (threadListData)
		{
			threadListData->GetNextPageData();
		}
	}
}

void PEDIY::ThreadListPage::BottomAppBar_LastPageButton_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (DefaultViewModel->HasKey(GetThreadListDataName()))
	{
		ThreadListData^ threadListData = safe_cast<ThreadListData^>(
			DefaultViewModel->Lookup(GetThreadListDataName()));
		if (threadListData)
		{
			threadListData->GetLastPageData();
		}
	}
}


void PEDIY::ThreadListPage::ThreadListView_ItemClick(Platform::Object^ sender, Windows::UI::Xaml::Controls::ItemClickEventArgs^ e)
{
	auto threadItem = safe_cast<ThreadItem^>(e->ClickedItem);

	auto jsonParameter = ref new JsonObject;
	jsonParameter->Insert(L"ThreadId", JsonValue::CreateNumberValue(threadItem->ThreadId));

	auto stringParameter = jsonParameter->Stringify();
	if (!Frame->Navigate(PostListPage::typeid, stringParameter))
	{
		throw ref new FailureException(_resourceLoader->GetString(L"NavigationFailedExceptionMessage"));
	}
}
