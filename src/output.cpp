#include "output.h"
#include <direct.h>
#include <io.h>

void Files_in_obj::make_New_file(int index) {
	string ts = "./output";
	if (0 !=  access(ts.data(), 0))
	{
		// if this folder not exist, create a new one.
		mkdir(ts.data());   // ���� 0 ��ʾ�����ɹ���-1 ��ʾʧ��
	}
	ts+="/rope_obj_" + to_string(index) + ".obj";
	if (!(obj_f = fopen(ts.data(), "w+"))) {
		cout << "openfail" << endl;
	};
}