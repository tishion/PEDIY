#include "pch.h"

using namespace PEDIY::Data;

using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Resources::Core;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Interop;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Media::Imaging;
using namespace Windows::Storage;
using namespace Windows::Data::Json;
using namespace Windows::Data::Html;
using namespace Windows::Web::Http;

//////////////////////////////////////////////////////////////////////////
PEDIY::Data::ThreadItem::ThreadItem(
	int32 ThreadId, 
	String^ ThreadTitle, 
	String^ PostUserName, 
	int32 PostUserId,
	int32 HasAvatar, 
	String^ AvatarTimeStamp,
	String^ LastReplyDate,
	int32 ViewCount, 
	int32 ReplyCount, 
	int32 GlobalStick, 
	int32 ForumStick, 
	int32 Quality):
	_ThreadId(ThreadId),
	_ThreadTitle(ThreadTitle),
	_PostUserName(PostUserName),
	_PostUserId(_PostUserId),
	_HasAvatar(HasAvatar),
	_AvatarTimeStamp(AvatarTimeStamp),
	_LastReplyDate(LastReplyDate),
	_ViewCount(ViewCount),
	_ReplyCount(ReplyCount),
	_GlobalStick(GlobalStick),
	_ForumStick(ForumStick),
	_Quality(Quality)

{

}

//////////////////////////////////////////////////////////////////////////
DependencyProperty^ ThreadListData::_DataLoadDone =
DependencyProperty::Register("DataLoadDone",
TypeName(BOOL::typeid), TypeName(ThreadListData::typeid), nullptr);


PEDIY::Data::ThreadListData::ThreadListData(int32 ForumId, String^ ForumName)
{
	_ForumId = ForumId;
	_ForumName = ForumName;
	_TimeStamp = 0;
	_PageCount = 0;
	_CurrentPage = 1;
	_ThreadList = ref new ThreadItemList();
	DataLoadDone = TRUE;
}

task<bool> PEDIY::Data::ThreadListData::LoadData(int32 Page)
{
	DataLoadDone = FALSE;
	return CHttpControllor::getInstance()->GetThreadListPageData(_ForumId, Page)
		.then([this](String^ jsonText)
	{
		ThreadList->Clear();

		JsonObject^ jsonObject = JsonObject::Parse(jsonText);

		_TimeStamp	= jsonObject->GetNamedNumber("time");
		_PageCount	= jsonObject->GetNamedNumber("pagenav");
		if (0 == _PageCount)
		{
			_PageCount = 1;
		}

		auto jsonThreadList = jsonObject->GetNamedArray("threadList")->GetView();

		for (const auto &jsonThread : jsonThreadList)
		{
			JsonObject^ jsonThreadItem = jsonThread->GetObject();

			ThreadItem^ threadItem = ref new ThreadItem(
				jsonThreadItem->GetNamedNumber("threadid"),
				HtmlUtilities::ConvertToText(jsonThreadItem->GetNamedString("threadtitle")),
				HtmlUtilities::ConvertToText(jsonThreadItem->GetNamedString("postusername")),
				jsonThreadItem->GetNamedNumber("postuserid"),
				jsonThreadItem->GetNamedNumber("avatar"),
				HtmlUtilities::ConvertToText(jsonThreadItem->GetNamedString("avatardateline")),
				HtmlUtilities::ConvertToText(jsonThreadItem->GetNamedString("lastpostdate")),
				jsonThreadItem->GetNamedNumber("views"),
				jsonThreadItem->GetNamedNumber("replycount"),
				jsonThreadItem->GetNamedNumber("globalsticky"),
				jsonThreadItem->GetNamedNumber("sticky"),
				jsonThreadItem->GetNamedNumber("goodnees"));

			ThreadList->Append(threadItem);
		};
	})
		.then([this](task<void> t)
	{
		bool bRet = true;
		try
		{
			t.get();
		}
		catch (Platform::COMException^ e)
		{
			OutputDebugString(e->Message->Data());
			// TODO: If App can recover from exception,
			// remove throw; below and add recovery code.
			bRet = false;
		}
		// Signal load completion event
		//_loadCompletionEvent.set();

		DataLoadDone = TRUE;

		return bRet;
	});
}

//task<void> PEDIY::Data::ThreadListData::Init()
//{
//	return create_task(_loadCompletionEvent);
//}

void PEDIY::Data::ThreadListData::GetFirstPageData()
{
	if (DataLoadDone)
	{
		_CurrentPage = 1;
		LoadData(_CurrentPage);
	}
}

void PEDIY::Data::ThreadListData::GetPreviousPageData()
{
	if (DataLoadDone && _CurrentPage > 1)
	{
		LoadData(--_CurrentPage);
	}
}

void PEDIY::Data::ThreadListData::GetNextPageData()
{
	if (DataLoadDone && _CurrentPage < _PageCount)
	{
		LoadData(++_CurrentPage);
	}
}

void PEDIY::Data::ThreadListData::GetLastPageData()
{
	if (DataLoadDone)
	{
		_CurrentPage = _PageCount;
		LoadData(_CurrentPage);
	}
}