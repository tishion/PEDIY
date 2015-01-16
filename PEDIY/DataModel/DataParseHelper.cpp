#include "pch.h"
#include "DataParseHelper.h"

namespace DataParseHelper
{
	CString GetPureJson(LPCTSTR pJsonText, MessageList& msgList)
	{
		CString strJsonText = pJsonText;
		CString strValidJsonText = strJsonText;
		CString strStart = _T("\"message\":\'");
		CString strEnd = _T("\'");
		CString strMessage;
		CString strNewValue;
		int nStart = 0;
		int nEnd = 0;

		for (int i = 0;; i++)
		{
			nStart = strJsonText.Find(strStart, nEnd);
			if (nStart < 0) break;

			nStart += strStart.GetLength();

			nEnd = strJsonText.Find(strEnd, nStart);
			if (nEnd < 0) break;

			strMessage = strJsonText.Mid(nStart, nEnd - nStart);

			msgList.push_back(strMessage);

			strMessage.Format(_T("\"message\":'%s'"), strMessage);
			strNewValue.Format(_T("\"message\":\"msg_%d\""), i);

			strValidJsonText.Replace(strMessage, strNewValue);
		}

		return strValidJsonText;
	}
}