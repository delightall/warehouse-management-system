#ifndef materials_list1_H
#define materials_list1_H


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
typedef struct node1
{
    materials data;     // 数据域
    struct node1* next;  // 指针域
} node1;


// 声明链表信息结构体
typedef struct
{
    node1* head; // 链表头节点指针
    node1* tail; // 链表尾节点指针
    int size;   // 链表长度
} *list1;

extern list1 l1;

void lend_materials(void);
void update_inventory(void);
list1 create(void);
void destroy(list1 l);
void clear(list1 l);
int empty(list1 l);
int size(list1 l);
void push_front(list1 l, materials* data);
void push_back(list1 l, materials* data);
void insert(list1 l, node1* pos, materials* data);
void erase(list1 l, node1* pos);
int remove2(list1 l, char* id);
int update(list1 l, char* id, materials* new_value);
materials* at(list1 l, int pos);
materials* find(list1 l, char* id, int* pos);
//void reverse(list1 l);
void traverse(list1 l, int(*visit)(materials*));

#endif