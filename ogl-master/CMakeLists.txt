# CMake entry point
cmake_minimum_required (VERSION 3.0)
project (Tutorials)

find_package(OpenGL REQUIRED)


if( CMAKE_BINARY_DIR STREQUAL CMAKE_SOURCE_DIR )
    message( FATAL_ERROR "Please select another Build Directory ! (and give it a clever name, like bin_Visual2012_64bits/)" )
endif()
if( CMAKE_SOURCE_DIR MATCHES " " )
	message( "Your Source Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()
if( CMAKE_BINARY_DIR MATCHES " " )
	message( "Your Build Directory contains spaces. If you experience problems when compiling, this can be the cause." )
endif()


set(GLEW_INCLUDE_DIR "$ENV{GLEW_INCLUDE_DIR}" CACHE STRING "Path for glew headers.")
set(GLFW_INCLUDE_DIR "$ENV{GLFW_INCLUDE_DIR}" CACHE STRING "Path for glfw headers.")

include_directories(
	"${GLEW_INCLUDE_DIR}"
	"${GLFW_INCLUDE_DIR}"
	external/glm-0.9.7.1/
	.)


set(GLEW_LIBRARY "$ENV{GLEW_LIBRARY}" CACHE STRING "Path for glew library.")
set(GLFW_LIBRARY "$ENV{GLFW_LIBRARY}" CACHE STRING "Path for glfw library.")

link_directories(
    ${GLEW_LIBRARY}
    ${GLFW_LIBRARY})


set(ALL_LIBS ${OPENGL_LIBRARY})

option(IS_GLEW_STATIC "Linkage of GLEW is either static or dynamic" OFF)
option(IS_GLFW_STATIC "Linkage of GLFW is either static or dynamic" OFF)

if(IS_GLEW_STATIC)
	list(APPEND ALL_LIBS glew32s)
	add_definitions(-DGLEW_STATIC)
else(IS_GLEW_STATIC)
	list(APPEND ALL_LIBS glew32)
	# We assume that glew32.dll is already added to the "Path" environment variable.
endif()

if(IS_GLFW_STATIC)
	list(APPEND ALL_LIBS glfw3)
else(IS_GLEW_STATIC)
	list(APPEND ALL_LIBS glfw3dll)
	# We assume that glfw3.dll is already added to the "Path" environment variable.
endif()


# User playground
add_executable(
	playground 
	playground/App.cpp
	playground/InPuts.h
	playground/TEX.cpp
	playground/App.h
	playground/KeyBoard.cpp             
	playground/Aspects.cpp
	playground/KeyBoard.h
	playground/Shader.cpp
	playground/TEX.h
	playground/Aspects.hpp
	playground/Light.cpp
	playground/Shader.hpp
	playground/VAO.cpp
	playground/Camera.cpp
	playground/Light.h
	playground/VAO.hpp
	playground/Camera.h
	playground/Math.cpp
	playground/VBO.hpp
	playground/Debug.h
	playground/Math.h
	playground/wglext.h
	playground/FBO.cpp
	playground/Mouse.cpp
	playground/Window.cpp
	playground/FBO.h
	playground/Mouse.h
	playground/TangentSpace.cpp
	playground/Window.h
	playground/IBO.hpp
	playground/playground.cpp
	playground/TangentSpace.hpp
	common/objloader.cpp
	common/objloader.hpp
	common/texture.cpp
	common/texture.hpp
	common/vboindexer.cpp
	common/vboindexer.hpp
	playground/ShadowFragmentShader.fragmentshader
	playground/ShadowVertexShader.vertexshader
	playground/SimpleFragmentShader.fragmentshader
	playground/SimpleVertexShader.vertexshader
)
target_link_libraries(playground
	${ALL_LIBS}
)


SOURCE_GROUP(Common REGULAR_EXPRESSION ".*/common/.*" )
SOURCE_GROUP(Shaders REGULAR_EXPRESSION ".*shader$" )


configure_file("tutorial13_normal_mapping/cylinder.obj.in" "cylinder.obj" COPYONLY)
configure_file("tutorial13_normal_mapping/diffuse.DDS.in" "diffuse.DDS" COPYONLY)
configure_file("tutorial13_normal_mapping/specular.DDS.in" "specular.DDS" COPYONLY)
configure_file("tutorial13_normal_mapping/normal.bmp.in" "normal.bmp" COPYONLY)
