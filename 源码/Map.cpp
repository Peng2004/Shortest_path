#include "Map.h"

// 将点转换为索引
int Map::P2I(Point p)
{
int key = p.y * w + p.x;
return key;
}


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


void Map::GetIs_obstacles()
{
    for (int i = 0; i < obstacles.size(); i++)
    {
        is_obstacles.insert(P2I(obstacles[i]));
    }
}
