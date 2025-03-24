target_sources( DemoDrawer 
    PUBLIC BouncingColorGenerator.h PRIVATE BouncingColorGenerator.cpp
    PUBLIC FilteredColorGenerator.h PRIVATE FilteredColorGenerator.cpp
    PUBLIC LowPassColorFilter.h PRIVATE LowPassColorFilter.cpp
    PUBLIC RandomColorGenerator.h PRIVATE RandomColorGenerator.cpp
    PUBLIC SingleColorGenerator.h PRIVATE SingleColorGenerator.cpp
)
