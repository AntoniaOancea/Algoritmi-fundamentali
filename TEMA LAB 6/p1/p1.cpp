#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;
ifstream f("maxflow.in");
ofstream g("maxflow.out");
vector<vector<int> > cap,cap_drum;
vector<int>tata,viz;
int n,m,t,s;


bool BFS()
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
        for(int i=0;i<cap_drum[u].size();i++)
       // for(auto v:cap_drum[u]) //pentru infoarena
        {
            int v=cap_drum[u][i];
            if(viz[v]==0 && cap[u][v]!=0)
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

int Edmonds_Karp()
{
    long cmax=0;
    while(BFS()==true) //cat timp mai exista un lant nevizitat
    {
        int u,v=t;
        int cmin=999999;
        while(v!=s)
        {
            u=tata[v];
            if(cap[u][v]<cmin)//cautam capacitatea minima din lant
                {cmin=cap[u][v];}
            v=tata[v];
        }
        v=t;
        while(v!=s)//parcurgem lantul
        {
            u=tata[v];
            cap[u][v]-=cmin;//scadem capacitatea min din cap fiecarei muchii din lant
            cap[v][u]+=cmin;//arcul e invers =>  scadem cap min
            v=tata[v];
        }
        cmax+=cmin;
    }
    return cmax;
}
int main()
{
    int u,v,z;
    f>>n>>m;//n noduri, m muchii
    t=n; //destinatie
    s=1; //sursa
    cap_drum.resize(n+1);
    tata.resize(n+1);
    cap.resize(n+1, vector<int>(n+1));
    for(int i=1; i<=m; i++)
    {
        f>>u>>v>>z;//o muchie de la u la v cu cap z
        cap_drum[u].push_back(v);
        cap_drum[v].push_back(u);
        cap[u][v]=z;
    }
    g << Edmonds_Karp();
    return 0;
}

