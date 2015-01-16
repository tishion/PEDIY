#pragma once

#include <atlstr.h>

using namespace concurrency;
using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Data::Json;
using namespace Windows::Data::Html;
using namespace Windows::Web::Http;

ref class CHttpControllor sealed
{
internal:
	CHttpControllor();
	static CHttpControllor^ getInstance();

	Uri^ GetLoginUri();
	task<String^> DoLogin();

	Uri^ GetSecurityTokenUri();
	task<String^> GetSecurityToken();

	Uri^ GetHomePageUri();
	task<String^> GetHomePageData();

	Uri^ GetThreadListPageUri(uint32 ForumId, uint32 Page=1);
	task<String^> GetThreadListPageData(uint32 ForumId, uint32 Page=1);


	Uri^ GetPostListPageUri(uint32 ThreadId, uint32 Page=1);
	task<String^> GetPostListPageData(uint32 ThreadId, uint32 Page = 1);

	Uri^ GetPostDetailUri(String^ PostId);	task<String^> GetPostDetailData(String^ PostId);

private:
	static HttpClient^	s_Client;
};

