#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include <fstream>

using namespace std;

int cap[201][201];
vector<int> graf[2001];
int tata[201] = { 0 }, viz[202] = { 0 };
int n;

ifstream f("harta.in");
ofstream g("harta.out");

int BFS()
{
    queue<int> q;
    for(int i=0;i<201;i++)
    {
        tata[i]=0;viz[i]=0;
    }

    q.push(0);
    viz[0] = 1;
    tata[0] = -1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();
        if (u == 2 * n + 1)
            return 1;
        for (int i = 0; i < graf[u].size(); i++)
        {
            int v = graf[u][i];
            if (cap[u][v] > 0 && !viz[v])
            {
                tata[v] = u;
                viz[v] = 1;
                q.push(v);
            }
        }
    }
    return 0;
}

int Edmonds_Karp()
{
    int cmax = 0, cmin, u, v;
    while (BFS())
    {
        for (int i = 0; i < graf[2 * n + 1].size(); i++)
        {
            u = graf[2 * n + 1][i];
            if (cap[u][2 * n + 1] > 0 && viz[u])
            {
                cmin = cap[u][2 * n + 1];
                while (tata[u] != -1)
                {
                    v = tata[u];
                    cmin = min(cmin, cap[v][u]);
                    u = v;
                }
                cmax += cmin;
                u = graf[2 * n + 1][i];
                cap[u][2 * n + 1] -= cmin;
                cap[2 * n + 1][u] += cmin;
                while (tata[u] != -1)
                {
                    v = tata[u];
                    cap[v][u] -= cmin;
                    cap[u][v] += cmin;
                    u = v;
                }
            }
        }
    }
    return cmax;
}

int main()
{
    int x, y;
    f >> n;
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (i != j)
            {
                graf[i].push_back(j + n);
                graf[j + n].push_back(i);
                cap[i][j + n] = 1;
            }
    for (int i = 1; i <= n; i++)
    {
        f >> x >> y;
        graf[0].push_back(i);
        graf[i].push_back(0);
        cap[0][i] = x;
        graf[2 * n + 1].push_back(i + n);
        graf[i + n].push_back(2 * n + 1);
        cap[i + n][2 * n + 1] = y;
    }

    g << Edmonds_Karp() << "\n";

    for (int i = 1; i <= n; i++)
        for (int j = n + 1; j <= 2 * n; j++)
            if (cap[j][i] == 1)
                g << i << " " << j - n << "\n";
    return 0;
}
