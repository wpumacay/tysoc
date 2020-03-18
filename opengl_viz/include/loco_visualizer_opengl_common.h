#pragma once

#include <loco_data.h>
#include <visualizer/loco_visualizer_camera.h>
#include <visualizer/loco_visualizer_light.h>
#include <CEngine.h>

namespace loco {
namespace glviz {

    const float HFIELD_HEIGHT_BASE = 1.0f;

    std::unique_ptr<engine::CICamera> CreateCamera( TVizCamera* vizCameraRef );
    std::unique_ptr<engine::CILight> CreateLight( TVizLight* vizLightRef );
    std::unique_ptr<engine::CIRenderable> CreateRenderable( const TShapeData& data );
    std::unique_ptr<engine::CMesh> CreateMeshFromData( const std::vector<float>& vertices,
                                                       const std::vector<int>& indices );

}}