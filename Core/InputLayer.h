#pragma once
#include <Layer.h>

class InputLayer : public Layer 
{
public:
    void onEvent(Event& e) override;
    static bool WantImGuiCaptureKeyboard();
    static bool WantImGuiCaptureMouse();
};


