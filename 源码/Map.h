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
    vector<Point> obstacles;// �ϰ���㼯��
    unordered_set<int> is_obstacles;// ����Ƿ�Ϊ�ϰ���Ĺ�ϣ��
    int w;// ��ͼ���
    int h;// ��ͼ�߶�
    int P2I(Point);// ����ת��Ϊ����
    void GetRandObstacles();// ��������ϰ���
    void GetIs_obstacles();// ���ϰ�����뵽is_obstacles������
};



