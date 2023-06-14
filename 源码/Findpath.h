#pragma once
#include"Map.h"
using namespace std;
class Findpath 
{
public:
	int w;
	int h;
	Map mymap;
	Findpath(int w, int h)
	{
		this->w = w;
		this->h = h;
		this->mymap.w = w;
		this->mymap.h = h;
	}
	unordered_set<int>pass_path;
	vector<Point>final_path;

	void Find();
	bool Isxline(Point);
	bool Isyline(Point);
	bool Isslash(Point);
};



