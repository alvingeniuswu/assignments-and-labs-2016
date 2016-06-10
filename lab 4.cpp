//
//  main.cpp
//  lab 4
//
//

#include<iostream>

using namespace std;
void show_data(int level)
{
    for (int i = 0; i < level; i++)
    {
        for (int j = 0; j <= i; j++)
            printf("  ");
        printf("Indexes\n");
    }
    for (int j = 0; j <= level; j++)
        printf("  ");
    printf("Data\n");
}


void show_indoe()
{
    printf("indoe  ˝数据结构\n");
    printf("Mode\n");
    printf("Owner info\n");
    printf("Size\n");
    printf("Timestamps\n");
    printf("0-9 Direct Blocks\n");
    show_data(0);
    printf("10 Indirect Blocks\n");
    show_data(1);
    printf("11 Double Indirect\n");
    show_data(2);
    printf("12 Triple Indirect\n");
    show_data(3);
}

#define SIZEBLOCK 1024

class Cinode
{
public:
    Cinode() {}
    Cinode(const int size_block)
    {
        int num_blocks;
        int num_per_block;
        num_blocks = 0;
        num_per_block = size_block / 4;
        for (int i = 0; i < 10; i++, num_blocks++)
            Data_blocks[i] = num_blocks;
        Indirect_blocks = (int *)malloc(num_per_block * 4);
        for (int i = 0; i < num_per_block; i++, num_blocks++)
            *(Indirect_blocks + i) = num_blocks;
        num_level1 = num_blocks;
        Double_indirect = (int **)malloc(num_per_block * 4);
        for (int i = 0; i < num_per_block; i++)
        {
            *(Double_indirect + i) = (int *)malloc(num_per_block * 4);
            for (int j = 0; j < num_per_block; j++, num_blocks++)
                *(*(Double_indirect + i) + j) = num_blocks;
        }
        num_level2 = num_blocks;
        Triple_indirect = (int ***)malloc(num_per_block * 4);
        for (int i = 0; i < num_per_block; i++)
        {
            *(Triple_indirect + i) = (int **)malloc(num_per_block * 4);
            for (int j = 0; j < num_per_block; j++)
            {
                *(*(Triple_indirect + i) + j) = (int *)malloc(num_per_block * 4);
                for (int k = 0; k < num_per_block; k++, num_blocks++)
                {
                    *(*(*(Triple_indirect + i) + j) + k) = num_blocks;
                }
            }
        }
        num_level3 = num_blocks;
    }
    ~Cinode() {}
    
    int Num_block(const long long int size_file, const int size_block)
    {
        int num_index;
        int num_block;//当前块数
        int num_per_block;//每个索引存放的块数
        num_index = size_file / size_block;
        num_per_block = size_block / 4;
        if (num_index < 10 && num_index >= 0)
            num_block = Data_blocks[num_index];
        else if (num_index < num_level1&& num_index >= 0)
            num_block = *(Indirect_blocks + num_index - 10);
        else if (num_index < num_level2&& num_index >= 0)
            num_block = *(*(Double_indirect + (num_index - num_level1) / num_per_block) +
                          (num_index - num_level1) % num_per_block);
        else if (num_index < num_level3&& num_index >= 0)
            num_block = *(*(*(Triple_indirect + (num_index - num_level2) / (num_per_block *num_per_block)) + (num_index -num_level2) % (num_per_block *num_per_block) / num_per_block) + (num_index - num_level2) % num_per_block);
        else
            num_block = -1;
        return num_block;
    }
    
    int Offset(const long long int size_file, const int size_block)
    {
        int offset;
        offset = size_file%size_block;
        return offset;
    }
    
    void main(const int size_block)
    {
        long long int size_file;
        cout << "输入文件偏移量" << endl;
        cin >> size_file;
        cout << "物理块为：" << Num_block(size_file, size_block) << "偏移量为：" <<
        Offset(size_file, size_block) << endl;
    }
    
private:
    int Data_blocks[10];
    int * Indirect_blocks;
    int num_level1;
    int ** Double_indirect;
    int num_level2;
    int *** Triple_indirect;
    int num_level3;
};


int main()
{
    Cinode c(SIZEBLOCK);
    show_indoe();
    c.main(SIZEBLOCK);
}