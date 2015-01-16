#include "pch.h"
#include <atlstr.h>

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
ForumItem::ForumItem(
	String^ ForumGroupName,
	String^ ForumName, 
	int32 ForumId,
	int32 ForumImgId) :
	_ForumGroupName(ForumGroupName),
	_ForumName(ForumName),
	_ForumId(ForumId),
	_ForumImgId(ForumImgId)
{
}

//////////////////////////////////////////////////////////////////////////
ForumGroupItem::ForumGroupItem(
	String^ ForumTitle) :
	_ForumGroupName(ForumTitle),
	_ForumList(ref new ForumItemList())
{

}

//////////////////////////////////////////////////////////////////////////
DependencyProperty^ HomeData::_DataLoadDone =
DependencyProperty::Register("DataLoadDone",
TypeName(BOOL::typeid), TypeName(HomeData::typeid), nullptr);

HomeData::HomeData()
{
	_ForumGroupList = ref new ForumGroupItemList();
	DataLoadDone = TRUE;
}

task<bool> PEDIY::Data::HomeData::LoadData()
{
	DataLoadDone = FALSE;

	return CHttpControllor::getInstance()->GetHomePageData()
		.then([this](String^ jsonText)
	{
		ForumGroupList->Clear();

		JsonObject^ jsonObject = JsonObject::Parse(jsonText);

		auto jsonForumGroupList = jsonObject->GetNamedArray("forumbits")->GetView();

		for (const auto &jsonForumGroup : jsonForumGroupList)
		{
			JsonObject^ jsonForumGroupItem = jsonForumGroup->GetObject();

			String^ forumGroupName = jsonForumGroupItem->GetNamedString("forumTitle");
			ForumGroupItem^ forumGroupItem = ref new ForumGroupItem(forumGroupName);

			auto jsonForumList = jsonForumGroupItem->GetNamedArray("forumSubTitle")->GetView();
			for (const auto &jsonForum : jsonForumList)
			{
				JsonObject^ jsonForumItem = jsonForum->GetObject();

				ForumItem^ forumItem = ref new ForumItem(
					forumGroupName,
					HtmlUtilities::ConvertToText(jsonForumItem->GetNamedString("name")),
					jsonForumItem->GetNamedNumber("id"),
					(uint32)(jsonForumItem->GetNamedNumber("imgId")));

				forumGroupItem->ForumList->Append(forumItem);
			};

			ForumGroupList->Append(forumGroupItem);
		};

		DataLoadDone = TRUE;
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

//task<void>  HomeData::Init()
//{
//	return create_task(_loadCompletionEvent);
//}

void PEDIY::Data::HomeData::GetHomePageData()
{
	if (DataLoadDone)
	{
		LoadData();
	}
}

//task<ForumGroupItem^> HomeData::GetForumGroupItem(String^ Name)
//{
//	return Init()
//		.then([this, Name]() -> ForumGroupItem^
//	{
//		// Simple linear search is acceptable for small data sets
//		for (const auto& forumGroupItem : ForumGroupList)
//		{
//			if (forumGroupItem->ForumGroupName == Name)
//			{
//				return forumGroupItem;
//			}
//		}
//		return nullptr;
//	});
//}
//
//task<ForumItem^> HomeData::GetForumItem(int32 Id)
//{
//	return Init()
//		.then([this, Id]() -> ForumItem^
//	{
//		// Simple linear search is acceptable for small data sets
//		for (const auto& forumGroupItem : ForumGroupList)
//		{
//			for (const auto& forumItem : forumGroupItem->ForumList)
//			{
//				if (forumItem->ForumId == Id)
//				{
//					return forumItem;
//				}
//			}
//		}
//		return nullptr;
//	});
//}
