#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "user_list.h"
#include "inventory_mgr.h"
#include "md5.h"

void root_menu(void);
void user_menu(void);
void allwelcome(void);


static user root = {"", "admin", "123456", "", 0, "", "", 0, 1};   // 初始化管理员信息

int main()
{
    /* 
    测试 md5 模块
    char digest[33];

	md5_string(argv[1], digest);
	
	printf("%s\n", digest); 
    */
    
    md5_string(root.password, root.password);

    write_usermsg(&root, USER_INFO_FILE);

	init_ul();
	init_vl();

	allwelcome();
    return 0;
}


// 管理员界面
void root_menu(void) 
{
	while (1) 
    {
		printf("\n");
		printf("     欢迎来到仓库管理系统(管理员)   \n");
		printf("****************菜单*****************\n");
		printf("                                    \n");
		printf("           1.修改用户名和密码          \n");
		printf("           2.添加普通用户             \n");
		printf("           3.删除普通用户            \n");
		printf("           4.修改普通用户信息           \n");
		printf("           5.查询普通用户信息           \n");
		printf("           6.增加物资信息            \n");
		printf("           7.删除物资信息            \n");
		printf("           8.修改物资信息            \n");
		printf("           9.查询物资信息            \n");
        printf("           0.退出               \n");
		printf("                                    \n");
		printf("************************************\n");
		printf("      请选择你想要的功能(序号)      \n");
		int n;
		scanf("%d", &n);
 
		while (n < 0 || n > 9) {
			printf("输入指令有误，请重新输入：\n");
			scanf("%d", &n);
		}
 
		switch (n) {
            case 0:
                printf("\n谢谢使用，下次再见！\n");
                exit(0);

			case 1:
				update_login(root);
				break;
 
			case 2:
				add_user();
				break;
 
			case 3:
				delete_user();
				break;
 
			case 4:
				update_user();
				break;
 
			case 5:
				inquire_user();
				break;
 
			case 6:
				add_inventory();
				break;
 
			case 7:
				delete_inventory();
				break;
 
			case 8:
				update_inventory();
				break;
 
			case 9:
				inquire_inventory();
                break;
		}
	}
}


// 用户界面
void user_menu(void) 
{
	while (1) 
    {
		int uu = 0;
		printf("              用户你好              \n");
		printf("        欢迎来到仓库管理系统        \n");
		printf("         请选择你想要的功能         \n");
		printf("****************菜单****************\n");
		printf("                                    \n");
		printf("         1.修改登录密码        \n");
        printf("         2.查看个人信息        \n");
        printf("         3.查看借出和归还物资的记录        \n");
        printf("         4.借出物资        \n");
        printf("         5.归还物资        \n");
		printf("         6.退出          \n");
		printf("                                    \n");
		printf("************************************\n");
		printf("请输入序号：\n");
		scanf("%d", &uu);
 
		switch (uu) 
        {
			case 1: 
            {
				//see();
				break;
			}
 
			case 2: 
            {
				//exit(1);
				break;
			}
 
			default: 
            {
				printf("请输入正确的序号\n");
				user_menu();
				break;
			}
		}
	}
}


void allwelcome() 
{
	printf("请选择登录方式\n");
	printf("1、用户登录\n");
	printf("2、管理员登录\n");

	printf(":>");
	int t = 0;
	scanf("%d", &t);
 
	if (t == 1) 
    {
		login_auth();
		user_menu();
	} 
    else if (t == 2) 
    {
		login_auth();
		root_menu();
	} 
    else 
    {
		system("cls");
		printf("出错了！！！请重试\n");
		allwelcome();
	}
}


