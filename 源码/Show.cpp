#include "Show.h"

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

void Show::Show_all()
{
    Show_back();
    Show_obsandline();
    system("pause");
    closegraph();
}

