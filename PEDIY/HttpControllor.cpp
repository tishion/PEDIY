#include "pch.h"
#include <atlstr.h>
#include <regex>

HttpClient^ 
CHttpControllor::s_Client = nullptr;


CHttpControllor^ CHttpControllor::getInstance()
{
	static CHttpControllor^ s_instance = ref new CHttpControllor();
	return s_instance;
}

CHttpControllor::CHttpControllor()
{
	s_Client = ref new HttpClient();


}

Uri^ CHttpControllor::GetSecurityTokenUri()
{
	CString str;
	str.Format(L"http://bbs.pediy.com/getsecuritytoken.php?styleid=12");
	return ref new Uri(ref new String(str.GetString()));
}

task<String^> CHttpControllor::GetSecurityToken()
{
	return create_task(s_Client->GetStringAsync(GetSecurityTokenUri()));

}

Uri^ CHttpControllor::GetHomePageUri()
{
	CString str;
	str.Format(L"http://bbs.pediy.com/index.php?styleid=12");
	return ref new Uri(ref new String(str.GetString()));
}

task<String^> CHttpControllor::GetHomePageData()
{
	return create_task(s_Client->GetStringAsync(GetHomePageUri()))
		.then([](String^ response)
	{
		// make the response string to well-formed json text
		CString strResponse(response->Data());

		strResponse.Replace(L"\r\n", L"");
		strResponse.Replace(L":[,{", L":[{");

		strResponse.Replace(L"forumTitle:", L"\"forumTitle\":");
		strResponse.Replace(L"forumSubTitle:", L"\"forumSubTitle\":");
		strResponse.Replace(L"name:", L"\"name\":");
		strResponse.Replace(L"id:", L"\"id\":");
		strResponse.Replace(L"imgId:", L"\"imgId\":");

		return ref new String(strResponse.GetString());
	});
}


Uri^ CHttpControllor::GetThreadListPageUri(uint32 ForumId, uint32 Page)
{
	CString str;
	str.Format(L"http://bbs.pediy.com/forumdisplay.php?styleid=12&f=%d&page=%d", ForumId, Page);
	return ref new Uri(ref new String(str.GetString()));
}

task<String^> CHttpControllor::GetThreadListPageData(uint32 ForumId, uint32 Page)
{
	return create_task(s_Client->GetStringAsync(GetThreadListPageUri(ForumId, Page)))
		.then([](String^ response)
	{
		CString strResponse(response->Data());

		strResponse.Replace(L"\r\n", L"");
		strResponse.Replace(L":[,{", L":[{");

		return ref new String(strResponse.GetString());
	});
};

Uri^ CHttpControllor::GetPostListPageUri(uint32 ThreadId, uint32 Page)
{
	CString str;
	str.Format(L"http://bbs.pediy.com/showthread.php?styleid=12&t=%d&page=%d", ThreadId, Page);
	return ref new Uri(ref new String(str.GetString()));
}

task<String^> CHttpControllor::GetPostListPageData(uint32 ThreadId, uint32 Page)
{
	return create_task(s_Client->GetStringAsync(GetPostListPageUri(ThreadId, Page)));
}

Uri^ CHttpControllor::GetPostDetailUri(String^ PostId)
{
	CString str;
	str.Format(L"http://bbs.pediy.com/showpost.php?styleid=12&p=%s", PostId->Data());
	return ref new Uri(ref new String(str.GetString()));
}

task<String^> CHttpControllor::GetPostDetailData(String^ PostId)
{
	return create_task(s_Client->GetStringAsync(GetPostDetailUri(PostId)));
}

Uri^ CHttpControllor::GetLoginUri()
{
	CString str;
	str.Format(L"http://bbs.pediy.com/login.php?do=login&styleid=12");
	return ref new Uri(ref new String(str.GetString()));
}

task<String^> CHttpControllor::DoLogin()
{

}
