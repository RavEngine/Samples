#pragma once
#include <RavEngine/GUI.hpp>
#include <RavEngine/CTTI.hpp>
#include <RavEngine/Utilities.hpp>

struct FPSSystem : public RavEngine::AutoCTTI {
    const std::string document, element;
    FPSSystem(const decltype(document)& document, const decltype(element)& element) : document(document), element(element){}
    
    inline void Tick(float, Ref<RavEngine::GUIComponent> gui) {
        auto doc = gui->GetDocument(document);
        gui->EnqueueUIUpdate([=]{
            doc->GetElementById(element)->SetInnerRML(RavEngine::StrFormat("TPS: {} <br /> FPS: {} ({} ms)",
                                                                           std::round(RavEngine::App::CurrentTPS()),
                                                                           std::round(RavEngine::App::GetRenderEngine().GetCurrentFPS()),
                                                                           std::round(RavEngine::App::GetRenderEngine().GetLastFrameTime())));
        });
    };
};
