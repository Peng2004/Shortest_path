#pragma once
#include<vector>
#include <cstdlib> 
#include <ctime> 
#include <unordered_set>
#include"Point.h"

using namespace std;

class Map
{
public:
    vector<Point> obstacles;// 障碍物点集合
    unordered_set<int> is_obstacles;// 标记是否为障碍物的哈希表
    int w;// 地图宽度
    int h;// 地图高度
    int P2I(Point);// 将点转换为索引
    void GetRandObstacles();// 随机生成障碍物
    void GetIs_obstacles();// 将障碍物加入到is_obstacles集合中
};



