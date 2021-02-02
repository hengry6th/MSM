
#include "world.h"


void World::step_euler() {
	rope->simulateEuler(dt, gravity);
}
void World::step_verlet() {
	rope->simulateVerlet(dt, gravity);
}
void World::set_dt(double time_step) {
	dt = time_step;
}
const double World::get_dt() const {
	return dt;
}
const Eigen::RowVector2d& World::get_gravity() const {
	return gravity;
}
