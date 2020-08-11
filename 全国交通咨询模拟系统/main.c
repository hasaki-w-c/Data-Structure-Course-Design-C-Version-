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
int flag = 0;      // 0δ��¼ 1����Ա 2�û� 3�˳� 

void all_map()     //�����б�
{
    int i;
    printf("                        *�����б�*\n");
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
        printf("                          ���Ե���!"); 
    else
        printf("                          ���ɵ���!");
} 

void Dijkstra(int v0, int s) //�Ͻ�˹���������·���������·��
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
        if (dis[i] < inf) //v0��ֱ�ӵ������һվ��Ϊv0
            p[i] = v0;
    }

    visit[v0] = 1;

    for (i = 0; i < n; i++)
    {
        min = inf;
        for (j = 0; j < n; j++) //ÿ���ҳ�����v0�����
        {
            if (visit[j] == 0 && dis[j] < min)
            {
                min = dis[j];
                u = j;
            }
        }
        visit[u] = 1; //��Ǹõ�
        for (v = 0; v < n; v++)
        {
            if (visit[v] == 0 && dis[v] > dis[u] + map[u][v]) //ͨ����������������
            {
                p[v] = u; //�洢���µıߣ���Ϊ·��
                dis[v] = dis[u] + map[u][v];
            }
        }
    }
    v = s;
    i = 1;
    while (p[v] != v0) //��·�ߴ���ջ�У��������
    {

        l[i++] = p[v];
        v = p[v];
    }
    printf("\n");
    u = i - 1;
    printf("                        *|·��Ϊ��\n");
    printf("                          %s--->", name[v0]);
    for (i = u; i >= 1; i--)
        printf("%s--->", name[l[i]]);
    printf("%s\n", name[s]);
    printf("                          ���·������Ϊ��%d ����\n", dis[s]);
}

void bfs(int v0, int s) //������ȱ���     �����ת���� 
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

    printf("                        *|·��Ϊ��\n                         ");
    for (i = tot - 1; i >= 0; i--)
    {
        if (i != tot - 1)
            printf("--->");
        printf("%s", name[l[i]]);
    }
    printf("\n                         �����ת��Ϊ��%d ��\n", dis[s]);
}

void addmap()
{
    int i;
    int num, dis;
    printf("                        *|                      ������������ƣ�");
    scanf("%s", name[n]);
    printf("                        *|                      ���������������");
    scanf("%s", ms[n]);

    all_map();
    printf("       ���������������ϸ�����еľ��룬��ʽΪ�������Ǳ�ţ����룩����-1 -1����\n");
    for (i = 0; i < n; i++) // ȫ������Ϊ���ɴ�
        map[i][n] = map[n][i] = inf;
    map[n][n] = 0;

    scanf("%d %d", &num, &dis);

    while (num != -1 && dis != -1)
    { // �������뾰��;��룬���þ���
        scanf("%d %d", &num, &dis);
        if (num >= 0 && num < n)
            map[n][num] = map[num][n] = dis;
    }

    n++;

    printf("\n                          ��ӳɹ�!\n");
}

void deletemap()
{
    int id, i;
    all_map();
    printf("                        *|                      ������Ҫɾ���ĳ��б�ţ�");
    scanf("%d", &id);

    for (i = id; i < n; i++)
        strcpy(name[i], name[i + 1]);
    for (i = 0; i < n; i++)
    { // ��������Ϣ��Ӧɾ��
        map[id][i] = map[id + 1][i];
        map[i][id] = map[i][id + 1];
    }

    n--;

    printf("\n                          ɾ���ɹ���\n");
}

void save()//�ļ����� 
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
                map[i][j] = inf; //inf��ʾ���������
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
        printf("                        *|��ӭ����ȫ�����·��ѯϵͳ����������Ҫ���еĹ��ܱ��:|*\n");
        printf("                        *|                    ����Ա����                       |*\n");
        printf("                        *|            1����ӳ���  2��ɾ������                 |*\n");
        printf("                        *|            3���޸�����  4�����ص�½����             |*\n");
        printf("                        *|            5.�˳�ϵͳ                               |*\n");
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
            printf("                        *|                      ����������������:");
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

void _dfs(int cur, int end, int visit[], int path[], int len, int limit)//������ȱ��������м�·�� 
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
        printf("                        *|��ӭ����ȫ�����·��ѯϵͳ����������Ҫ���еĹ��ܱ��:|*\n");
        printf("                        *|                   �û�ʹ�ý���                      |*\n");
        printf("                        *|                1���鿴���г���                      |*\n");
        printf("                        *|                2����ѯ���������Ƿ���Ե���          |*\n");
        printf("                        *|                3�������·                          |*\n");
        printf("                        *|                4���������ת��                      |*\n");
        printf("                        *|                5������������֮�����еļ�·��      |*\n");
        printf("                        *|                6���˳�                              |*\n");
        printf("                        *|-----------------------------------------------------|*\n");
        scanf("%d", &choose);
        if (choose == 1)
        {
            all_map();
            printf("                          ��������Ҫ�鿴�ĳ��еı�ţ�");
            scanf("%d", &id);
            if (id >= 0 && id < n)
                printf("\n");
                printf("                          %s %s", name[id], ms[id]);
        }
        else if (choose == 2)
        {
        	all_map();
            printf("\n\n");
            printf("                        *|�����������յ���б�ţ�");
            scanf("%d %d", &start, &end);
            if (start >= 0 && start < n && end >= 0 && end < n && start != end)
        	ask(start, end);
		} 
        else if (choose == 3)
        {
            all_map();
            printf("\n\n");
            printf("                        *|�����������յ���б�ţ�");
            scanf("%d %d", &start, &end);
            if (start >= 0 && start < n && end >= 0 && end < n && start != end)
                Dijkstra(start, end);
        }
        else if (choose == 4)
        {
            all_map();
            printf("\n\n");
            printf("                        *|�����������յ���б�ţ�");
            scanf("%d %d", &start, &end);
            if (start >= 0 && start < n && end >= 0 && end < n && start != end)
                bfs(start, end);
        }
        else if (choose == 5)
        {
            all_map();
            printf("\n\n");
            printf("                        *|�����������յ���б�ţ�");
            scanf("%d %d", &start, &end);

            if (start >= 0 && start < n && end >= 0 && end < n && start != end)
            {
                printf("                          ��ת��<=3�ļ�·��Ϊ��\n                          ");
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
    printf("                        *|                       ��½����                      |*\n");
    printf("                        *|                ����������ʲô��ݵ�¼��             |*\n");
    printf("                        *|                     1.����Ա                        |*\n");
    printf("                        *|                     2.�û�                          |*\n");
    printf("                        *|                     3.�˳�ϵͳ(����!=1&&2����)      |*\n");
    printf("                        *|-----------------------------------------------------|*\n");

    scanf("%d", &choose);
    if (choose == 1)
    {
        printf("                        *|                      �����������û���:");
        scanf("%s", user);
        printf("                        *|                      ��������������:");
        scanf("%s", pass);
        if (strcmp(user, username) == 0 && strcmp(pass, password) == 0)
        {
            printf("                                                ��½�ɹ���    \n");
            flag = 1;
        }
        else
        {
            printf("                                        �����û�����������������µ�½��\n");
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
        printf("                                                ��������!\n");
}
