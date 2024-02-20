#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "materials_mgr.h"

#define MATERIALS_INFO_FILE "./materials_info.dat"

list2 ml;

// 借出物资
void lend_materials(void)
{
    materials m1;

    printf("请输入物资编号：\n");
    scanf("%s", m1.id);
    printf("请输入借出数量：\n");
    scanf("%ld", &m1.num);
    printf("请输入备注：\n");
    scanf("%s", m1.bei);

    push_back2(ml, &m1);

    FILE* fp = fopen(MATERIALS_INFO_FILE, "ab");

    if(fp == NULL)
    {
        perror("fopen fail");
        return;
    }

    fwrite(&m1, sizeof(m1), 1, fp);

    fclose(fp);
}


// 归还物资
void return_materials(void)
{
    char id[20];
    int pos;

    printf("请输入物资编号：\n");
    scanf("%s", id);

    materials* m1 = find2(ml, id, &pos);

    if(m1 == NULL) 
    {
        printf("物资不存在， 归还失败\n");
    }
    else
    {
        FILE* fp = fopen(materials_INFO_FILE, "r+b");

        m1->num = 0;

        if(fp == NULL)  
        {
            perror("fopen fail");
            exit(1);
        }

        fseek(fp, pos * sizeof(materials), SEEK_SET);
        fwrite(m1, sizeof(materials), 1, fp);
        fclose(fp);
        printf("物资归还成功\n");
    }
}


// 获取当前时间
void get_time(void)
{
    time_t timep; 
    struct tm *p; 
    char str[50] = "";

    time(&timep); 
    p = localtime(&timep);  //取得当地时间 
}
    

// 初始化物资借还记录链表
void init_ml(void)
{
    ml = create2();

    materials m2;

    FILE* fp = fopen(MATERIALS_INFO_FILE, "rb");

    if(fp == NULL)
    {
        perror("fopen fail!\n");
        exit(1);
    }

    while(fread(&m2, sizeof(m2), 1, fp) == 1)
    {
        push_back2(ml, &m2);
    }

    fclose(fp);
}


// 查看借出和归还物资记录
/* void show_msg()
{
    printf("*************");
    printf("借出记录\n");
    printf("物资编号：%s");
} */
