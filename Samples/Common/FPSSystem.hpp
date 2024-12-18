#pragma once
#include <RavEngine/GUI.hpp>
#include <RavEngine/CTTI.hpp>
#include <RavEngine/Utilities.hpp>
#include <RavEngine/GetApp.hpp>
#include <RavEngine/RenderEngine.hpp>

struct FPSSystem : public RavEngine::AutoCTTI {
    const std::string document, element;
    FPSSystem(const decltype(document)& document, const decltype(element)& element) : document(document), element(element){}
    
    inline void operator()(RavEngine::GUIComponent& gui) const {
        auto doc = gui.GetDocument(document);
        auto App = RavEngine::GetApp();
        gui.EnqueueUIUpdate([=]{
            doc->GetElementById(element)->SetInnerRML(RavEngine::Format("TPS: {}",
                                                                           std::round(App->CurrentTPS())));
        });
    };
};
