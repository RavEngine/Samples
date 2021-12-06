#include "AppInfo.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/Entity.hpp>
#include <RavEngine/SystemInfo.hpp>

using namespace RavEngine;
using namespace std;

static const char* GetRating(){
    // these ratings have absolutely nothing
    // to do with the specs being displayed
    const char* messages[] = {
        "Amazing!",
        "Could be better...",
        "Top notch!",
        "*Yawn*",
        "What is this?!",
        "I sure do like being inside this fancy computer",
        "Seal of approval!",
        "Drag racing champion!",
        "Tell your friends!",
    };
    return messages[rand() % sizeof(messages)/sizeof(messages[0])];
}

struct Level : public World{
    Level(){
        auto guientity = CreatePrototype<Entity>();
        auto& gui = guientity.EmplaceComponent<GUIComponent>();
        auto doc = gui.AddDocument("ui.rml");
        auto view = doc->GetElementById("view");
        
        
        DispatchAsync([=]{
            auto v = SystemInfo::OperatingSystemVersion();
            
            Vector<const char*> featuresStr;
            auto features = SystemInfo::GetSupportedGPUFeatures();
            if(features.DrawIndirect()){
                featuresStr.push_back("Draw Indirect");
            }
            if(features.DMA()){
                featuresStr.push_back("DMA");
            }
            if (features.HDRI10()){
                featuresStr.push_back("HDR10");
            }
            if (features.OcclusionQuery()){
                featuresStr.push_back("Occlusion Query");
            }
            if (features.Readback()){
                featuresStr.push_back("Readback");
            }
            if (features.HalfAttribute()){
                featuresStr.push_back("Half-width Attr");
            }
            if (features.Uint10Attribute()){
                featuresStr.push_back("U10 Attr");
            }
            std::ostringstream oss;
            std::copy(begin(featuresStr), end(featuresStr), std::ostream_iterator<decltype(featuresStr)::value_type>(oss, ", "));

            view->SetInnerRML(StrFormat(
R"(
Platform<br/>
{} {} {} v{}.{}.{}.{}<br/><br/>

Core<br/>
{}x {}<br/>
{} MB<br/>
<br/>

Graphics<br/>
{}<br/>
{} MB ({} used)<br/>
- {}<br/>
<br/>
{}
)",
                                        SystemInfo::OperatingSystemNameString(), SystemInfo::ArchitectureString(),  SystemInfo::IsMobile()?"Mobile":"Desktop", v.major,v.minor,v.patch,v.extra,
                                        
                                        SystemInfo::NumLogicalProcessors(),SystemInfo::CPUBrandString(),
                                        SystemInfo::SystemRAM(),
                                        
                                        SystemInfo::GPUBrandString(), SystemInfo::GPUVRAM(), SystemInfo::GPUVRAMinUse(),
                                        oss.str(),
                                        GetRating()
                          ));
        },1);
    }
};

struct SystemApp : public App{
    SystemApp() : App(APPNAME){}
    
    void OnStartup(int argc, char **argv) final{
        AddWorld(RavEngine::New<Level>());
        
        SetWindowTitle(StrFormat("{} | {}", APPNAME, App::GetRenderEngine().GetCurrentBackendName()).c_str());
    }
};

START_APP(SystemApp)
