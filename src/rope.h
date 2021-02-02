#pragma once
#ifndef ROPE_H
#define ROpe_H

#include <vector>
#include "mass.h"
#include "spring.h"
#include <Eigen/Core>
#include <string>
#include "output.h"

using namespace std;

class Rope {

private:
	vector<Mass*> masses;
	vector<Spring*> springs;
	//used for libigl to draw
	//Eigen::MatrixXd mass_posi;
	//Eigen::MatrixXi spring_index;
public:
	Rope(vector<Mass*>& masses, vector<Spring*>& springs)
		:masses(masses), springs(springs) {};
	Rope(Eigen::RowVector2d start, Eigen::RowVector2d end, int node_num, float node_mass,
		float k, vector<int> pinned_nodes);
	void simulateVerlet(float delta_t, Eigen::RowVector2d gravity);
	void simulateEuler(float delta_t, Eigen::RowVector2d gravity);
	vector<Mass*>& get_masses() { return masses; }
	vector<Spring*>& get_springs() { return springs; }
	void output_2_obj(int step_index);
};
#endif // !ROPE_H
