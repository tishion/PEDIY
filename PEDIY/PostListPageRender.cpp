#include "pch.h"
#include "PostListPageRender.h"
#include "PostListPageRenderConst.h"

namespace PEDIY
{
	namespace PostListPageRender
	{
		CPostListPageRender::CPostListPageRender(PostListData^ postListData)
		{
			HtmlSource_ = ref new String(L"");
			PostListData_ = postListData;
		}

		String^ CPostListPageRender::GetHtmlSource()
		{
			// doctype
			HtmlSource_ += htmlDoctype;
			// Begin of <HTML>
			HtmlSource_ += htmlHtmlStart;
			// Head
			HtmlSource_ += htmlHead;
			// 
			HtmlSource_ += htmlPostListStart;

			for (const auto &postItem : PostListData_->PostList)
			{
				String^ postItemString = ref new String(L"");
				postItemString += htmlPostItemStart;
				// PostTitle
				if (nullptr != postItem->PostTitle
					&& false == postItem->PostTitle->IsEmpty())
				{
					postItemString += htmlPostItemTitleStart;
					postItemString += postItem->PostTitle;
					postItemString += htmlPostItemTitleEnd;
				}

				// PostDate + PostTime
				{
					postItemString += htmlPostUserNameDateTimeStart;

					postItemString += htmlPostUserNameStart;
					postItemString += postItem->PostUserName;
					postItemString += htmlPostUserNameEnd;

					postItemString += htmlPostDateTimeStart;
					postItemString += postItem->PostDate;
					postItemString += L", ";
					postItemString += postItem->PostTime;
					postItemString += htmlPostDateTimeEnd;					

					postItemString += htmlPostUserNameDateTimeEnd;
				}

				// PostMessage
				{
					postItemString += htmlPostMessageStart;
					postItemString += postItem->PostMessage;
					postItemString += htmlPostMessageEnd;
				}

				// Attachments
				{

				}

				postItemString += htmlPostItemEnd;

				HtmlSource_ += postItemString;
			}

			HtmlSource_ += htmlPostListEnd;

			HtmlSource_ += htmlHtmlEnd;

			return HtmlSource_;
		}
	}
}

