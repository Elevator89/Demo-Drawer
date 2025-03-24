cmake_minimum_required( VERSION 3.20 )

project( DemoDrawer )

find_package( glfw3 3.4 REQUIRED )
find_package( OpenGL REQUIRED )

include_directories("glad/include")

if( MSVC )
    SET( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:mainCRTStartup" )
endif()

add_executable( DemoDrawer src/main.cpp "${CMAKE_SOURCE_DIR}/glad/src/gl.c" "${CMAKE_SOURCE_DIR}/glad/include/glad/gl.h" )

add_subdirectory( src )

target_link_libraries( DemoDrawer ${OPENGL_LIBRARIES} glfw )

function(add_file_copy_target targetName destDir)
    set(outputFileNames)
    foreach(srcFileName IN LISTS ARGN)
        get_filename_component(srcFileBaseName "${srcFileName}" NAME)
        add_custom_command( OUTPUT "${destDir}/${srcFileBaseName}" COMMAND "${CMAKE_COMMAND}" -E copy "${srcFileName}" "${destDir}" DEPENDS "${srcFileName}" )
        list(APPEND outputFileNames "${destDir}/${srcFileBaseName}")
    endforeach()

    add_custom_target("${targetName}" DEPENDS ${outputFileNames} )
endfunction()

add_file_copy_target(CopySahders
    "${CMAKE_BINARY_DIR}/shaders"
        "${CMAKE_SOURCE_DIR}/shaders/tex.vert"
        "${CMAKE_SOURCE_DIR}/shaders/tex.frag")

add_dependencies(DemoDrawer CopySahders)
