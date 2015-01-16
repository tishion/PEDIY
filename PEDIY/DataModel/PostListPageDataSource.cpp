#include "pch.h"

using namespace PEDIY::Data;
using namespace PEDIY::PostListPageRender;

using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Resources::Core;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
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
PEDIY::Data::AttachmentItem::AttachmentItem(
	String^ AttachmentId,
	String^ FileName, 
	String^ FileSize) :
	_AttachmentId(_AttachmentId),
	_FileName(FileName),
	_FileSize(FileSize)
{

}


//////////////////////////////////////////////////////////////////////////
PEDIY::Data::PostItem::PostItem(
	String^ PostId,
	int32 HasThumbNail, 
	String^ PostUserName, 
	int32 PostUserId, 
	String^ HasAvatar,
	String^ AvatarTimeStamp,
	String^ PostTime, 
	String^ PostDate, 
	String^ PostTitle, 
	String^ PostMessage) :
	_PostId(PostId),
	_HasThumbNail(HasThumbNail),
	_PostUserName(PostUserName),
	_PostUserId(PostUserId),
	_HasAvatar(_HasAvatar),
	_AvatarTimeStamp(_AvatarTimeStamp),
	_PostTime(PostTime),
	_PostDate(PostDate),
	_PostTitle(PostTitle),
	_PostMessage(PostMessage)
{
	_ThumbnailAttachmentList = ref new AttachmentItemList;
	_OtherAttachmentList = ref new AttachmentItemList;
}

//////////////////////////////////////////////////////////////////////////
DependencyProperty^ PostListData::_DataLoadDone =
DependencyProperty::Register("DataLoadDone",
TypeName(BOOL::typeid), TypeName(PostListData::typeid), nullptr);

DependencyProperty^ PostListData::_FirstPost =
DependencyProperty::Register("FirstPost",
TypeName(PostItem::typeid), TypeName(PostListData::typeid), nullptr);

DependencyProperty^ PostListData::_HTMLSource =
DependencyProperty::Register("HtmlSource",
TypeName(String::typeid), TypeName(PostListData::typeid), nullptr);

PEDIY::Data::PostListData::PostListData(int32 ThreadId)
{
	_ThreadId = ThreadId;
	_CurrentPage = 1;
	_PostList = ref new PostItemList();
	DataLoadDone = TRUE;
}

///*
task <void> PEDIY::Data::PostListData::LoadData(int32 Page)
{
	DataLoadDone = FALSE;
	return CHttpControllor::getInstance()->GetPostListPageData(_ThreadId, Page)
		.then([=](String^ jsonText)
	{
		PostList->Clear();

		CString strText = jsonText->Data();
		CString strValidJsonText;

		MessageList msgList;
		strValidJsonText = DataParseHelper::GetPureJson(strText, msgList);

		strValidJsonText.Replace(L"\r\n", L"");
		strValidJsonText.Replace(L":[,{", L":[{");

		String^ validJsonText = ref new String(strValidJsonText.GetString());

		JsonObject^ jsonObject = JsonObject::Parse(validJsonText);

		_TimeStamp = (jsonObject->GetNamedNumber("time"));
		_PageCount = (jsonObject->GetNamedNumber("pagenav"));
		if (0 == _PageCount)
		{
			_PageCount = 1;
		}

		auto jsonPostList = jsonObject->GetNamedArray("postbits")->GetView();

		std::vector<task<void>> tasks;

		uint32 nIndex = 0;
		_PostList = ref new PostItemList(jsonPostList->Size);
		for (const auto &jsonThread : jsonPostList)
		{
			JsonObject^ jsonPostItem = jsonThread->GetObject();
			String^ postId = jsonPostItem->GetNamedString("postid");

			auto t = CHttpControllor::getInstance()->GetPostDetailData(postId)
				.then([=](String^ message)
			{
				String^ postTitle = jsonPostItem->HasKey("title") ? HtmlUtilities::ConvertToText(jsonPostItem->GetNamedString("title")) : L"";
				String^ postMessage = message;

				PostItem^ postItem = ref new PostItem(
					postId,
					jsonPostItem->GetNamedNumber("thumbnail"),
					HtmlUtilities::ConvertToText(jsonPostItem->GetNamedString("username")),
					jsonPostItem->GetNamedNumber("userid"),
					jsonPostItem->GetNamedString("avatar"),
					jsonPostItem->GetNamedString("avatardateline"),
					HtmlUtilities::ConvertToText(jsonPostItem->GetNamedString("posttime")),
					HtmlUtilities::ConvertToText(jsonPostItem->GetNamedString("postdate")),
					postTitle,
					postMessage);

				if (jsonPostItem->HasKey("thumbnailattachments"))
				{
					auto jsonAttachmentList = jsonPostItem->GetNamedArray("thumbnailattachments")->GetView();
					for (const auto &jsonAttachment : jsonAttachmentList)
					{
						JsonObject^ jsonAttachmentItem = jsonAttachment->GetObject();

						AttachmentItem^ attchmentItem = ref new AttachmentItem(
							jsonAttachmentItem->GetNamedString("attachmentid"),
							HtmlUtilities::ConvertToText(jsonAttachmentItem->GetNamedString("filename")),
							jsonAttachmentItem->GetNamedString("filesize"));

						postItem->ThumbnailAttachmentList->Append(attchmentItem);
					}
				}

				if (jsonPostItem->HasKey("otherattachments"))
				{
					auto jsonAttachmentList = jsonPostItem->GetNamedArray("otherattachments")->GetView();
					for (const auto &jsonAttachment : jsonAttachmentList)
					{
						JsonObject^ jsonAttachmentItem = jsonAttachment->GetObject();

						AttachmentItem^ attchmentItem = ref new AttachmentItem(
							jsonAttachmentItem->GetNamedString("attachmentid"),
							HtmlUtilities::ConvertToText(jsonAttachmentItem->GetNamedString("filename")),
							jsonAttachmentItem->GetNamedString("filesize"));

						postItem->OtherAttachmentList->Append(attchmentItem);
					}
				}

				PostList->SetAt(nIndex, postItem);
			});

			tasks.push_back(t);
			nIndex++;
		}

		when_all(tasks.begin(), tasks.end())
			.then([this]()
		{
			CPostListPageRender render(this);
			HtmlSource = render.GetHtmlSource();
			DataLoadDone = TRUE;		
		});
	});
}
//*/

void PEDIY::Data::PostListData::GetFirstPageData()
{
	if (DataLoadDone)
	{
		_CurrentPage = 1;
		LoadData(_CurrentPage);
	}
}

void PEDIY::Data::PostListData::GetPreviousPageData()
{
	if (DataLoadDone && _CurrentPage > 1)
	{
		LoadData(--_CurrentPage);
	}
}

void PEDIY::Data::PostListData::GetNextPageData()
{
	if (DataLoadDone && _CurrentPage < _PageCount)
	{
		LoadData(++_CurrentPage);
	}
}

void PEDIY::Data::PostListData::GetLastPageData()
{
	if (DataLoadDone)
	{
		_CurrentPage = _PageCount;
		LoadData(_CurrentPage);
	}
}

void PEDIY::Data::PostListData::OnHTMLSourceChanged(DependencyObject^ d, DependencyPropertyChangedEventArgs^ e)
{
	WebView^ webView = safe_cast<WebView^>(d);
	String^ value = safe_cast<String^>(e->NewValue);
	webView->NavigateToString(value);
}