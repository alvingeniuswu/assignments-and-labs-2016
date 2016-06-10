#include<iostream>
#include<stdlib.h>

using namespace std;



int *Available;//可用资源向量

int **Max;//最大需求矩阵

int **Allocation;//分配矩阵

int **Need;//需求矩阵

bool *Finish;

int *Work;

void Safe(const int p, const int r)
{
    int * P = (int *)malloc(sizeof(int)*p);
    int p_num = 0;
    bool has_n_w = true;
    while (has_n_w)
    {
        has_n_w = false;
        for (int i = 0; i < p; i++)
        {
            bool n_w = true;
            if (!*(Finish + i))
            {
                for (int j = 0; j < r; j++)
                {
                    if (*(*(Need + i) + j) > *(Work + j))
                    {
                        n_w = false;
                        break;
                    }
                }
                if (n_w)
                {
                    for (int j = 0; j < r; j++)
                        *(Work + j) = *(*(Allocation + i) + j) + *(Work + j);
                    *(Finish + i) = true;
                    *(P + p_num) = i + 1;
                    p_num++;
                    has_n_w = true;
                }
            }
        }
    }
    bool fin = true;
    for (int i = 0; i < p; i++)
    {
        if (!*(Finish + i))
        {
            fin = false;
            break;
        }
    }
    if (fin)
    {
        for (int i = 0; i < p; i++)
            cout << "  P" << *(P + i)<< endl;
    }
    else
    {
        cout << "死锁" << endl;
    }
    
}

void Init()
{
    int P, R;
    
    cout << "输入进程数量" << endl;
    cin >> P;
    cout << "输入资源数量" << endl;
    cin >> R;
    
    
    Available = (int *)malloc(sizeof(int)*P);
    Max = (int **)malloc(sizeof(int)*P);
    for (int i = 0; i < P; i++)
        *(Max + i) = (int *)malloc(sizeof(int)*R);
    Allocation = (int **)malloc(sizeof(int)*P);
    for (int i = 0; i < P; i++)
        *(Allocation + i) = (int *)malloc(sizeof(int)*R);
    Need = (int **)malloc(sizeof(int)*P);
    for (int i = 0; i < P; i++)
        *(Need + i) = (int *)malloc(sizeof(int)*R);
    Finish = (bool *)malloc(sizeof(int)*P);
    Work = (int *)malloc(sizeof(int)*P);
    
    for (int i = 0; i < R; i++)
    {
        cout << "输入第" << i + 1 << "个资源数量" << endl;
        cin >> *(Available + i);
    }
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            cout << "输入第" << i + 1 << "进程对第" << j + 1 << "种资源的最大需求" << endl;
            cin >> *(*(Max + i) + j);
        }
        
    }
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            cout << "输入第" << i + 1 << "进程对第" << j + 1 << "获得的资源" << endl;
            cin >> *(*(Allocation + i) + j);
        }
        
    }
    for (int i = 0; i < P; i++)
    {
        for (int j = 0; j < R; j++)
        {
            *(*(Need + i) + j) = *(*(Max + i) + j) - *(*(Allocation + i) + j);
        }
    }
    for (int i = 0; i < P; i++)
        *(Finish + i) = false;
    for (int i = 0; i < R; i++)
        *(Work + i) = *(Available + i);
    Safe(P, R);
}




int main()
{
    Init();
}