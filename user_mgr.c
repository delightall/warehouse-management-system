#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "user_list.h"
#include "md5.h"


list ul;

// 把用户信息写入文件中
int write_usermsg(user* u1, const char* pathname)
{
    FILE* fp = fopen(USER_INFO_FILE, "ab");

    if(fp == NULL)
    {
        perror("fopen fail");
        return 0;
    }

    fwrite(u1, sizeof(user), 1, fp);

    fclose(fp);

    return 1;
}



// 登录验证
void login_auth(void)
{
    char account[20], password[20], password_md5[32];

    printf("\n请登录\n");
    printf("请输入用户名：");
    scanf("%s", account);
    printf("请输入密码：");
    scanf("%s", password);

    md5_string(password, password_md5);

    user u1;
    int auth_flag = 0;

    FILE* fp = fopen(USER_INFO_FILE, "rb");

    if(fp == NULL)
    {
        perror("fopen fail");
        exit(1);
    }

    while(fread(&u1, sizeof(user), 1, fp) == 1)
    {
        if(!strcmp(account, u1.account) && !strcmp(password_md5, u1.password))
        {
            auth_flag = 1;
            break;
        }
    }

    fclose(fp);

    if(auth_flag)
    {
        printf("欢迎使用本系统！\n");
    }
    else
    {
        printf("用户名或密码错误，登录失败！\n");
        exit(1);
    }
}


// 更新系统用户的用户名和密码
void update_login(user root)
{
    printf("请输入用户名：");
    scanf("%s", root.account);
    printf("请输入密码：");
    scanf("%s", root.password);

    if(write_usermsg(&root, USER_INFO_FILE))
        printf("更新成功！\n");
}

int check_user_name(const char* account)
{
    int exist_flag = 0;
    user u1;
    FILE* fp = fopen(USER_INFO_FILE, "rb");

    if(fp == NULL)
    {
        perror("fopen fail");
        exit(1);
    }

    while(fread(&u1, sizeof(user), 1, fp) == 1)
    {
        if(strcmp(u1.name, account) == 0)
            {
                exist_flag = 1;
                break;
            }
    }

    fclose(fp);

    return !exist_flag;
}


// 手机号校验
int telephone(char* phone_num)
{
    int flag = 0, i;

    if(phone_num[0] != '1') return flag;

    for(i = 1; i < 11; i++)
    {
        if(phone_num[i] < '0' && phone_num[i] > '9')
            return flag;
    }

    return !flag;
}


// 初始化用户链表
void init_ul(void)
{
    ul = create();

    user u1;

    FILE* fp = fopen(USER_INFO_FILE, "rb");

    if(fp == NULL)
    {
        perror("fopen fail!\n");
        exit(1);
    }

    while(fread(&u1, sizeof(u1), 1, fp) == 1)
    {
        push_back(ul, &u1);
    }

    fclose(fp);
}



// 添加新用户
void add_user(void)
{
    user u1;

    while (1)
    {
        printf("请输入工号：\n");
        scanf("%s", u1.uid);

        strcpy(u1.account, u1.uid);

        if (check_user_name(u1.account))
            break;

        printf("\n用户名已存在，请重新输入！\n");
    }

    printf("请输入姓名：\n");
    scanf("%s", u1.name);

    printf("请输入性别：\n");
    scanf("%d", &u1.sex);

    while(1)
    {
        printf("请输入身份证号码：\n");
        scanf("%s", u1.id_card);

        if (!check_card(u1.id_card))
        {
            for (int i = 0; i < 6; i++)
            {
                u1.password[i] = u1.id_card[i + 12];
            }

            break;
        }

        printf("\n身份证号不合法，请重新输入！\n");
    }

    while(1)
    {
        printf("请输入手机号：\n");
        scanf("%s", u1.phone_num);

        if (telephone(u1.phone_num))
            break;
    
        printf("\n手机号不合法，请重新输入！\n");
    }

    u1.delete_flag = 0;
    u1.role = 2;

    push_back(ul, &u1);

    FILE* fp = fopen(USER_INFO_FILE, "ab");

    if(fp == NULL)
    {
        perror("fopen fail");
        exit(1);
    }

    fwrite(&u1, sizeof(u1), 1, fp);
    fclose(fp);

    printf("\n用户录入成功！\n");
}



// 身份证校验
int check_card(char* a)
{
    char* p = a;
    int i;

    if(strlen(a) == 18)
    {
        for(i=0; i<17; i++)
        {
            if(!(47 < a[i] && a[i] < 58))
                return 1;
        }                  

        if((47 < a[17] && a[17] <58) || (a[17] == 'x'))  //判断最后以为是否是x或者是数字
            {
                if(nian(p+6) == 1)
                    return 0;
            
            }

    }

    return 2;
}


int nian(char *p1)
{
   int bools=0;
   int count;
   int number;
   int year=0,month,day,sum,leap,i;
   for(i=3;i>=0;i--)    //将字符数组转换为数字
   {
       number=1;
       for(count=i;count>=0;count--)
       {
           number=number*10;
       }
       year+=(*p1-48)*number;
       p1++;
   }
   if((*p1-48)==0)
       month=(*(++p1)-48);

   else
       month=((*p1)-48)*10+(*(++p1)-48);

    p1++;
    if((*p1-48)==0)
       day=(*(++p1)-48);

    else
       day=((*p1)-48)*10+(*(++p1)-48);
    if((year%4==0&&year%100!=0)||(year%400==0))   //判断闰年
        leap=1;
    else
        leap=0;
    switch(month)
    {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12: if(day<32&&day>0) bools=1; break;
        case 4:
        case 6:
        case 9:
        case 11:if(day<31&&day>0) bools=1;break;
        case 2:
        if(leap==1)
          {
           if(day>0&&day<30) bools=1;
          }
        else
          {
           if(day<29&&day>0) bools=1;
          }
        break;
        default:bools=0;
    }
    return bools;
}


// 删除用户
void delete_user(void)
{   
    char uid[20];
    int pos;

    printf("请输入你想要删除的用户工号：");
    scanf("%s", uid);

    user* u1 = find_uid(ul, uid, &pos);

    if(u1 == NULL || u1->delete_flag == 1) 
    {
        printf("用户不存在， 删除失败");
    }
    else
    {
        u1->delete_flag = 1;
        FILE* fp = fopen(USER_INFO_FILE, "r+b");

        if(fp == NULL)  
        {
            perror("foenp fail");
            exit(1);
        }

        fseek(fp, pos * sizeof(user), SEEK_SET);
        fwrite(u1, sizeof(user), 1, fp);
        fclose(fp);
        printf("用户删除成功");
    }
}


// 修改用户信息
void update_user(void)
{
    user u1;
    char uid[20];
    int pos;

    printf("请输入需要修改的用户工号：\n");
    scanf("%s", uid);

    printf("请输入新的用户信息\n");
    printf("请输入工号：\n");
    scanf("%s", u1.uid);
    printf("请输入用户名：\n");
    scanf("%s", u1.account);
    printf("请输入密码：\n");
    scanf("%s", u1.password);
    printf("请输入姓名：\n");
    scanf("%s", u1.name);
    printf("请输入性别：\n");
    scanf("%d", &u1.sex);
    printf("请输入身份证号：\n");
    scanf("%s", u1.id_card);
    printf("请输入手机号：\n");
    scanf("%s", u1.phone_num);
    u1.delete_flag = 0;
    u1.role = 2;

    user* u2 = find_uid(ul, uid, &pos);

    if(u2 == NULL) 
    {
        printf("用户不存在， 修改失败");
    }
    else
    {
        FILE* fp = fopen(USER_INFO_FILE, "r+b");

        if(fp == NULL)  
        {
            perror("foenp fail");
            exit(1);
        }
        
        *u2 = u1;

        fseek(fp, pos * sizeof(user), SEEK_SET);
        fwrite(u2, sizeof(user), 1, fp);
        fclose(fp);
        printf("用户修改成功");
    }
}


// 展示用户信息
void show_user(user* u)
{
	if(!u->delete_flag)
    {
        printf("工号：%s\n", u->uid);
        printf("用户名：%s\n", u->account);
        printf("密码：%s\n", u->password);
        printf("姓名：%s\n", u->name);
        printf("性别：%s\n", u->sex ? "女" : "男");
        printf("身份证号：%s\n", u->id_card);
        printf("手机号：%s\n", u->phone_num);
    }
}

void inquire_user() 
{
	int tem;
	printf("请选择你想通过什么方式进行查找？（输入号码）\n");
	printf("1.通过工号进行查找\n");
	printf("2.通过姓名进行查找\n");
    printf("3.通过手机号进行查找\n");
    printf("4.通过身份证号进行查找\n");
	scanf("%d", &tem);
 
	if(tem == 1) 
    {
		uid_inquire();
	} 
    else if(tem == 2) 
    {
		name_inquire();
	} 
    else if(tem == 3) 
    {
		phone_inquire();
	} 
    else if(tem == 4) 
    {
		card_inquire();
	} 
    else
    {
		printf("号码输入错误，请重新输入");
	}
}


// 根据用户工号查询用户信息
void uid_inquire(void)
{
    char uid[20];
    int pos;

    printf("请输入工号：\n");
    scanf("%s", uid);

    user* u1 = find_uid(ul, uid, &pos);

    if(u1 == NULL) 
    {
        printf("用户不存在， 查找失败");
    }
    else
    {
        show_user(u1);
    }
}


// 根据用户姓名查询用户信息
void name_inquire(void)
{
    char name[20];
    int pos;

    printf("请输入姓名：\n");
    scanf("%s", name);

    user* u1 = find_name(ul, name, &pos);

    if(u1 == NULL) 
    {
        printf("用户不存在， 查找失败");
    }
    else
    {
        show_user(u1);
    }
}


// 根据用户手机号查询用户信息
void phone_inquire(void)
{
    char phone[20];
    int pos;

    printf("请输入手机号：\n");
    scanf("%s", phone);

    user* u1 = find_phone(ul, phone, &pos);

    if(u1 == NULL) 
    {
        printf("用户不存在， 查找失败");
    }
    else
    {
        show_user(u1);
    }
}


// 根据身份证号查询用户信息
void card_inquire(void)
{
    char card[20];
    int pos;

    printf("请输入身份证号：\n");
    scanf("%s", card);

    user* u1 = find_card(ul, card, &pos);

    if(u1 == NULL) 
    {
        printf("用户不存在， 查找失败");
    }
    else
    {
        show_user(u1);
    }
}


