target_sources( DemoDrawer PUBLIC
    "ColorGeneration/BouncingColorGenerator.h"
    "ColorGeneration/BouncingColorGenerator.cpp"
    "ColorGeneration/FilteredColorGenerator.h"
    "ColorGeneration/FilteredColorGenerator.cpp"
    "ColorGeneration/LowPassColorFilter.h"
    "ColorGeneration/LowPassColorFilter.cpp"
    "ColorGeneration/RandomColorGenerator.h"
    "ColorGeneration/RandomColorGenerator.cpp"
    "ColorGeneration/SingleColorGenerator.h"
    "ColorGeneration/SingleColorGenerator.cpp"
    "Drawing/IPointsTraverser.h"
    "Drawing/ChanceBasedDrawer.h"
    "Drawing/ChanceBasedDrawer.cpp"
    "Drawing/PointTraversal/ChanceBasedPointsTraverser.h"
    "Drawing/PointTraversal/ChanceBasedPointsTraverser.cpp"
    "Drawing/PointTraversal/Neighbour4PointsTraverser.h"
    "Drawing/PointTraversal/Neighbour4PointsTraverser.cpp"
    "Rendering/FileUtil.h"
    "Rendering/FileUtil.cpp"
    "Rendering/ShaderException.h"
    "Rendering/ShaderException.cpp"
    "Rendering/ShaderType.h"
    "Rendering/ShaderUtil.h"
    "Rendering/ShaderUtil.cpp"
    "Rendering/TexUtil.h"
    "Rendering/TexUtil.cpp"
    "Topologies/CroppedTopology.h"
    "Topologies/CroppedTopology.cpp"
    "Topologies/ThorusTopology.h"
    "Topologies/ThorusTopology.cpp"
    "Color.h"
    "ColorUtil.h"
    "ColorUtil.cpp"
    "Field.h"
    "IColorFilter.h"
    "IColorGenerator.h"
    "IContainer.h"
    "ContainerType.h"
    "QueueContainer.h"
    "QueueContainer.cpp"
    "StackContainer.h"
    "StackContainer.cpp"
    "IDrawer.h"
    "ITopology.h"
    "OutOfRangeException.h"
    "Point.h"
    "Point.cpp"
)
