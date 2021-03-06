#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <graphics.h>
#include <conio.h>


using namespace std;
#define MAXSIZE 1000
typedef struct SqList {//˳���
    int x[MAXSIZE] = { 0 };
    int y[MAXSIZE] = { 0 };
    int length = 0;
}SqList;
bool ListInsert(SqList* L, int i, int x, int y) {//����
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
    // ��ͼ���ڳ�ʼ��
    initgraph(640, 480);

    // ����Ļ��������ַ���
    RECT r = { 0, 0, 639, 479 };
    drawtext(_T("��ȡ���������С�����"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    Sleep(3000);
    cleardevice();

    // ��������˳�
    

    fstream fout("./log.txt", ios::out | ios::trunc);//����ļ�����
    SqList L;//����˳���
    int x;
    int y;
    int i = 1;
    int stop = 0;
    unsigned seed;  // Random generator seed
    // Use the time function to get a "seed�� value for srand
    seed = time(0);
    srand(seed);
    while (1) {
        //scanf_s("%d%d%d", &x, &y, &stop);��������
        x = rand() %100 + 1;//����ģ�������ȡ����
        y = rand() % 100 + 1;
        if (i == 100) {//�ٶ�ɨ��100��
            stop = -1;
        }
        ListInsert(&L, i, x, y);//��¼ÿ��ɨ����������Ϣ
        i++;
        if (stop == -1) {
            break;
        }
    }
    int k = 0;
    for (int j = i; j > 1; j--) {

        ofstream out("./log.txt", ios::app);//app��ʾÿ�β���ǰ����λ���ļ�ĩβ
        if (out.fail()) {
            cout << "error\n";
        }
        out << "X: " << L.x[k];
        out << "Y:" << L.y[k] << endl;
        out.close();
        k++;
    }
    drawtext(_T("��ȡ���"), &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
    Sleep(1000);
    closegraph();

    return 0;

}