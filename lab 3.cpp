//
//  main.cpp
//  lab 3
//
//  Created by 吴思扬 on 16/6/11.
//  Copyright © 2016年 吴思扬. All rights reserved.
//


#include<iostream>
#include<map>
#include<math.h>
#include<string>

using namespace std;

#define SIZE_ADDRESS 64


struct Page{
    long long int num;
    map<long long int, Page> data;
};

Page PAGE;

int ADDRESS = 0;

Page Init_page(int level_page, const long long int num_item_level,
               const int num_bit_last,const long long int num)
{
    Page page;
    page.num = num;
 
    if (level_page == 0)
    {
        long long int num_item_last;
        num_item_last = pow(2, num_bit_last);
        for (int i = 0; i < num_item_last; i++)
        {
            Page p;
            p.num = ADDRESS;
            page.data[i] = p;
            ADDRESS++;
        }
    }
    else if (level_page>0)
    {
        level_page--;
        for (int i = 0; i < num_item_level; i++)
        {
            Page p;
            p = Init_page(level_page, num_item_level, num_bit_last,i);
            page.data[i] = p;
        }
    }
    return page;
}



void Run(const int size_address,const long long int size_page_item,
         const long long int size_page,unsigned const long long int logic_address)
{
    int level_page = 0;
    int num_bit_offset = 0;
    int num_bit_all_num_page;
    int num_bit_level;
    long long int num_item_level;
    int num_bit_last;
    
    num_bit_offset = log10(size_page)/log10(2);
    num_bit_all_num_page = size_address - num_bit_offset;
    
   
    num_item_level = size_page / size_page_item;
    num_bit_level = log10(num_item_level) / log10(2);
    level_page = num_bit_all_num_page / num_bit_level;
    num_bit_last = num_bit_all_num_page%num_bit_level;
    
 
    PAGE = Init_page(level_page, num_item_level, num_bit_last,0);
 
    long long int offset = logic_address % size_page;
    long long int num_block;
    long long int num_all_page = logic_address / size_page;
    long long int last_address = num_all_page;
    long long int now_address[100];
    
    for (int i = 0; i < level_page; i++)
    {
        now_address[i] = last_address / pow(2, num_bit_all_num_page - (num_bit_level*(i+1)));
        last_address = last_address % (int)pow(2, num_bit_all_num_page - (num_bit_level*(i + 1)));
    }
    Page *page = &PAGE;
    for (int i = 0; i < level_page; i++)
    {
        page = &page->data[now_address[i]];
    }
    num_block = page->data[last_address].num;
    cout << "物理块号：" << num_block << endl << "块内偏移：" << offset << endl;
    
}

unsigned long long int _16_10(char num16[])
{
    unsigned long long int num10 = 0;
    float i = 0;
    for (int j = SIZE_ADDRESS/4-1; j>=0;j--)
    {
        if (num16[j] <= '9'&&num16[j] >= '0')
            num16[j] = num16[j] - 48;
        else if (num16[j] <= 'F'&&num16[j] >= 'A')
            num16[j] = num16[j] - 55;
        else if (num16[j] <= 'f'&&num16[j] >= 'a')
            num16[j] = num16[j] - 87;
    }
    for (int j = SIZE_ADDRESS / 4 - 1; j >= 0; j--)
    {
        long long int pow_16_i;
        pow_16_i = pow(16, i);
        num10 = num10 + (long long int)num16[j] * pow_16_i;
        i++;
    }
    return num10;
}

int main()
{
    long long int size_page_item;
    long long int size_page;
    char logic_address16[SIZE_ADDRESS/4+1];
    unsigned long long int logic_address10;
    cout << "输入页记录大小：" << endl;
    cin >> size_page_item;
    cout << "输入页大小：" << endl;
    cin >> size_page;
    cout << "请输入逻辑地址："<<SIZE_ADDRESS/4<<"位16进制" << endl;
    cin >> logic_address16;
    size_page = size_page * 1024;
    logic_address10 = _16_10(logic_address16);
    Run(SIZE_ADDRESS, size_page_item, size_page,logic_address10);
    
}