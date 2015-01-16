#pragma once
using namespace Platform;
using namespace Windows::UI::Input;
using namespace Windows::UI::Xaml::Input;


namespace PEDIY
{
	namespace Common
	{
		ref class GestureRecognizerHandler sealed
		{

		public:
			GestureRecognizerHandler(
				Windows::UI::Xaml::UIElement^ elem);
			virtual ~GestureRecognizerHandler();

			void PointerPressed(Object^ sender, PointerRoutedEventArgs^ e);
			void PointerMoved(Object^ sender, PointerRoutedEventArgs^ e);
			void PointerReleased(Object^ sender, PointerRoutedEventArgs^ e);

			void CrossSliding(GestureRecognizer^ sender, CrossSlidingEventArgs^ args);

		private:
			Platform::WeakReference				_elem;
			Windows::Foundation::EventRegistrationToken _PointerPressedEventToken;
			Windows::Foundation::EventRegistrationToken _PointerMovedEventToken;
			Windows::Foundation::EventRegistrationToken _PointerReleasedEventToken;

			Windows::UI::Input::GestureRecognizer^ gr;

		};
	}
}

