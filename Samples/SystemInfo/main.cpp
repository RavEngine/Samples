#include "AppInfo.hpp"
#include <RavEngine/App.hpp>
#include <RavEngine/World.hpp>
#include <RavEngine/GameObject.hpp>
#include <RavEngine/SystemInfo.hpp>
#include <RavEngine/CameraComponent.hpp>

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
        "Seal of approval!",
        "Drag racing champion!",
        "Tell your friends!",
        "The latest and greatest, maybe!",
        "Fancy!",
    };
    return messages[rand() % sizeof(messages)/sizeof(messages[0])];
}

struct Level : public World{
    Level(){
        auto guientity = CreatePrototype<GameObject>();
        guientity.EmplaceComponent<CameraComponent>().SetActive(true);
        auto& gui = guientity.EmplaceComponent<GUIComponent>();
        auto doc = gui.AddDocument("ui.rml");
        auto view = doc->GetElementById("view");
        
        // get the name of the GPU
        // we have to embed every possible PCI device into the app
        // then search it for the ID

        // get PCI vendor and device IDs
        auto data = SystemInfo::GPUPCIData();

        // read the file containing all ids and strings
        auto filedata = GetApp()->GetResources().FileContentsAt<Vector<char>>("/uis/pci.ids");

        string_view allids(filedata.data(), filedata.size());

        stringstream stream;
        stream << std::hex << data.vendorID;
        // do we know about this vendor?
		auto vendorid_str = stream.str();
		size_t pos = 0;
		for(; pos < allids.size(); pos++){
			// check the first n bytes after pos
			if (strncmp(vendorid_str.data(), allids.data() + pos, vendorid_str.size()) == 0){
				break;
			}
			else{
				// read to the end of the line
				for( ; pos < allids.size() && allids[pos] != '\n'; pos++);
			}
		}
		
        //auto pos = allids.find(stream.str());
        string brandstring;
        if (pos == string_view::npos) {
            brandstring = "Unknown Vendor - Unknown GPU";
        }
        else {
            // get the vendor name
            size_t start =  pos + stream.str().size() + 1;  // + 1 tab
            size_t size = 0;
            for (size_t i = start; i < allids.size() && allids[i] != '\n'; size = i++ - start);
            string_view vendor(allids.data() + start,++size);
            brandstring += vendor;

            stream.str("");
            stream.clear();
            stream << std::hex << data.deviceID;

            // get the device name
            pos = allids.find(stream.str(), start + size);
            if (pos == string_view::npos) {
                brandstring += " - Unknown GPU";
            }
            else {
                start = pos + stream.str().size() + 1;  // + 1 tab
                for (size_t i = start; i < allids.size() && allids[i] != '\n'; size = i++ - start);
                string_view device(allids.data() + start, ++size);
                brandstring += StrFormat(" - {}",device);
            }
        }
        
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
{} MB ({} MB used)<br/>
- {}<br/>
<br/>
{}
)",
                                        SystemInfo::OperatingSystemNameString(), SystemInfo::ArchitectureString(),  SystemInfo::IsMobile()?"Mobile":"Desktop", v.major,v.minor,v.patch,v.extra,
                                        
                                        SystemInfo::NumLogicalProcessors(),SystemInfo::CPUBrandString(),
                                        SystemInfo::SystemRAM(),
                                        
                                        brandstring, SystemInfo::GPUVRAM(), SystemInfo::GPUVRAMinUse(),
                                        oss.str(),
                                        GetRating()
                          ));
        },1);
    }
};

struct SystemApp : public App{
    SystemApp() : App(APPNAME){}
    
    void OnStartup(int argc, char **argv) final{
        //SetMinTickTime(std::chrono::duration<double, std::milli>(33));  // limit to 30fps
        AddWorld(RavEngine::New<Level>());
        
        SetWindowTitle(StrFormat("{} | {}", APPNAME, App::GetRenderEngine().GetCurrentBackendName()).c_str());
    }
};

START_APP(SystemApp)
