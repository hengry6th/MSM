#pragma once
#ifndef ROPE_H
#define ROpe_H

#include <vector>
#include "mass.h"
#include "spring.h"
#include <Eigen/Core>

using namespace std;

class Rope {

private:
	vector<Mass*> masses;
	vector<Spring*> springs;
	//used for libigl to draw
	Eigen::MatrixXd mass_posi;
	Eigen::MatrixXi spring_index;
public:
	Rope(vector<Mass*>& masses, vector<Spring*>& springs)
		:masses(masses), springs(springs) {};
	Rope(Eigen::RowVector2d start, Eigen::RowVector2d end, int node_num, float node_mass,
		float k, vector<int> pinned_nodes);
	void simulateVerlet(float delta_t, Eigen::RowVector2d gravity);
	void simulateEuler(float delta_t, Eigen::RowVector2d gravity);
	Eigen::MatrixXd& get_positions() {
		return mass_posi;
	}
	Eigen::MatrixXi& get_index() {
		return spring_index;
	}

	vector<Mass*>& get_masses() { return masses; }
	vector<Spring*>& get_springs() { return springs; };
};
#endif // !ROPE_H
