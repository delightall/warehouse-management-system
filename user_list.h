#ifndef USER_LIST_H
#define USER_LIST_H


#define USER_INFO_FILE "./user_info.dat"

// 声明用户结构体
typedef struct
{
    char uid[20];       // 用户工号
    char account[20];   // 用户名，普通用户用户名固定为工号
    char password[20];  // 用户密码,默认为身份证号的后六位
    char name[15];      // 用户姓名
    int sex;            // 用户性别（0为男，1为女）
    char id_card[18];   // 用户身份证号
    char phone_num[11]; // 用户手机号
    int delete_flag;    // 是否删除用户（0表示未删除，1表示已删除）
    int role;           // 1 表示系统管理员，2 表示普通用户
} user;


// 声明链表节点结构体
typedef struct node
{
    user data;          // 数据域
    struct node* next;  // 指针域
} node;


// 声明链表信息结构体
typedef struct
{
    node* head; // 链表头节点指针
    node* tail; // 链表尾节点指针
    int size;   // 链表长度
} *list;

extern list ul;


int write_usermsg(user* u1, const char* pathname);
void login_auth(void);
void update_login(user root);
int nian(char *p1);
int check_card(char* a);
int telephone(char* phone_num);
void init_ul(void);
void add_user(void);
void delete_user(void);
void update_user(void);
void show_user(user* u);
void inquire_user(void);
void uid_inquire(void);
void name_inquire(void);
void phone_inquire(void);
void card_inquire(void);
list create(void);
void destroy(list l);
void clear(list l);
int empty(list l);
int size(list l);
void push_front(list l, user* data);
void push_back(list l, user* data);
void insert(list l, node* pos, user* data);
void erase(list l, node* pos);
int remove2(list l, char* uid);
int update(list l, char* uid, user* new_value);
user* at(list l, int pos);
user* find_uid(list l, char* uid, int* pos);
user* find_name(list l, char* name, int* pos);
user* find_phone(list l, char* phone, int* pos);
user* find_card(list l, char* card, int* pos);
//void reverse(list l);
void traverse(list l, int(*visit)(user*));

#endif
