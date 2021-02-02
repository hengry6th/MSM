#pragma once
#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <fstream>
#include <Eigen/Core>
#include <iostream>

using namespace std;

// file class, include file ptr and put Eigen::Vertex2d to  
class Files_in_obj {
private:
	FILE* obj_f;
public:
	void make_New_file(int index);
	void add_point(Eigen::RowVector2d v_position) {
		fprintf(obj_f, "v %lf %lf %lf\n", v_position.x(), v_position.y(), 0.0);
	};
	//.obj v index start from 1
	void add_edge(int v, int u) {
		fprintf(obj_f, "l %d %d\n", v + 1, u + 1);
	}
	void close_f() {
		fclose(obj_f);
	}
};


#endif // !OUTPUT_H
