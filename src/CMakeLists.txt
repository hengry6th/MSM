#file(GLOB SRCFILES "./*.cpp" "./*.h")
add_executable(LearnFEM main.cpp     "spring.h" "mass.h" "rope.cpp" "world.h" "world.cpp")
target_link_libraries(LearnFEM PUBLIC igl::core igl::opengl_glfw)
