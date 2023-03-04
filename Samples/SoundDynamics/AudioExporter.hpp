#pragma once
#include <RavEngine/Ref.hpp>
#include <RavEngine/Filesystem.hpp>

namespace RavEngine {
class AudioAsset;

struct AudioExporter{
    /**
     Write an AudioAsset to disk in one-shot as a wav file
     @param asset the asset to write
     @param destination where to write it
     */
    static void ExportWavOneShot(Ref<AudioAsset> asset, const Filesystem::Path& destination);
};

}
