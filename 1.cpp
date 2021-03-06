#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <conio.h>


using namespace std;
#define MAXSIZE 1000
typedef struct SqList {//顺序表
    int x[MAXSIZE] = { 0 };
    int y[MAXSIZE] = { 0 };
    int length = 0;
}SqList;
bool ListInsert(SqList* L, int i, int x, int y) {//插入
    int k;
    if (L->length == MAXSIZE) {
        return false;
    }
    if (i<1 || i>L->length + 1) {
        return false;
    }
    if (i <= L->length) {
        for (k = L->length - 1; k > i - 1; k--) {
            L->x[k + 1] = L->x[k];
        }
    }
    L->x[i - 1] = x;
    L->y[i - 1] = y;
    L->length++;
    return true;
}


int main() {
    // 绘图窗口初始化
    initgraph(640, 480);

    // 在屏幕中央输出字符串
    RECT r = { 0, 0, 639, 479 };
    drawtext(_T("获取坐标数据中。。。"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    Sleep(3000);
    cleardevice();

    // 按任意键退出
    

    fstream fout("./log.txt", ios::out | ios::trunc);//清空文件内容
    SqList L;//建立顺序表
    int x;
    int y;
    int i = 1;
    int stop = 0;
    unsigned seed;  // Random generator seed
    // Use the time function to get a "seed” value for srand
    seed = time(0);
    srand(seed);
    while (1) {
        //scanf_s("%d%d%d", &x, &y, &stop);机器输入
        x = rand() %100 + 1;//用于模拟机器获取数据
        y = rand() % 100 + 1;
        if (i == 100) {//假定扫描100次
            stop = -1;
        }
        ListInsert(&L, i, x, y);//记录每次扫描后的坐标信息
        i++;
        if (stop == -1) {
            break;
        }
    }
    int k = 0;
    for (int j = i; j > 1; j--) {

        ofstream out("./log.txt", ios::app);//app表示每次操作前均定位到文件末尾
        if (out.fail()) {
            cout << "error\n";
        }
        out << "X: " << L.x[k];
        out << "Y:" << L.y[k] << endl;
        out.close();
        k++;
    }
    drawtext(_T("获取完成"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    Sleep(1000);
    closegraph();

    return 0;

}