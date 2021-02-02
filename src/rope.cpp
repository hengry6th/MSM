#include <vector>
#include "mass.h"
#include "spring.h"
#include "rope.h"
//#include <Eigen/Core>

#define kd 0.00005

using namespace std;
//using namespace Eigen;

Rope::Rope(Eigen::RowVector2d start, Eigen::RowVector2d end, int node_num, float node_mass,
	float k, vector<int> pinned_nodes) {
	masses = vector<Mass*>(node_num);
	springs = vector<Spring*>(node_num - 1);
    mass_posi.resize(node_num, 2);
    spring_index.resize(node_num - 1, 3);
    
    Eigen::RowVector2d length = (end - start) / (node_num - 1);
	masses[0] = new Mass(0, start, node_mass, false);
    mass_posi(0, 0) = start.x();
    mass_posi(0, 1) = start.y();
    //mass_posi(0, 2) = 0.0;
	for (int i = 1; i < node_num; i++) {
		start += length;
		masses[i] = new Mass(i, start, node_mass, false);
        mass_posi(i, 0) = start.x();
        mass_posi(i, 1) = start.y();
        //mass_posi(i, 2) = 0.0;
		springs[i - 1] = new Spring(masses[i - 1], masses[i], k);
        spring_index(i - 1, 0) = i - 1;
        spring_index(i - 1, 1) = i;
        spring_index(i - 1, 2) = i;
	}
	for (auto& i : pinned_nodes) {
		masses[i]->pinned = true;
	}
}
void Rope::simulateEuler(float delta_t, Eigen::RowVector2d gravity) {
    for (auto& s : springs)
    {
        // TODO (Part 2): Use Hooke's law to calculate the force on a node
        // get force by Hook's law
        Eigen::RowVector2d l = s->m2->position - s->m1->position;
        Eigen::RowVector2d f = -(s->k) * l/l.norm() * (l.norm() - s->rest_length);

        s->m1->forces -= f;
        s->m2->forces += f;

    }
    for (auto& m : masses)
    {
        if (!m->pinned)
        {
            // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position
            // save last position;
            m->last_position = m->position;
            // update position with damp;
            Eigen::RowVector2d a = m->forces / m->mass + gravity;
            m->velocity += a * delta_t;
            m->velocity *= (1 - kd);
            m->position += m->velocity * delta_t;//+ 0.5 * a * delta_t * delta_t;
            mass_posi(m->id, 0) = m->position.x();
            mass_posi(m->id, 1) = m->position.y();
            double x = mass_posi(m->id, 0);
            double y = mass_posi(m->id, 1);
            double c = y;

        }
        // Reset all forces on each mass
        m->forces = Eigen::RowVector2d(0, 0);
    }
}
void Rope::simulateVerlet(float delta_t, Eigen::RowVector2d gravity) {
    for (auto& s : springs)
    {
        // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet £¨solving constraints)
        Mass* m1 = s->m1;
        Mass* m2 = s->m2;
        Eigen::RowVector2d l = m1->position - m2->position;
        double constraint = l.norm() - s->rest_length;
        Eigen::RowVector2d delt_s = constraint * l/l.norm();
        if (!m1->pinned) s->m1->position -= delt_s * m2->mass / (m1->mass + m2->mass);
        if (!m2->pinned) s->m2->position += delt_s * m1->mass / (m1->mass + m2->mass);
    }

    for (auto& m : masses)
    {
        if (!m->pinned)
        {
            Eigen::RowVector2d temp_position = m->position;
            // TODO (Part 3.1): Set the new position of the rope mass
            // update position with damp
            m->position = m->position + (1 - kd) * (m->position - m->last_position) + gravity * delta_t * delta_t;
            m->last_position = temp_position;
            mass_posi(m->id, 0) = m->position.x();
            mass_posi(m->id, 1) = m->position.y();
            // TODO (Part 4): Add global Verlet damping
        }
    }
}