target_sources( DemoDrawer 
    PUBLIC "Color.h"
    PUBLIC "ColorUtil.h" PRIVATE "ColorUtil.cpp"
    PUBLIC "Field.h"
    PUBLIC "IColorFilter.h"
    PUBLIC "IColorGenerator.h"
    PUBLIC "IDrawer.h"
    PUBLIC "ITopology.h"
    PUBLIC "OutOfRangeException.h"
    PUBLIC "Point.h" PRIVATE "Point.cpp"
)

add_subdirectory( Rendering )
add_subdirectory( Topologies )
add_subdirectory( Drawing )
add_subdirectory( ColorGeneration )
