#ifndef materials_list2_H
#define materials_list2_H


#define materials_INFO_FILE "./materials_info.dat"


// 定义物资借还记录信息结构体
typedef struct 
{
    char uid[20];           // 用户工号
    char id[50];            // 物资编号
    char lend_time[20];     // 借出时间
    char return_time[20];   // 归还时间
    long num;               // 借出数量
    char bei[300];          // 备注
} materials;


// 声明链表节点结构体
typedef struct node2
{
    materials data;     // 数据域
    struct node2* next;  // 指针域
} node2;


// 声明链表信息结构体
typedef struct
{
    node2* head; // 链表头节点指针
    node2* tail; // 链表尾节点指针
    int size;   // 链表长度
} *list2;

extern list2 ml;

void init_ml(void);
void lend_materials(void);
void update_inventory(void);
list2 create2(void);
// void destroy2(list2 l);
// void clear2(list2 l);
// int empty2(list2 l);
// int size2(list2 l);
// void push_front2(list2 l, materials* data);
void push_back2(list2 l, materials* data);
// void insert2(list2 l, node2* pos, materials* data);
// void erase2(list2 l, node2* pos);
// int remove3(list2 l, char* id);
// int update2(list2 l, char* id, materials* new_value);
// materials* at2(list2 l, int pos);
materials* find2(list2 l, char* id, int* pos);
//void reverse(list2 l);
// void traverse2(list2 l, int(*visit)(materials*));

#endif