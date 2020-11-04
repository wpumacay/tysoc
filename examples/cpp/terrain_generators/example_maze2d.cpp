#include <loco.h>

std::string PHYSICS_BACKEND = loco::config::physics::NONE;
std::string RENDERING_BACKEND = loco::config::rendering::GLVIZ_GLFW;

int main( int argc, char* argv[] )
{
    loco::InitUtils();

    if ( argc > 1 )
    {
        std::string choice_backend = argv[1];
        if ( choice_backend == "mujoco" )
            PHYSICS_BACKEND = loco::config::physics::MUJOCO;
        else if ( choice_backend == "bullet" )
            PHYSICS_BACKEND = loco::config::physics::BULLET;
        else if ( choice_backend == "dart" )
            PHYSICS_BACKEND = loco::config::physics::DART;
        else if ( choice_backend == "raisim" )
            PHYSICS_BACKEND = loco::config::physics::RAISIM;
        else if ( choice_backend == "none" )
            PHYSICS_BACKEND = loco::config::physics::NONE;
    }

    LOCO_TRACE( "Physics-Backend: {0}", PHYSICS_BACKEND );
    LOCO_TRACE( "Rendering-Backend: {0}", RENDERING_BACKEND );

    auto scenario = std::make_unique<loco::TScenario>();
    auto floor = scenario->AddSingleBody( std::make_unique<loco::primitives::TPlane>( "floor", 10.0f, 10.0f, loco::TVec3(), loco::TMat3() ) );
    const ssize_t maze2d_count_x = 5;
    const ssize_t maze2d_count_y = 5;
    auto maze_terrain_gen = scenario->AddTerrainGenerator( std::make_unique<loco::terrain::TMaze2dTerrainGenerator>( 
                                                                    "maze2d_gen0", scenario.get(), maze2d_count_x, maze2d_count_y,
                                                                    loco::TVec3( 0.5f, 0.5f, 0.5f ), loco::TVec2( 0.0f, 0.0f ) ) );
    static_cast<loco::terrain::TMaze2dTerrainGenerator*>( maze_terrain_gen )->GenerateLayout( "*xx**" 
                                                                                              "x**x*" 
                                                                                              "**x**" 
                                                                                              "*x***" 
                                                                                              "xxxx*" );

    auto runtime = std::make_unique<loco::TRuntime>( PHYSICS_BACKEND, RENDERING_BACKEND );
    auto simulation = runtime->CreateSimulation( scenario.get() );
    auto visualizer = runtime->CreateVisualizer( scenario.get() );

    floor->drawable()->ChangeTexture( "built_in_chessboard" );
    floor->drawable()->ChangeColor( { 0.3f, 0.5f, 0.7f } );

    while ( visualizer->IsActive() )
    {
        if ( visualizer->CheckSingleKeyPress( loco::Keys::KEY_ESCAPE ) )
            break;
        else if ( visualizer->CheckSingleKeyPress( loco::Keys::KEY_R ) )
            simulation->Reset();
        else if ( visualizer->CheckSingleKeyPress( loco::Keys::KEY_P ) )
            simulation->running() ? simulation->Pause() : simulation->Resume();

        simulation->Step( 1.0f / 60.0f );
        visualizer->Render();
    }

    runtime->DestroySimulation();
    runtime->DestroyVisualizer();

    return 0;
}