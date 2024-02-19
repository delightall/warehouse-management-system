#include <stdio.h>
#include <stdlib.h>
#include "inventory_mgr.h"
//#include "materials_mgr.h"

#define INVENTORY_INFO_FILE "./inventory_info.dat"


list1 vl;

// 增加物资
void add_inventory(void)
{
    inventory v1;
    //materials m1;

    printf("请输入物资编号：\n");
    scanf("%s", v1.id);
    printf("请输入物资名称：\n");
    scanf("%s", v1.name);
    printf("请输入物资总数：\n");
    scanf("%ld", &v1.amount);
    
    v1.margin = v1.amount; // 当前余量

    v1.delete_flag = 0;

    push_back1(vl, &v1);

    FILE* fp = fopen(INVENTORY_INFO_FILE, "ab");

    if(fp == NULL)
    {
        perror("fopen fail");
        exit(0);
    }

    fwrite(&v1, sizeof(v1), 1, fp);

    fclose(fp);
}


// 删除物资
void delete_inventory(void)
{
    char id[20];
    int pos;

    printf("请输入物资编号：\n");
    scanf("%s", id);

    inventory* v1 = find1(vl, id, &pos);

    if(v1 == NULL || v1->delete_flag == 1) 
    {
        printf("物资不存在， 删除失败");
    }
    else
    {
        v1->delete_flag = 1;
        remove1(vl, id);

        FILE* fp = fopen(inventory_INFO_FILE, "r+b");

        if(fp == NULL)  
        {
            perror("foenp fail");
            exit(1);
        }

        fseek(fp, pos * sizeof(inventory), SEEK_SET);
        fwrite(v1, sizeof(inventory), 1, fp);
        fclose(fp);
        printf("物资删除成功");
    }

}


// 修改物资
void update_inventory(void)
{
    inventory v1;
    char id[20];
    int pos;

    printf("请输入需要修改的物资编号：\n");
    scanf("%s", id);

    printf("请输入新的用户信息\n");
    printf("请输入物资编号：\n");
    scanf("%s", v1.id);
    printf("请输入物资名称：\n");
    scanf("%s", v1.name);
    printf("请输入物资总数：\n");
    scanf("%ld", &v1.amount);
    printf("请输入当前余量：\n");
    scanf("%ld", &v1.margin);
    v1.delete_flag = 0;
    
    printf("--------------\n");

    inventory* v2 = find1(vl, id, &pos);

    if(v2 == NULL) 
    {
        printf("物资不存在， 修改失败");
    }
    else
    {
        FILE* fp = fopen(INVENTORY_INFO_FILE, "r+b");

        if(fp == NULL)  
        {
            perror("fopen fail");
            exit(1);
        }
        
        *v2 = v1;

        fseek(fp, pos * sizeof(inventory), SEEK_SET);
        fwrite(v2, sizeof(inventory), 1, fp);
        fclose(fp);
        printf("物资修改成功");
    }
}


// 查询物资
void inquire_inventory(void)
{
    char id[20];
    int pos;

    printf("请输入你要查询物资的编号：\n");
    scanf("%s", id);

    inventory* v1 = find1(vl, id, &pos);

    if(v1 == NULL) 
    {
        printf("物资不存在， 查找失败");
    }
    else
    {
        show_inventory(v1);
    }
}


// 展示物资信息
void show_inventory(inventory* v)
{
	if(!v->delete_flag)
    {
        printf("编号 名称 总数 当前余量\n");
        printf("%s %s %ld  %ld\n", v->id, v->name, v->amount, v->margin);
    }	
    else
    {
        printf("物资不存在， 查找失败");
    }
}


// 初始化链表物资
void init_vl(void)
{
    vl = create1();

    inventory u1;

    FILE* fp = fopen(INVENTORY_INFO_FILE, "rb");

    if(fp == NULL)
    {
        perror("fopen fail!\n");
        exit(1);
    }

    while(fread(&u1, sizeof(u1), 1, fp) == 1)
    {
        push_back1(vl, &u1);
    }

    fclose(fp);
}

