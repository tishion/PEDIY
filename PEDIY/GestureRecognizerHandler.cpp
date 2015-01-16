#include "pch.h"

using namespace PEDIY;
using namespace PEDIY::Common;

using namespace Platform::Collections;
using namespace Windows::ApplicationModel::Resources::Core;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::ViewManagement;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Interop;

GestureRecognizerHandler::GestureRecognizerHandler(
	Windows::UI::Xaml::UIElement^ elem) :
	_elem(elem)
{
	gr = ref new Windows::UI::Input::GestureRecognizer();

	gr->GestureSettings = GestureSettings::CrossSlide;
	gr->CrossSlideHorizontally = true;
	gr->CrossSliding += ref new TypedEventHandler<GestureRecognizer^, CrossSlidingEventArgs^>(this, &GestureRecognizerHandler::CrossSliding);

	_PointerPressedEventToken = elem->PointerPressed += ref new PointerEventHandler(this, &GestureRecognizerHandler::PointerPressed);
	_PointerMovedEventToken = elem->PointerMoved += ref new PointerEventHandler(this, &GestureRecognizerHandler::PointerMoved);
	_PointerReleasedEventToken = elem->PointerReleased += ref new PointerEventHandler(this, &GestureRecognizerHandler::PointerReleased);
}

PEDIY::Common::GestureRecognizerHandler::~GestureRecognizerHandler()
{
	Windows::UI::Xaml::Controls::Page^ elem = _elem.Resolve<Windows::UI::Xaml::Controls::Page>();
	if (elem)
	{
		elem->PointerPressed -= _PointerPressedEventToken;
		elem->PointerMoved -= _PointerMovedEventToken;
		elem->PointerReleased -= _PointerReleasedEventToken;
	}
}

void PEDIY::Common::GestureRecognizerHandler::PointerPressed(Object^ sender, PointerRoutedEventArgs^ e)
{
	gr->ProcessDownEvent(e->GetCurrentPoint(nullptr));
}

void PEDIY::Common::GestureRecognizerHandler::PointerMoved(Object^ sender, PointerRoutedEventArgs^ e)
{
	gr->ProcessMoveEvents(e->GetIntermediatePoints(nullptr));
}

void PEDIY::Common::GestureRecognizerHandler::PointerReleased(Object^ sender, PointerRoutedEventArgs^ e)
{
	gr->ProcessUpEvent(e->GetCurrentPoint(nullptr));
}

void PEDIY::Common::GestureRecognizerHandler::CrossSliding(GestureRecognizer^ sender, CrossSlidingEventArgs^ args)
{
	args->CrossSlidingState;
	args->Position.ToString();
}
