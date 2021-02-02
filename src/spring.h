
#pragma once
#ifndef SPRING_H
#define SPRING_H

#include "mass.h"

struct Spring {
	Spring(Mass* m1, Mass* m2, float k)
		:m1(m1), m2(m2), k(k), rest_length((m1->position - m2->position).norm()) {}

	//k stand for stiffness
	float k;
	double rest_length;

	Mass* m1;
	Mass* m2;
};

#endif // !SPRING_H