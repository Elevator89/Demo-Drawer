target_sources( DemoDrawer 
    PUBLIC "IPointPicker.h"
    PUBLIC "IPointPusher.h"
    PUBLIC "IPointsTraverser.h"
    PUBLIC "PointsTraverserDrawer.h" PRIVATE "PointsTraverserDrawer.cpp"
    PUBLIC "QueuePopWithChanceDrawer.h" PRIVATE "QueuePopWithChanceDrawer.cpp"
    PUBLIC "QueuePopWithChanceDrawer.h" PRIVATE "QueuePopWithChanceDrawer.cpp"
    PUBLIC "RandomDrawer.h" PRIVATE "RandomDrawer.cpp"
    PUBLIC "StackPopWithChanceDrawer.h" PRIVATE "StackPopWithChanceDrawer.cpp"
    PUBLIC "StackPushWithChanceDrawer.h" PRIVATE "StackPushWithChanceDrawer.cpp"
)

add_subdirectory( PointPicking )
add_subdirectory( PointPushing )
add_subdirectory( PointTraversal )
