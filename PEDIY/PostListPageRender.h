#pragma once


#include "pch.h"
#include "PostListPage.xaml.h"


using namespace PEDIY::Data;
using namespace Platform;
using namespace Platform::Collections;


namespace PEDIY
{
	namespace PostListPageRender
	{
		class CPostListPageRender
		{
		public:
			CPostListPageRender(PostListData^ postListData);
			String^ GetHtmlSource();

		protected:

		private:
			String^ HtmlSource_;
			PostListData^ PostListData_;
		};
	}
}





