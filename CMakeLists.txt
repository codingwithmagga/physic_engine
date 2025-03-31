cmake_minimum_required(VERSION 3.21)

project(
  "PhysicEngineWithGui"
  VERSION 0.1.0
  LANGUAGES CXX
)

add_subdirectory(libs/physic_engine)
add_subdirectory(libs/opengl_ui)

add_executable(opengl_test src/main.cpp)

target_link_libraries(
  opengl_test
  PRIVATE
	PhysicEngine::PhysicEngine
	OpenGLWrapper::OpenGLWrapper
)
