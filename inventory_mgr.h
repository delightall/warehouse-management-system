#ifndef inventory_list1_H
#define inventory_list1_H


#define inventory_INFO_FILE "./inventory_info.dat"


// 定义库存物资信息结构体
typedef struct 
{
    char id[20];        // 物资编号
    char name[50];      // 物资名称
    long amount;        // 物资总数
    long margin;        // 当前余量
    int delete_flag;    // 是否已删除，0为未删除，1为已删除
} inventory;


// 声明链表节点结构体
typedef struct node1
{
    inventory data;      // 数据域
    struct node1* next;   // 指针域
} node1;


// 声明链表信息结构体
typedef struct
{
    node1* head; // 链表头节点指针
    node1* tail; // 链表尾节点指针
    int size;   // 链表长度
} *list1;

extern list1 vl;

list1 create1(void);
inventory* find1(list1 l, char* id, int* pos);
void push_back1(list1 l, inventory* data);
int remove1(list1 l, char* id);
void init_vl(void);
void add_inventory(void);
void delete_inventory(void);
void update_inventory(void);
void show_inventory(inventory* v);
void inquire_inventory(void);

#endif