#include <InputLayer.h>
#include <Events.h>
#include <EventDispatcher.h>
#include <Input.h>

#include <imgui.h>

void InputLayer::onEvent(Event& e)
{
	EventDispatcher dispatcher(e);

	dispatcher.dispatch<KeyPressedEvent>([&](KeyPressedEvent& event) {
		if(!WantImGuiCaptureKeyboard()) Input::SetKey(event.getKeyCode(), true);
		return false;
	});

	dispatcher.dispatch<KeyReleasedEvent>([&](KeyReleasedEvent& event) {
		if(!WantImGuiCaptureKeyboard()) Input::SetKey(event.getKeyCode(), false);
		return false;
		});

	dispatcher.dispatch<MouseMovedEvent>([&](MouseMovedEvent& event) {
		if(!WantImGuiCaptureMouse()) Input::SetMousePos(event.getX(), event.getY());
		return false; 
	});

}

bool InputLayer::WantImGuiCaptureKeyboard()
{
	ImGuiIO& io = ImGui::GetIO();
	return io.WantCaptureKeyboard;
}

bool InputLayer::WantImGuiCaptureMouse()
{
	ImGuiIO& io = ImGui::GetIO();
	return io.WantCaptureMouse;
}

