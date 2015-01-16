#pragma once

#include "pch.h"
using namespace Platform;

String^ htmlDoctype = 
L"<!DOCTYPE html PUBLIC \" -//W3C//DTD XHTML 1.0 Transitional//EN\" \"http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd\">\r\n";
String^ htmlHtmlStart = 
L"<html xmlns=\"http://www.w3.org/1999/xhtml\">\r\n";
String^ htmlHead =
L"<head>\r\n"\
L"<META content=\"text/html; charset=utf-8\" http-equiv=Content-Type>\r\n"\
L"<style type=\"text/css\" id=\"vbulletin_css\">\r\n"\
L"body {\r\n"\
L"	background: #EFF3F9;\r\n"\
L"	color: #13253C;\r\n"\
L"}\r\n"\
L"a:link, body_alink {\r\n"\
L"	color: #000000;\r\n"\
L"	text-decoration: none;\r\n"\
L"}\r\n"\
L"a:visited, body_avisited {\r\n"\
L"	color: #000000;\r\n"\
L"	text-decoration: none;\r\n"\
L"}\r\n"\
L"a:hover, a:active, body_ahover {\r\n"\
L"	color: #529AF2;\r\n"\
L"	text-decoration: underline;\r\n"\
L"}\r\n"\
L".page {\r\n"\
L"	background: #FFFFFF;\r\n"\
L"	color: #13253C;\r\n"\
L"}\r\n"\
L".alt1, .alt1Active {\r\n"\
L"	background: #F5F5F5;\r\n"\
L"	color: #13253C;\r\n"\
L"	border-bottom: 1px solid #E2E7F0;\r\n"\
L"	padding: 5px;\r\n"\
L"}\r\n"\
L".alt2, .alt2Active {\r\n"\
L"	width: auto !important;\r\n"\
L"	height: auto !important;\r\n"\
L"	background: #DEE3E7;\r\n"\
L"	color: #333333;\r\n"\
L"	border-bottom: 1px solid #E2E7F0;\r\n"\
L"}\r\n"\
L".smallfont {\r\n"\
L"	word-break: normal;"\
L"}\r\n"\
L".tborder {\r\n"\
L"	background: #FFFFFF;\r\n"\
L"	color: #13253C;\r\n"\
L"	border: 1px solid #8FA0B0;\r\n"\
L"}\r\n"\
L"legend {\r\n"\
L"	color: #00447F;\r\n"\
L"}\r\n"\
L".tb {\r\n"\
L"	table-layout: fixed;\r\n"\
L"}\r\n"\
L"#wrap {\r\n"\
L"	word-break: break-all;\r\n"\
L"	width: 100%;\r\n"\
L"}\r\n"\
L".divh {\r\n"\
L"	background-color: #FFFFCC;\r\n"\
L"	border: 1px dashed #000000;\r\n"\
L"	text-align: center;\r\n"\
L"}\r\n"\
L".quote {\r\n"\
L"	width: auto !important;\r\n"\
L"	height: auto !important;\r\n"\
L"	background-color: #FFFFCC;\r\n"\
L"	border: 1px solid #000000;\r\n"\
L"	text-align: left;\r\n"\
L"}\r\n"\
L".quoted1 {\r\n"\
L"	width: 95%;\r\n"\
L"	border: 1px solid #909090;\r\n"\
L"	padding: 8px;\r\n"\
L"	padding-top: 0px;\r\n"\
L"	margin: 8px;\r\n"\
L"	margin-top: 12pt;\r\n"\
L"	text-align: left;\r\n"\
L"}\r\n"\
L".quoted2 {\r\n"\
L"	position: relative;\r\n"\
L"	left: 4px;\r\n"\
L"	top: -7.5pt;\r\n"\
L"	width: auto;\r\n"\
L"	color: #ffffff;\r\n"\
L"	border: 1px solid #909090;\r\n"\
L"	background-color: #909090;\r\n"\
L"	padding: 1px;\r\n"\
L"	padding-left: 6px;\r\n"\
L"	padding-right: 6px;\r\n"\
L"	z-index: 1;\r\n"\
L"}\r\n"\

L".postlist {\r\n"\
L"	padding-left: 5px;\r\n"\
L"	padding-right: 5px;\r\n"\
L"}\r\n"\

L".postitem {\r\n"\
L"	margin-bottom: 20px;\r\n"\
L"}\r\n"\

L".posttitle {\r\n"\
L"	font-size: 60px;\r\n"\
L"	word-break: break-all;\r\n"\
L"}\r\n"\

L".postusername {\r\n"\
L"	float: left;\r\n"\
L"	font-size: 50px;\r\n"\
L"}\r\n"\

L".postdatetime {\r\n"\
L"	float: right;\r\n"\
L"	font-size: 50px;\r\n"\
L"}\r\n"\

L".postmessage {\r\n"\
L"	font-size: 50px;\r\n"\
L"	word-break: break-all;\r\n"\
L"}\r\n"\

L"</style>\r\n"\
L"</head>\r\n";

String^ htmlPostListStart =
L"<body><div class=\"postlist\">\r\n";

String^ htmlPostItemStart =
L"	<div class=\"postitem\">\r\n";

String^ htmlPostItemTitleStart =
L"    	<div class=\"posttitle\">\
 			<strong>";
String^ htmlPostItemTitleEnd =
L"</strong>\r\n\
         </div>";
String^ htmlPostUserNameDateTimeStart =
L"    	<div class=\"postusernamedatetime\">\r\n";
String^ htmlPostUserNameStart =
L"        	<div class=\"postusername\"><strong>";
String^ htmlPostUserNameEnd =
L"</strong></div>\r\n";
String^ htmlPostDateTimeStart =
L"        	<div class=\"postdatetime\">";
String^ htmlPostDateTimeEnd =
L"</div>\r\n";
String^ htmlPostUserNameDateTimeEnd =
L"      </div>\r\n"\
L"      <hr style=\"height:1px; clear: both;\" />\r\n";
String^ htmlPostMessageStart =
L"      <div class=\"postmessage\">\r\n";
String^ htmlPostMessageEnd =
L"      </div>\r\n";
String^ htmlPostItemEnd =
L"    </div>\r\n";
String^ htmlPostListEnd =
L"</div></body>\r\n";
String^ htmlHtmlEnd =
L"</html>";