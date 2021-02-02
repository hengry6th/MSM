
#pragma once
#ifndef WORLD
#define WORLD
#include "rope.h"

class World {
private:
	double dt;
	Eigen::RowVector2d gravity;
	Rope* rope;
public:
	World():dt(0.025), gravity(Eigen::RowVector2d(0, 0)){}
	World(Rope* rope) : rope(rope){}
	~World() {
		delete rope;
	};
	void set_rope(Rope* rope_in) { rope = rope_in; }
	void step_euler();
	void step_verlet();
	void set_dt(double time_step);
	void set_g(Eigen::RowVector2d g) { gravity = g; }
	const double get_dt() const;
	const Eigen::RowVector2d& get_gravity() const;

};

#endif // !WORLD
