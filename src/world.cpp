
#include "world.h"

//container

//use semi-implicit Euler method
// to update vertex position 
void World::step_euler() {
	rope->simulateEuler(dt, gravity);
}

//use explicit Verlet method
// to update vertex position
void World::step_verlet() {
	rope->simulateVerlet(dt, gravity);
}
// set delta t for updating
void World::set_dt(double time_step) {
	dt = time_step;
}
const double World::get_dt() const {
	return dt;
}

// set gravity
const Eigen::RowVector2d& World::get_gravity() const {
	return gravity;
}
