#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define inf 10000000 
#define N 100 
int map[N][N], visit[N], dis[N];
char name[N][N];
char ms[N][500];
int n;
char username[16], password[16];
int flag = 0;      // 0未登录 1管理员 2用户 3退出 

void all_map()     //城市列表
{
    int i;
    printf("                        *城市列表*\n");
    printf("                        *|-----------*\n");
    for (i = 0; i < n; i++)
        printf("                        *|%d.%s\n", i, name[i]);
    printf("                        *|-----------*\n");
}

void ask(int v0, int s)
{
	int min, i, j, u, v;
    int tot = 0;
    int p[N], l[N], q[N], front = 0, tail = 0;
    int cur;

    for (i = 0; i < N; i++)
    {
        dis[i] = -1;
        p[i] = -1;
        l[i] = 0;
        visit[i] = 0;
    }

    q[tail++] = v0;
    visit[v0] = 1;

    while (front != tail)
    {
        cur = q[front++];
        if (cur == s)
            break;
        for (i = 0; i < n; i++)
        {
            if (!visit[i] && map[cur][i] && map[cur][i] != inf)
            {
                dis[i] = dis[cur] + 1;
                q[tail++] = i;
                visit[i] = 1;
                p[i] = cur;
            }
        }
    }

    for (i = s; p[i] != -1; i = p[i])
        l[tot++] = i;
    l[tot++] = v0;

    if (i != tot - 1)
        printf("                          可以到达!"); 
    else
        printf("                          不可到达!");
} 

void Dijkstra(int v0, int s) //迪杰斯特拉求最短路径，并输出路线
{
    int min, i, j, u, v;
    int p[N], l[N];
    for (i = 0; i < N; i++)
    {
        p[i] = -1;
        l[i] = 0;
        visit[i] = 0;
    }
    for (i = 0; i < n; i++)
    {
        dis[i] = map[v0][i];
        if (dis[i] < inf) //v0能直接到达，即上一站点为v0
            p[i] = v0;
    }

    visit[v0] = 1;

    for (i = 0; i < n; i++)
    {
        min = inf;
        for (j = 0; j < n; j++) //每次找出距离v0最近点
        {
            if (visit[j] == 0 && dis[j] < min)
            {
                min = dis[j];
                u = j;
            }
        }
        visit[u] = 1; //标记该点
        for (v = 0; v < n; v++)
        {
            if (visit[v] == 0 && dis[v] > dis[u] + map[u][v]) //通过最近点更新其他边
            {
                p[v] = u; //存储更新的边，即为路线
                dis[v] = dis[u] + map[u][v];
            }
        }
    }
    v = s;
    i = 1;
    while (p[v] != v0) //将路线存入栈中，正序输出
    {

        l[i++] = p[v];
        v = p[v];
    }
    printf("\n");
    u = i - 1;
    printf("                        *|路线为：\n");
    printf("                          %s--->", name[v0]);
    for (i = u; i >= 1; i--)
        printf("%s--->", name[l[i]]);
    printf("%s\n", name[s]);
    printf("                          最短路径长度为：%d 公里\n", dis[s]);
}

void bfs(int v0, int s) //广度优先遍历     最短中转次数 
{
    int min, i, j, u, v;
    int tot = 0;
    int p[N], l[N], q[N], front = 0, tail = 0;
    int cur;

    for (i = 0; i < N; i++)
    {
        dis[i] = -1;
        p[i] = -1;
        l[i] = 0;
        visit[i] = 0;
    }

    q[tail++] = v0;
    visit[v0] = 1;

    while (front != tail)
    {
        cur = q[front++];
        if (cur == s)
            break;
        for (i = 0; i < n; i++)
        {
            if (!visit[i] && map[cur][i] && map[cur][i] != inf)
            {
                dis[i] = dis[cur] + 1;
                q[tail++] = i;
                visit[i] = 1;
                p[i] = cur;
            }
        }
    }

    for (i = s; p[i] != -1; i = p[i])
        l[tot++] = i;
    l[tot++] = v0;

    printf("                        *|路线为：\n                         ");
    for (i = tot - 1; i >= 0; i--)
    {
        if (i != tot - 1)
            printf("--->");
        printf("%s", name[l[i]]);
    }
    printf("\n                         最短中转数为：%d 个\n", dis[s]);
}

void addmap()
{
    int i;
    int num, dis;
    printf("                        *|                      请输入城市名称：");
    scanf("%s", name[n]);
    printf("                        *|                      请输入城市描述：");
    scanf("%s", ms[n]);

    all_map();
    printf("       请依次输入与以上各大城市的距离，格式为：（曾是编号，距离），以-1 -1结束\n");
    for (i = 0; i < n; i++) // 全都设置为不可达
        map[i][n] = map[n][i] = inf;
    map[n][n] = 0;

    scanf("%d %d", &num, &dis);

    while (num != -1 && dis != -1)
    { // 依次输入景点和距离，设置距离
        scanf("%d %d", &num, &dis);
        if (num >= 0 && num < n)
            map[n][num] = map[num][n] = dis;
    }

    n++;

    printf("\n                          添加成功!\n");
}

void deletemap()
{
    int id, i;
    all_map();
    printf("                        *|                      请输入要删除的城市编号：");
    scanf("%d", &id);

    for (i = id; i < n; i++)
        strcpy(name[i], name[i + 1]);
    for (i = 0; i < n; i++)
    { // 将距离信息对应删除
        map[id][i] = map[id + 1][i];
        map[i][id] = map[i][id + 1];
    }

    n--;

    printf("\n                          删除成功！\n");
}

void save()//文件保存 
{
    int i, j, c = 0;
    FILE *f = fopen("map.txt", "w");
    fprintf(f, "%d\n", n);
    for (i = 0; i < n; i++)
        fprintf(f, "%s %s\n", name[i], ms[i]);
    fprintf(f, "\n");
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (map[i][j] && map[i][j] != inf)
                c++;
    fprintf(f, "%d\n", c);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            if (map[i][j] && map[i][j] != inf)
                fprintf(f, "%d %d %d\n", i, j, map[i][j]);
    fclose(f);

    f = fopen("admin.txt", "w");
    fprintf(f, "%s %s", username, password);
    fclose(f);
}

void load()
{
    int i, j, c, a, b, value;
    FILE *f = fopen("map.txt", "r");
    fscanf(f, "%d", &n);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            if (i == j)
                map[i][j] = 0;
            else
                map[i][j] = inf; //inf表示的是无穷大
        }
    for (i = 0; i < n; i++)
        fscanf(f, "%s %s", name[i], ms[i]);
    fscanf(f, "%d", &c);
    for (i = 0; i < c; i++)
    {
        fscanf(f, "%d %d %d", &a, &b, &value);
        map[a][b] = map[b][a] = value;
    }
    fclose(f);
    f = fopen("admin.txt", "r");
    fscanf(f, "%s %s", username, password);
    fclose(f);
}
void admin_nav()
{
    int choose;
    char pass[16];
    system("cls");

    while (1)
    {
        printf("                                                                           \n\n\n");
        printf("                        *|-----------------------------------------------------|*\n"); 
        printf("                        *|欢迎来到全国最短路查询系统！请输入您要进行的功能编号:|*\n");
        printf("                        *|                    管理员界面                       |*\n");
        printf("                        *|            1、添加城市  2、删除城市                 |*\n");
        printf("                        *|            3、修改密码  4、返回登陆界面             |*\n");
        printf("                        *|            5.退出系统                               |*\n");
        printf("                        *|-----------------------------------------------------|*\n");
        scanf("%d", &choose);
        if (choose == 1)
        {
            addmap();
        }
        else if (choose == 2)
        {
            deletemap();
        }
        else if (choose == 3)
        {
            printf("                        *|                      请输入您的新密码:");
            scanf("%s", pass);
            strcpy(password, pass);
        }
        else if (choose == 4)
        {
        	flag = 0;
            main();
            break;
        }
        else if (choose == 5)
        {
			break;	 
		} 
        save();
    }
}

void _dfs(int cur, int end, int visit[], int path[], int len, int limit)//深度优先遍历求所有简单路径 
{
    int i;
    if (limit >= 0)
    {
        visit[cur] = 1;
        path[len++] = cur;
        if (cur == end)
        {
            for (i = 0; i < len; i++)
            {
                if (i)
                    printf("--->");
                
                printf("%s", name[path[i]]);
				
            }
            printf("\n                          ");
        }
        else
        {
            for (i = 0; i < n; i++)
            {
                if (!visit[i] && map[cur][i] && map[cur][i] != inf)
                {
                    _dfs(i, end, visit, path, len, limit - 1);
                }
            }
        }
        visit[cur] = 0;
    }
}

void dfs(int start, int end, int limit)
{
    int visit[N] = {0};
    int path[N] = {0};
    int len = 0;
    _dfs(start, end, visit, path, len, limit);
}
void user_nav()
{
    int choose;
    int start, end;
    int id;
    system("cls");
	 
    while (1)
    {
        printf("\n\n\n");
        printf("                        *|-----------------------------------------------------|*\n");
        printf("                        *|欢迎来到全国最短路查询系统！请输入您要进行的功能编号:|*\n");
        printf("                        *|                   用户使用界面                      |*\n");
        printf("                        *|                1、查看所有城市                      |*\n");
        printf("                        *|                2、查询两个城市是否可以到达          |*\n");
        printf("                        *|                3、求最短路                          |*\n");
        printf("                        *|                4、求最短中转数                      |*\n");
        printf("                        *|                5、求两个城市之间所有的简单路径      |*\n");
        printf("                        *|                6、退出                              |*\n");
        printf("                        *|-----------------------------------------------------|*\n");
        scanf("%d", &choose);
        if (choose == 1)
        {
            all_map();
            printf("                          请输入您要查看的城市的编号：");
            scanf("%d", &id);
            if (id >= 0 && id < n)
                printf("\n");
                printf("                          %s %s", name[id], ms[id]);
        }
        else if (choose == 2)
        {
        	all_map();
            printf("\n\n");
            printf("                        *|请输入起点和终点城市编号：");
            scanf("%d %d", &start, &end);
            if (start >= 0 && start < n && end >= 0 && end < n && start != end)
        	ask(start, end);
		} 
        else if (choose == 3)
        {
            all_map();
            printf("\n\n");
            printf("                        *|请输入起点和终点城市编号：");
            scanf("%d %d", &start, &end);
            if (start >= 0 && start < n && end >= 0 && end < n && start != end)
                Dijkstra(start, end);
        }
        else if (choose == 4)
        {
            all_map();
            printf("\n\n");
            printf("                        *|请输入起点和终点城市编号：");
            scanf("%d %d", &start, &end);
            if (start >= 0 && start < n && end >= 0 && end < n && start != end)
                bfs(start, end);
        }
        else if (choose == 5)
        {
            all_map();
            printf("\n\n");
            printf("                        *|请输入起点和终点城市编号：");
            scanf("%d %d", &start, &end);

            if (start >= 0 && start < n && end >= 0 && end < n && start != end)
            {
                printf("                          中转数<=3的简单路径为：\n                          ");
                dfs(start, end, 3);
            }
        }
        else if (choose == 6)
        { 
            flag = 3;
            break;
        } 
    }
}

void login()
{
    int choose;
    char user[16], pass[16];
    system("cls");
    printf("                                                                           \n\n\n");
    printf("                        *|-----------------------------------------------------|*\n");
    printf("                        *|                       登陆界面                      |*\n");
    printf("                        *|                请问您想以什么身份登录：             |*\n");
    printf("                        *|                     1.管理员                        |*\n");
    printf("                        *|                     2.用户                          |*\n");
    printf("                        *|                     3.退出系统(输入!=1&&2即可)      |*\n");
    printf("                        *|-----------------------------------------------------|*\n");

    scanf("%d", &choose);
    if (choose == 1)
    {
        printf("                        *|                      请输入您的用户名:");
        scanf("%s", user);
        printf("                        *|                      请输入您的密码:");
        scanf("%s", pass);
        if (strcmp(user, username) == 0 && strcmp(pass, password) == 0)
        {
            printf("                                                登陆成功！    \n");
            flag = 1;
        }
        else
        {
            printf("                                        您的用户名或密码错误！请重新登陆！\n");
        } 
    }
    if (choose == 2)
        flag = 2;
    if (choose != 1 && choose != 2)
        flag = 3;
}

int main()
{
    load();
    save();
    while (flag == 0)
        login();
    if (flag == 1)
        admin_nav();
    else if (flag == 2)
        user_nav();
    else if (flag == 3)
        printf("                                                结束程序!\n");
}
