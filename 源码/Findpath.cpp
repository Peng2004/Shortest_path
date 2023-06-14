#include "Findpath.h"

void Findpath::Find()
{
	mymap.GetRandObstacles();
	mymap.GetIs_obstacles();
	vector<vector<Point>>path;
	vector<vector<Point>>temp_path;
	vector<Point>start;
	start.push_back(Point(0, 0));
	path.push_back(start);
	bool isover = 1;
	while (isover)
	{
		temp_path = path;
		path.clear();
		for (int i = 0; i < temp_path.size(); i++)
		{
			Point now = temp_path[i].back();
			if (Isslash(now) == 1)
			{
				path.push_back(temp_path[i]);
				path[path.size() - 1].push_back(Point(now.x + 1, now.y + 1));
				pass_path.insert(mymap.P2I(Point(now.x + 1, now.y + 1)));
			}
			if (Isxline(now) == 1)
			{
				path.push_back(temp_path[i]);
				path[path.size() - 1].push_back(Point(now.x + 1, now.y));
				pass_path.insert(mymap.P2I(Point(now.x + 1, now.y)));
			}
			if (Isyline(now) == 1)
			{
				path.push_back(temp_path[i]);
				path[path.size() - 1].push_back(Point(now.x, now.y + 1));
				pass_path.insert(mymap.P2I(Point(now.x, now.y + 1)));
			}
		}
		for (int i = 0; i < path.size(); i++)
		{
			if (mymap.P2I(path[i].back()) == mymap.P2I(Point(w-1, h-1)))
			{
				final_path = path[i];
				isover = 0;;
			}
		}
	}
}
bool Findpath::Isslash(Point now)
{
	bool judge = 0;
	if (now.x != (w - 1)&&now.y!=(h-1))
	{
		unordered_set<int>::iterator iter1 = mymap.is_obstacles.find(mymap.P2I(Point(now.x + 1, now.y + 1)));
		unordered_set<int>::iterator iterx = mymap.is_obstacles.find(mymap.P2I(Point(now.x + 1, now.y)));
		unordered_set<int>::iterator itery = mymap.is_obstacles.find(mymap.P2I(Point(now.x, now.y + 1)));
		if(iter1== mymap.is_obstacles.end()&&(iterx == mymap.is_obstacles.end()|| itery == mymap.is_obstacles.end()))
		//if (iter1 == mymap.is_obstacles.end() )
		{ 
			unordered_set<int>::iterator iter2 = pass_path.find(mymap.P2I(Point(now.x + 1, now.y + 1)));
			{
				if (iter2 == pass_path.end())
				{
					judge = 1;
				}
			}
		}
	}
	return judge;
}
bool Findpath::Isxline(Point now)
{
	bool judge = 0;
	if (now.x != (w - 1))
	{
		unordered_set<int>::iterator iter1 = mymap.is_obstacles.find(mymap.P2I(Point(now.x + 1, now.y)));
		if (iter1 == mymap.is_obstacles.end())
		{
			unordered_set<int>::iterator iter2 = pass_path.find(mymap.P2I(Point(now.x + 1, now.y)));
			{
				if (iter2 == pass_path.end())
				{
					judge = 1;
				}
			}
		}
	}
	return judge;
}
bool Findpath::Isyline(Point now)
{
	bool judge = 0;
	if (now.y != (h - 1))
	{
		unordered_set<int>::iterator iter1 = mymap.is_obstacles.find(mymap.P2I(Point(now.x , now.y + 1)));
		if (iter1 == mymap.is_obstacles.end())
		{
			unordered_set<int>::iterator iter2 = pass_path.find(mymap.P2I(Point(now.x , now.y + 1)));
			{
				if (iter2 == pass_path.end())
				{
					judge = 1;
				}
			}
		}
	}
	return judge;
}
