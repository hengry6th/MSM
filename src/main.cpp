#include "mass.h"
#include "spring.h"
#include "rope.h"
#include "world.h"
#include <string>
#include <igl/opengl/glfw/Viewer.h>
#include <chrono>

Rope* rope;
World* world;
static int globalstep = 1;

bool preDrawFunc(igl::opengl::glfw::Viewer& viewer)
{
    viewer.data().clear();
    auto start = std::chrono::high_resolution_clock::now();
    world->step_euler();
    auto end = std::chrono::high_resolution_clock::now();
    auto seconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    std::cout << "Time step " << globalstep++ << " : " << seconds << "ms\n";
    for (auto& m : rope->get_masses()) viewer.data().add_points(m->position, Eigen::RowVector3d(0, 1, 0));
    for (auto& s : rope->get_springs()) viewer.data().add_edges(s->m1->position, s->m2->position, Eigen::RowVector3d(0, 1, 0));
    //viewer.data().set_mesh(rope->get_positions(), rope->get_index());

    return false;
}


int main() {
    std::string mshFile = std::string(RESOURCE) + "tet.msh";
    world = new World();
    world->set_dt(0.1);
    world->set_g(Eigen::RowVector2d(0, -1));
    rope = new Rope(Eigen::RowVector2d(0, 0), Eigen::RowVector2d(200, 0),
        3, 1, 100, vector<int>{0});
    world->set_rope(rope);
    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.callback_pre_draw = &preDrawFunc;
    viewer.core().orthographic = false;
    viewer.core().camera_zoom *= 0.4;
    //viewer.data().set_mesh(rope->get_positions(), rope->get_index());
    viewer.data().point_size = 3;
    viewer.core().align_camera_center(rope->get_positions(), rope->get_index());
    viewer.launch();
    delete world;
    return 0;
}
