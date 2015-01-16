#pragma once

using namespace concurrency;
using namespace Platform;


namespace PEDIY
{
	namespace Data
	{
		//  threadtitle		string	帖子的标题
		//  threadid		int		帖子的ID
		//	postusername	string	帖子的作者
		//	postuserid		int		帖子作者的ID
		//	avatar			int		作者是否有头像，0没有，1有
		//	avatardateline	int		作者上传头像的时间戳
		//	lastpostdate	int		帖子被回复的时间
		//	views			int		帖子的查看数
		//	replycount		int		帖子被回复数
		//	globalsticky	int		是否全局置顶，全局置顶该字段为 - 1，否则为0
		//	sticky			int		是否置顶帖，置顶帖该字段为1, 否则为0
		//	goodnees		int		是否为精华帖
		//								0：表示不是精华帖
		//								1： 转帖
		//								2： 关注
		//								10：优秀
		//								40：精华
		//								80：酷帖
		//								若是工具下载版，该字段含义：
		//								1：收集
		//								10： 利器
		//								30 ：独家
		[Windows::UI::Xaml::Data::Bindable]
		public ref class ThreadItem sealed :
			public Windows::UI::Xaml::Data::ICustomPropertyProvider
		{
		public:

			property String^ ThreadTitle
			{
				String^ get() { return _ThreadTitle; };
			}

			property String^ PostUserName
			{
				String^ get() { return _PostUserName; };
			}

			property String^ AvatarTimeStamp
			{
				String^ get() { return _AvatarTimeStamp; };
			}

			property String^ LastReplyDate
			{
				String^ get() { return _LastReplyDate; };
			}

			property int32 ThreadId
			{
				int32 get() { return _ThreadId;  };
			}

			property int32 PostUserId
			{
				int32 get() { return _PostUserId; };
			}

			property int32 HasAvatar
			{
				int32 get() { return _HasAvatar; };
			}

			property int32 ViewCount
			{
				int32 get() { return _ViewCount; };
			}

			property int32 ReplyCount
			{
				int32 get() { return _ReplyCount; };
			}

			property String^ Quality
			{
				String^ get() 
				{
					if (1 == _Quality)
					{
						return ref new String(L"转帖");
					}
					else if (2 == _Quality)
					{
						return ref new String(L"关注");
					}
					else if (10 == _Quality)
					{
						return ref new String(L"优秀");
					}
					else if (40 == _Quality)
					{
						return ref new String(L"精华");
					}
					else if (80 == _Quality)
					{
						return ref new String(L"酷贴");
					}
					else
					{
						return ref new String(L"");
					}
				};
			}

			property String^ RepliesAndViews
			{
				String^ get()
				{
					return (_ReplyCount.ToString() + L"/" + _ViewCount.ToString());
				}
			}

			property Windows::UI::Xaml::Visibility IsGlobalStick
			{
				Windows::UI::Xaml::Visibility get() 
				{ 
					if (_GlobalStick == 0)
					{
						return Windows::UI::Xaml::Visibility::Collapsed;
					}
					return Windows::UI::Xaml::Visibility::Visible;
				};
			}

			property Windows::UI::Xaml::Visibility IsForumStick
			{
				Windows::UI::Xaml::Visibility get()
				{
					if (_GlobalStick == 0 &&_ForumStick == 1)
					{
						return Windows::UI::Xaml::Visibility::Visible;
					}
					return Windows::UI::Xaml::Visibility::Collapsed;
				};
			}

			property Windows::UI::Xaml::Visibility IsGoodQuality
			{
				Windows::UI::Xaml::Visibility get()
				{
					if (_Quality == 0)
					{
						return Windows::UI::Xaml::Visibility::Collapsed;
					}
					return Windows::UI::Xaml::Visibility::Visible;
				};
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
				GetStringRepresentation() { return _ThreadTitle; };

		internal:
			ThreadItem(
				int32	ThreadId,
				String^ ThreadTitle,
				String^	PostUserName,
				int32	PostUserId,
				int32	HasAvatar,
				String^	AvatarTimeStamp,
				String^	LastReplyDate,
				int32	ViewCount,
				int32	ReplyCount,
				int32	GlobalStick,
				int32	ForumStick,
				int32	Quality);

		private:
			int32	_ThreadId;
			String^	_ThreadTitle;
			String^	_PostUserName;
			int32	_PostUserId;
			int32	_HasAvatar;
			String^	_AvatarTimeStamp;
			String^	_LastReplyDate;
			int32	_ViewCount;
			int32	_ReplyCount;
			int32	_GlobalStick;
			int32	_ForumStick;
			int32	_Quality;
		};


		//
		[Windows::UI::Xaml::Data::Bindable]
		public ref class ThreadListData sealed :
			public Windows::UI::Xaml::DependencyObject
		{
			typedef Platform::Collections::Vector<ThreadItem^> ThreadItemList;
		public:
			property Windows::Foundation::Collections::IObservableVector<ThreadItem^>^ ThreadList
			{
				Windows::Foundation::Collections::IObservableVector<ThreadItem^>^ get()
				{
					return _ThreadList;
				};
			}

			property String^ ForumName
			{
				String^ get()
				{
					return _ForumName;
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
			ThreadListData(int32 ForumId, String^ ForumName);

			task<bool>
				LoadData(int32 Page = 1);

			//task<void>
			//	Init();

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

			int32							_ForumId;
			String^							_ForumName;


			int32							_TimeStamp;
			int32							_PageCount;
			int32							_CurrentPage;

			ThreadItemList^					_ThreadList;
		};
	}
}