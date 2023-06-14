# Shortest_Path

#### C++课后设计

#### 彭绮钰

+++

#### 整个系统由四个类构成：Point、Map、Findpath和Show。其中，Point类表示一个二维点的坐标，Map类表示地图信息和障碍物集合，Findpath类负责寻找最短路径，Show类用于显示地图和路径。

### Point类:

~~~c++
class Point
{
public:
    int x;
    int y;
    Point(int x, int y) {
        this->x = x;
        this->y = y;
    }

};
~~~

 **数据成员:**

x（横坐标）

y（纵坐标）

 **成员函数:**

构造函数：用于初始化Point对象的坐标。

 

### Map类:

~~~c++
class Map
{
public:
    vector<Point> obstacles;
    unordered_set<int> is_obstacles;
    int w;
    int h;
    int P2I(Point);
    void GetRandObstacles();
    void GetIs_obstacles();
};
~~~

 **数据成员:**

obstacles（障碍物点集合）：用vector<Point>存储障碍物点的坐标。

is_obstacles（标记是否为障碍物的哈希表）：使用unordered_set<int>存储障碍物点的索引。

w（地图宽度）

h（地图高度）

 **成员函数:**

P2I(Point p)：将Point对象转换为索引，使用公式key = p.y * w + p.x。

~~~c++
int Map::P2I(Point p)
{
int key = p.y * w + p.x;
return key;
}
~~~



GetRandObstacles()：根据地图尺寸，在合适的范围内生成随机的障碍物坐标，并存储到obstacles中。

~~~c++
void Map::GetRandObstacles()
{
    srand(time(0)); 
    const int num_points = (w*h)/3 ; 
    const int x_max = w; 
    const int y_max = h;
    for (int i = 0; i < num_points; i++)
    {
        int x = rand() % (x_max - 2) + 1;
        int y = rand() % (y_max - 2) + 1;
        obstacles.push_back(Point(x, y));
    }
}
~~~



GetIs_obstacles()：遍历obstacles，将障碍物点的索引存储到is_obstacles中。

 ~~~c++
 void Map::GetIs_obstacles()
 {
     for (int i = 0; i < obstacles.size(); i++)
     {
         is_obstacles.insert(P2I(obstacles[i]));
     }
 }
 
 ~~~



### Findpath类:

~~~c++
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
~~~



 **数据成员:**

w（地图宽度）

h（地图高度）

mymap（Map对象）

pass_path（经过的路径集合）：使用unordered_set<int>存储已经经过的路径点的索引。

final_path（最终路径）：用vector<Point>存储最短路径上的点坐标。

 **成员函数:**

Find()：在地图上寻找从起点(0,0)到终点(w-1,h-1)的最短路径。使用广度优先搜索算法进行遍历，通过判断是否可以向右移动、向下移动或斜向移动来确定下一个点，直到找到终点或无法继续搜索。

~~~c++
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
~~~



Isxline(Point now)：判断当前点是否可以向右移动，即判断右侧的点是否为障碍物并且未经过。

~~~c++
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
~~~



Isyline(Point now)：判断当前点是否可以向下移动，即判断下方的点是否为障碍物并且未经过。

~~~c++
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
~~~



Isslash(Point now)：判断当前点是否可以斜向移动，即判断右下方的点是否为障碍物并且未经过。

~~~c++
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
~~~



 

 ### Show类:

~~~c++
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
~~~



 **数据成员:**

w（地图宽度）

h（地图高度）

 **成员函数:**

Show_back()：使用图形库初始化画布，并绘制背景网格和边框。

~~~c++
void Show::Show_back()
{
    initgraph(w * 30, h * 30);
    setbkcolor(WHITE);
    cleardevice();
    setcolor(BLACK);
    rectangle(0, 0, w * 30, h * 30);
    setlinestyle(PS_SOLID, (int)w / 10);
    for (int i = 1; i < h; i++) {
        line(0, i * 30, w * 30, i * 30);
    }

    for (int i = 1; i < w; i++) {
        line(i * 30, 0, i * 30, h * 30);
    }
}
~~~



Show_obsandline()：创建Findpath对象，调用Find方法获取最短路径，并在画布上绘制障碍物和路径。

~~~c++
void Show::Show_obsandline()
{
    Findpath find(w,h);
    find.Find();
    setfillcolor(BLACK);
    int x = 0, y = 0;
    for (int i = 0; i < find.mymap.obstacles.size(); i++)
    {
        x = find.mymap.obstacles[i].x;
        y = find.mymap.obstacles[i].y;
        fillrectangle((x) * 30, (y) * 30, (x + 1) * 30, (y + 1) * 30);
    }
    setcolor(RED);
    setlinestyle(PS_SOLID, (int)w / 5);
    for (int i = 0; i < find.final_path.size() - 1; i++)
    {
        line((find.final_path[i].x) * 30 + 15, (find.final_path[i].y) * 30 + 15,
            (find.final_path[i + 1].x) * 30 + 15, (find.final_path[i + 1].y) * 30 + 15);
    }
}
~~~



Show_all()：调用Show_back()和Show_obsandline()，显示全部内容。

~~~c++
void Show::Show_all()
{
    Show_back();
    Show_obsandline();
    system("pause");
    closegraph();
}
~~~

