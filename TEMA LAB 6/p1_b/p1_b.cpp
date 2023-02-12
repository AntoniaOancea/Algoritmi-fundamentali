#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string.h>

using namespace std;

ifstream f("maxflow.in");
ofstream g("maxflow.out");

int n, m, s, t;
vector<vector<int> > cap1;
vector<int> tata;
vector<vector<int> > la1;
vector<vector<int> > cap2;
vector<vector<int> > la2;
vector<int>viz2;
bool BFS(int s, int t)
{
    vector<int> viz(n+1);
    queue<int> q;
    q.push(s);
    viz[s] = 1;
    tata[s] = -1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i=0;i<la2[u].size();i++)
        {
            int v=la2[u][i];
            if(viz[v]==0 && cap2[u][v]!=0)
            {
                tata[v] = u;
                if(v == t)
                    return true;
                viz[v] = 1;
                q.push(v);
            }
        }
    }
    return false;
}
void DFS(int s)
{
    viz2[s] = 1;
    for(int i=0;i<n;i++)
        if(cap2[s][i] && !viz2[i])
            DFS(i);
}
void Edmonds_Karp(int s,int t)
{
    la2=la1;
    cap2=cap1;
    while(BFS(s,t)==true)
    {
        int u,v,cmin=999999;
        v=t;
        while(v!=s)
        {
            u = tata[v];
            if(cap1[u][v]<cmin)
                cmin=cap2[u][v];
            v=tata[v];
        }
        v=t;
        while(v!=s)
        {
            u=tata[v];
            cap2[u][v]-= cmin;
            cap2[v][u]+= cmin;
            v=tata[v];
        }
    }
    viz2.resize(n+1);
    for(int i=0;i<=n;i++)
        viz2[i]=0;
    DFS(s);

    for(int i=0;i<n;i++)
        for(int j=0;j<n;j++)
            if(viz2[i] && !viz2[j] && cap1[i][j])
                g<<"("<<i<<","<<j<<") ";

}

int main()
{
    f>>n>>m;
    s=1;
    t=n;
    tata.resize(n+1);
    la1.resize(n+1);
    cap1.resize(n+1, vector<int>(n+1));
    la2.resize(n+1);
    cap2.resize(n+1, vector<int>(n+1));
    for(int i=1;i<=m;i++)
    {
        int x,y,z;
        f>>x>>y>>z;
        la1[x].push_back(y);
        la1[y].push_back(x);
        cap1[x][y]=z;
    }
    int sursa=1;
    for(int i=2;i<=n;i++)
        {
            g<<"De la sursa la varful "<<i<<" taiem muchiile: "<<endl;
            Edmonds_Karp(sursa, i);
            g<<endl;
        }
    return 0;
}
