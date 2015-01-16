#pragma once

using namespace concurrency;
using namespace Platform;

namespace PEDIY
{
	namespace Data
	{
		//
		[Windows::UI::Xaml::Data::Bindable]
		public ref class ForumItem sealed : 
			public Windows::UI::Xaml::Data::ICustomPropertyProvider
		{
		public:
			property String^ ForumGroupName
			{
				String^ get()
				{
					return _ForumGroupName;
				};
			}

			property String^ ForumName 
			{ 
				String^ get()
				{
					return _ForumName;
				};
			}

			property int32 ForumId 
			{ 
				int32 get()
				{
					return _ForumId;
				};
			}

			property int32 ForumImgId 
			{ 
				int32 get()
				{
					return _ForumImgId;
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

			virtual String^ 
				GetStringRepresentation() { return _ForumName; };

		internal:
			ForumItem(String^ ForumGroupName, String^ ForumName, int32 ForumId, int32 ForumImgId);

		private:
			String^		_ForumGroupName;
			String^		_ForumName;
			int32		_ForumId;
			int32		_ForumImgId;
		};

		[Windows::UI::Xaml::Data::Bindable]
		public ref class ForumGroupItem sealed :
			public Windows::UI::Xaml::Data::ICustomPropertyProvider
		{
			typedef Platform::Collections::Vector<ForumItem^> ForumItemList;
		public:
			property String^ ForumGroupName
			{ 
				String^ get()
				{
					return _ForumGroupName;
				};
			}
	
			property Windows::Foundation::Collections::IObservableVector<ForumItem^>^ ForumList
			{
				Windows::Foundation::Collections::IObservableVector<ForumItem^>^ get()
				{
					return _ForumList;
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

			virtual String^ 
				GetStringRepresentation() { return _ForumGroupName; };

		internal:
			ForumGroupItem(String^ ForumGroupName);
			

		private:
			String^				_ForumGroupName;
			ForumItemList^		_ForumList;
		};

		[Windows::UI::Xaml::Data::Bindable]
		public ref class HomeData sealed :
			public Windows::UI::Xaml::DependencyObject
		{
			typedef Platform::Collections::Vector<ForumGroupItem^> ForumGroupItemList;
		public:
			property Windows::Foundation::Collections::IObservableVector<ForumGroupItem^>^ ForumGroupList
			{
				Windows::Foundation::Collections::IObservableVector<ForumGroupItem^>^ get()
				{
					return _ForumGroupList;
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
			HomeData();

			task<bool>
				LoadData();

			//task<void>
			//	Init();

			void
				GetHomePageData();

			//task<ForumGroupItem^>
			//	GetForumGroupItem(String^ Name);

			//task<ForumItem^> 
			//	GetForumItem(int32 Id);

		private:
			//task_completion_event<void>						_loadCompletionEvent;
			static Windows::UI::Xaml::DependencyProperty^	_DataLoadDone;
			ForumGroupItemList^								_ForumGroupList;
		};
	}
}