#pragma once
#include<graphics.h>
#include"Findpath.h"
using namespace std;
class Show
{

	public:
		int w;
		int h;
		Show(int w, int h)
		{
			this->w = w;
			this->h = h;
		}

		void Show_back();
		void Show_obsandline();
		void Show_all();

};

