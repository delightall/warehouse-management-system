#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "user_list.h"


// 创建一个空链表（只有一个头结点）
list create(void)
{
    node* p = malloc(sizeof(node));

    if(p == NULL)
    {
        perror("malloc error");
        return NULL;
    }

    p->next = NULL;

    list l = malloc(sizeof(list));
    
    if(l == NULL)
    {
        perror("malloc error");
        return NULL;
    }

    l->head = l->tail = p;
    l->size = 0;

    return l;
}


// 销毁链表（删除所有节点）
void destroy(list l)
{
    node* p;

    // 释放链表 l 的所有节点
    while(l->head != NULL)
    {
        p = l->head->next;
        free(l->head);
        l->head = p;
    }
    
    // 释放链表 l 结构体
    free(l);
}


// 清空链表（除了头节点，删除其他所有节点，因为头节点没有存放数据元素）
void clear(list l)
{
    node* p, *q;

    p = l->head->next;
    l->head->next = NULL;

    while(p != NULL)
    {
        q = p->next;
        free(p);
        p = q;
    }

    l->tail = l->head;
}


// 判空，时间复杂度为 O(1)
int empty(list l)
{
    return !(l->size);
}


// 求长度，时间复杂度为 O(1)
int size(list l)
{
	return l->size;
}


// 插入新节点（头插），时间复杂度为 O(1)，空间复杂度为 O(1)
void push_front(list l, user* data)
{
    node* p = malloc(sizeof(node));

    if(p == NULL)
    {
        perror("malloc error");
        return;
    }

    // 为新节点赋值
    p->data = *data;
    p->next = l->head->next;

    // 修改链表信息
    l->head->next = p;
    if(l->size == 0) l->tail = p;
    l->size++;
}


// 插入新节点（尾插），时间复杂度为 O(1)，空间复杂度为 O(1)
void push_back(list l, user* data)
{
    node* p = malloc(sizeof(node));

    if(p == NULL)
    {
        perror("malloc error");
        return;
    }

    p->data = *data;
    p->next = NULL;

    l->tail->next = p;
    l->tail = p;
    l->size++;
}


// 插入一个新节点（中插，即在任意位置插入），时间复杂度为 O(1)，空间复杂度为 O(1)
// 在 pos 指向的节点后面插入一个新节点
void insert(list l, node* pos, user* data)
{
    node* p = malloc(sizeof(node));

    if(p == NULL)
    {
        perror("malloc error");
        return;
    }

    p->data = *data;
    p->next = pos->next;
    
    pos->next = p;

    if(p->next == NULL) l->tail = p;
    l->size++;
}


// 从链表中删除一个节点（根据节点指针删除），时间复杂度为 O(1)，空间复杂度为 O(1)
// 删除 pos 指向节点的后继
void erase(list l, node* pos)
{
    node* p = pos->next;
    pos->next = p->next;
    free(p);

    if(pos->next == NULL) l->tail = pos;
    l->size--;
}


// 从链表中删除一个节点（根据节点数据域删除），时间复杂度为 O(n)，空间复杂度为 O(1)
int remove2(list l, char* uid)
{
    node* p = l->head, *q;

    while(p->next != NULL && strcmp(p->next->data.uid, uid) == 0)
        p = p->next;

    // 如果没有找到
    if(p->next == NULL) return 0;

    // 找到了
    q = p->next;
    p->next = q->next;
    free(q);

    if(p->next == NULL) l->tail = p;
    l->size--;

    return 1;
}


// 修改链表中某个节点的数据域
int update(list l, char* uid, user* new_value)
{
    node* p = l->head->next;

    while(p != NULL)
    {
        if(strcmp(p->next->data.uid, uid) == 0)
        {
            p->data = *new_value;
            return 1;
        }

        p = p->next;
    }
        
    return 0;
}


// 随机访问某个数据元素（即根据数据元素的位置进行访问），时间复杂度为 O(n)
user* at(list l, int pos)
{
    node* p = l->head->next;

    int i = 0;

    for(; i != pos; i++)
    {
        p = p->next;
    }

    return &(p->data);  
}


// 在链表中查找某个节点
user* find_uid(list l, char* uid, int* pos)
{
    node* p = l->head->next;

    if(pos != NULL) *pos = 0;

    while(p != NULL)
    {
        if(strcmp(p->data.uid, uid) == 0) return &(p->data);

        p = p->next;
        if(pos != NULL) (*pos)++;
    }

    return NULL;
}

user* find_name(list l, char* name, int* pos)
{
    node* p = l->head->next;

    if(pos != NULL) *pos = 0;

    while(p != NULL)
    {
        if(strcmp(p->data.name, name) == 0) return &(p->data);

        p = p->next;
        if(pos != NULL) (*pos)++;
    }

    return NULL;
}


user* find_phone(list l, char* phone, int* pos)
{
    node* p = l->head->next;

    if(pos != NULL) *pos = 0;

    while(p != NULL)
    {
        if(strcmp(p->data.phone_num, phone) == 0) return &(p->data);

        p = p->next;
        if(pos != NULL) (*pos)++;
    }

    return NULL;
}


user* find_card(list l, char* card, int* pos)
{
    node* p = l->head->next;

    if(pos != NULL) *pos = 0;

    while(p != NULL)
    {
        if(strcmp(p->data.id_card, card) == 0) return &(p->data);

        p = p->next;
        if(pos != NULL) (*pos)++;
    }

    return NULL;
}



// 遍历节点
// visit 为访问函数，用它实现对每个节点的具体访问操作
void traverse(list l, int(*visit)(user*))
{
    node* p = l->head->next;

    while(p != NULL)
    {
        if(visit(&(p->data)) == 0) break;

        p = p->next;
    }
}
