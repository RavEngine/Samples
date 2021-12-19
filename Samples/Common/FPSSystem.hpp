#pragma once
#include <RavEngine/GUI.hpp>
#include <RavEngine/CTTI.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/GetApp.hpp>

struct FPSSystem : public RavEngine::AutoCTTI {
    const std::string document, element;
    FPSSystem(const decltype(document)& document, const decltype(element)& element) : document(document), element(element){}
    
    inline void operator()(float, RavEngine::GUIComponent& gui) const {
        auto doc = gui.GetDocument(document);
        auto App = RavEngine::GetApp();
        gui.EnqueueUIUpdate([=]{
            doc->GetElementById(element)->SetInnerRML(RavEngine::StrFormat("TPS: {} <br /> FPS: {} ({} ms)",
                                                                           std::round(App->CurrentTPS()),
                                                                           std::round(App->GetRenderEngine().GetCurrentFPS()),
                                                                           std::round(App->GetRenderEngine().GetLastFrameTime())));
        });
    };
};
