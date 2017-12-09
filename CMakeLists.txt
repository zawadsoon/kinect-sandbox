# CMake entry point
cmake_minimum_required (VERSION 2.0)
project (KinectSandbox)

set(SOURCE_FILES main.cpp support/UtilsShader.cpp support/GLWindowUtils.cpp support/Kinect.cpp support/Cloud.cpp support/Settings.cpp)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(PkgConfig REQUIRED)

include_directories(${GLFW_INCLUDE_DIRS})
include_directories(vendor/libfreenect/include)
include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS} )

pkg_search_module(GLFW REQUIRED glfw3)

link_directories(freenect vendor/libfreenect/build/lib)

add_executable(KinectSandbox ${SOURCE_FILES})

target_link_libraries(KinectSandbox ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES} ${GLEW_LIBRARIES} ${GLFW_LIBRARIES} freenect)

add_custom_command(TARGET KinectSandbox PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/shaders $<TARGET_FILE_DIR:KinectSandbox>/shaders)