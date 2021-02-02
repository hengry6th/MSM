#pragma once
#ifndef MASS_H
#define MASS_H

#include <Eigen/Core>


struct Mass {
	Mass(int id, Eigen::RowVector2d position, float mass, bool pinned)
		: id(id), start_position(position), position(position), last_position(position),
		mass(mass), pinned(pinned), velocity(Eigen::RowVector2d(0, 0)), forces(Eigen::RowVector2d(0, 0)) {}

	int id;
	float mass;
	bool pinned;

	Eigen::RowVector2d position;
	Eigen::RowVector2d start_position;
	Eigen::RowVector2d last_position;

	Eigen::RowVector2d velocity;
	Eigen::RowVector2d forces;
};

#endif // !MASS_H
