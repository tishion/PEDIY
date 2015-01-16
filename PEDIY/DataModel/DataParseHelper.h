#pragma once

#include <vector>
#include <atlstr.h>
typedef std::vector<CString> MessageList;


namespace DataParseHelper
{
	CString GetPureJson(LPCTSTR pJsonText, MessageList& msgList);

}
