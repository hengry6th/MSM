#include "mass.h"
#include "spring.h"
#include "rope.h"
#include "world.h"
#include <string>
#include <igl/opengl/glfw/Viewer.h>
#include <chrono>
#include <ratio>
#include <ctime>

Rope* rope;
World* world;
static int globalstep = 1;

std::string getCurrentSystemTime()
{
    auto tt = std::chrono::system_clock::to_time_t
    (std::chrono::system_clock::now());
    struct tm* ptm = localtime(&tt);
    char date[60] = { 0 };
    sprintf(date, "%d-%02d-%02d-%02d.%02d.%05d",
        (int)ptm->tm_year + 1900, (int)ptm->tm_mon + 1, (int)ptm->tm_mday,
        (int)ptm->tm_hour, (int)ptm->tm_min, (int)ptm->tm_sec);
    return std::string(date);
}

bool preDrawFunc(igl::opengl::glfw::Viewer& viewer)
{
    viewer.data().clear();
    string start_time = getCurrentSystemTime();
    auto start = std::chrono::high_resolution_clock::now();
    world->step_euler();
    auto end = std::chrono::high_resolution_clock::now();
    world->output_2_obj(globalstep);
    std::chrono::duration<double, std::ratio<1, 1>> duration_s(end - start);
    std::cout << "Time step " << globalstep++ << " start_time:" << start_time  << " time_cost: " << duration_s.count() << "ms" <<endl;
    for (auto& m : rope->get_masses()) viewer.data().add_points(m->position, Eigen::RowVector3d(0, 1, 0));
    for (auto& s : rope->get_springs()) viewer.data().add_edges(s->m1->position, s->m2->position, Eigen::RowVector3d(0, 1, 0));
    //viewer.data().set_mesh(rope->get_positions(), rope->get_index());

    return false;
}


int main() {
    std::string mshFile = std::string(RESOURCE) + "tet.msh";
    world = new World();
    world->set_dt(0.025);
    world->set_g(Eigen::RowVector2d(0, -1));
    rope = new Rope(Eigen::RowVector2d(0, 0), Eigen::RowVector2d(10, 0),
        3, 1, 100, vector<int>{0});
    world->set_rope(rope);
    // Plot the mesh
    igl::opengl::glfw::Viewer viewer;
    viewer.callback_pre_draw = &preDrawFunc;
    viewer.core().orthographic = false;
    viewer.core().camera_zoom *= 0.4;
    //viewer.data().set_mesh(rope->get_positions(), rope->get_index());
    viewer.data().point_size = 5;
    viewer.data().line_width = 2;
    viewer.launch();
    delete world;
    return 0;
}
