#pragma once

//功能说明
//获得帖子列表详细信息，单独的帖子称为post
//
//调用说明
//请求地址：http ://bbs.pediy.com/showthread.php?t=threadid?styleid=12
//登录之后需要提交cookie
//
//参数说明：
//Name                Type    Description
//threadid            int        主题帖的ID
//
//返回结果
//返回参数说明：
//Name                Type    Description
//time                   int       取主题帖的当前时间戳
//pagenav            int       这个版面主题帖有多少页（导航条里的最大数）
//postbits             结构体 单个post里详细信息
//
//postbits 结构说明：
//Name                Type    Description
//postid                int       帖子ID
//thumbnail         int       是否含有缩略图，暂时没启有，默认为0
//username          string  帖子作者的用户名
//userid                int       帖子作者的用户ID
//avatar                int       帖子作者是否有头像，0没有头像，1有头像
//avatardateline  int       帖子作者头像的时间戳，如果没头像则为0
//posttime           string  帖子的时间，格式如：12 : 13 : 14
//postdate           string   帖子的日期，格式如：2013 - 01 - 30
//title                   string   帖子的标题内容
//message           string   帖子的主体内容
//thumbnailattachments  结构体  附件
//
//thumbnailattachments 结构说明：
//Name                Type    Description
//attachmentid    int       附件ID
//filename            string  附件文件名
//filesize               int       附件大小
//
//返回JSON样例：
//http ://bbs.pediy.com/showthread.php?t=161964?styleid=12
//
//
//{"time":1359885305, "pagenav" : 0, "postbits" : [{"postid":"1139493", "thumbnail" : 0, "username" : "kanxue", "userid" : 93, "avatar" : "1", "avatardateline" : "1328408022", "posttime" : "12:13:14", "postdate" : "2013-01-30", "title" : "【测试】附件图片测试2", "message" : '再次测试~~<br/><img  src="http://bbs.pediy.com/attachment.php?attachmentid=76125&amp;thumb=1&amp;d=1359535385"><br/>大家好', "thumbnailattachments" : [{"attachmentid": "76126", "filename" : "meigus15.jpg", "filesize" : "7626"}, { "attachmentid": "76128", "filename" : "W020121221530237405253.jpg", "filesize" : "5731" }], "otherattachments" : [, { "attachmentid": "76239", "filename" : "test.rar", "filesize" : "53298" }] }]}

using namespace concurrency;
using namespace Platform;

namespace PEDIY
{
	namespace Data
	{
		[Windows::UI::Xaml::Data::Bindable]
		public ref class AttachmentItem sealed :
			public Windows::UI::Xaml::Data::ICustomPropertyProvider
		{
		public:
			property String^	 AttachmentId
			{
				String^	get() { return _AttachmentId; };
			}

			property String^ FileName
			{
				String^ get() { return _FileName; };
			}

			property String^ FileSize
			{
				String^	get() { return _FileSize; };
			}

			property Windows::UI::Xaml::Interop::TypeName Type
			{
				virtual Windows::UI::Xaml::Interop::TypeName get()
				{
					return this->GetType();
				};
			}

		public:
			// Implementation of ICustomPropertyProvider provides a string representation for the object to be used as automation name for accessibility
			virtual Windows::UI::Xaml::Data::ICustomProperty^
				GetCustomProperty(Platform::String^ name) { return nullptr; };

			virtual Windows::UI::Xaml::Data::ICustomProperty^
				GetIndexedProperty(Platform::String^ name, Windows::UI::Xaml::Interop::TypeName type) { return nullptr; };

			virtual Platform::String^
				GetStringRepresentation() { return _FileName; };

		internal:
			AttachmentItem(String^ AttachmentId, String^ FileName, String^ FileSize);

		private:
			String^					_AttachmentId;
			String^					_FileName;
			String^					_FileSize;
		};


		[Windows::UI::Xaml::Data::Bindable]
		public ref class PostItem sealed :
			public Windows::UI::Xaml::Data::ICustomPropertyProvider
		{
			typedef Platform::Collections::Vector<AttachmentItem^> AttachmentItemList;
		public:

			property String^ PostId
			{
				String^ get() { return _PostId; };
			}

			property String^ PostUserName
			{
				String^ get() { return _PostUserName; };
			}

			property String^ HasAvatar
			{
				String^ get() { return _HasAvatar; };
			}

			property String^ AvatarTimeStamp
			{
				String^ get() { return _AvatarTimeStamp; };
			}

			property String^ PostTime
			{
				String^ get() { return _PostTime; };
			}

			property String^ PostDate
			{
				String^ get() { return _PostDate; };

			}

			property String^ PostTitle
			{
				String^ get() { return _PostTitle; };

			}

			property String^ PostMessage
			{
				String^ get() { return _PostMessage; };

			}

			property int32 HasThumbNail
			{
				int32 get() { return _HasThumbNail; };

			}

			property int32 PostUserId
			{
				int32 get() { return _PostUserId; };

			}

			property Windows::Foundation::Collections::IObservableVector<AttachmentItem^>^ ThumbnailAttachmentList
			{
				Windows::Foundation::Collections::IObservableVector<AttachmentItem^>^ get()
				{
					return _ThumbnailAttachmentList;
				};
			}

			property Windows::Foundation::Collections::IObservableVector<AttachmentItem^>^ OtherAttachmentList
			{
				Windows::Foundation::Collections::IObservableVector<AttachmentItem^>^ get()
				{
					return _OtherAttachmentList;
				};
			}


		public:
			property Windows::UI::Xaml::Interop::TypeName Type
			{
				virtual Windows::UI::Xaml::Interop::TypeName get()
				{
					return this->GetType();
				};
			}

		public:
			// Implementation of ICustomPropertyProvider provides a string representation for the object to be used as automation name for accessibility
			virtual Windows::UI::Xaml::Data::ICustomProperty^
				GetCustomProperty(Platform::String^ name) { return nullptr; };

			virtual Windows::UI::Xaml::Data::ICustomProperty^
				GetIndexedProperty(Platform::String^ name, Windows::UI::Xaml::Interop::TypeName type) { return nullptr; };

			virtual Platform::String^
				GetStringRepresentation() { return nullptr;  };

		internal:
			PostItem(
				String^	PostId,
				int32	HasThumbNail,
				String^	PostUserName,
				int32	PostUserId,
				String^	HasAvatar,
				String^	AvatarTimeStamp,
				String^	PostTime,
				String^	PostDate,
				String^	PostTitle,
				String^	PostMessage);

		private:
			String^		_PostId;
			int32		_HasThumbNail;
			String^		_PostUserName;
			int32		_PostUserId;
			String^		_HasAvatar;
			String^		_AvatarTimeStamp;
			String^		_PostTime;
			String^		_PostDate;
			String^		_PostTitle;
			String^		_PostMessage;

			AttachmentItemList^	_ThumbnailAttachmentList;
			AttachmentItemList^	_OtherAttachmentList;
		};

		//
		[Windows::UI::Xaml::Data::Bindable]
		public ref class PostListData sealed :
			public Windows::UI::Xaml::DependencyObject
		{
			typedef Platform::Collections::Vector<PostItem^> PostItemList;
		public:
			property String^ HtmlSource
			{
				String^ get() 
				{ 
					return (String^)GetValue(_HTMLSource); 
				};

				void set(String^ value) 
				{ 
					SetValue(_HTMLSource, value);
				};
			}

			property Windows::Foundation::Collections::IObservableVector<PostItem^>^ PostList
			{
				Windows::Foundation::Collections::IObservableVector<PostItem^>^ get()
				{
					return _PostList;
				};
			}

			property PostItem^ FirstPost
			{
				PostItem^ get()
				{
					return (PostItem^)GetValue(_FirstPost);
				};

				void set(PostItem^ value)
				{
					SetValue(_FirstPost, value);
				};
			}

			property BOOL DataLoadDone
			{
				BOOL get()
				{
					return (BOOL)GetValue(_DataLoadDone);
				};

				void set(BOOL value)
				{
					SetValue(_DataLoadDone, value);
				};
			}
		internal:
			PostListData(int32 ThreadId);

			task<void>
				LoadData(int32 Page = 1);

			void
				GetFirstPageData();

			void
				GetPreviousPageData();

			void
				GetNextPageData();

			void
				GetLastPageData();

		private:
			//task_completion_event<void>						_loadCompletionEvent;
			static Windows::UI::Xaml::DependencyProperty^	_DataLoadDone;
			static Windows::UI::Xaml::DependencyProperty^	_FirstPost;
			static Windows::UI::Xaml::DependencyProperty^	_HtmlSource;

			static Windows::UI::Xaml::DependencyProperty^	_HTMLSource;
			static void OnHTMLSourceChanged(DependencyObject^ d, Windows::UI::Xaml::DependencyPropertyChangedEventArgs^ e);

			int32							_ThreadId;
			
			int32							_TimeStamp;
			int32							_PageCount;
			int32							_CurrentPage;

			PostItemList^					_PostList;
		};
	}
}