#include <iostream>
#include<fstream>
#include<vector>
#include<queue>

using namespace std;
ifstream f("cuplaj.in");
ofstream g ("cuplaj.out");
vector<vector<int> > la;
vector<vector<int> > cap;
vector<int> tata;
int s,t,n,m,e;
bool BFS()
{
    vector<int> viz(n+m+2);
    queue<int> q;
    q.push(s);
    viz[s] = 1;
    tata[s] = -1;
    while(!q.empty())
    {
        int u = q.front();
        q.pop();
        for(int i=0;i<la[u].size();i++)
        //for(auto v: la[u])
        {
            int v=la[u][i];
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
    long cmax = 0;
    while(BFS()==true)
    {
        int u, v, cmin = 999999;
        v=t;
        while(v != s)
        {
            u = tata[v];
            if(cap[u][v] < cmin)
                cmin = cap[u][v];
            v = tata[v];
        }
        v=t;
        while(v != s)
        {
            u = tata[v];
            cap[u][v] -= cmin;
            cap[v][u] += cmin;
            v = tata[v];
        }
        cmax += cmin;
    }
    return cmax;
}
int main()
{
    int x,y;
    f>>n>>m>>e;
    la.resize(n+m+2);
    tata.resize(n+m+2);
    cap.resize(n+m+2, vector<int>(n+m+2));
    for(int i=1; i<=e; i++)  // in stanga elem sunt de la 1 la n si in drepata de la n+1 pentru a le deosebi
        {
            f>>x>>y;
            la[x].push_back(y+n);
            la[y+n].push_back(x);
            cap[x][y+n]=1; //cap va fi 1 sa calculam fluxul maxim
        }
        s=0; // start
        t=m+n+1;     // end
        for(int i=1; i<=max(n,m); i++)
        {
            if(i<=n){
            la[s].push_back(i);
            la[i].push_back(s);
            cap[s][i]=1;}
            if(i<=m){
                la[i+n].push_back(t);
                la[t].push_back(i+n);
                cap[i+n][t]=1;
            }
        }
        g << Edmonds_Karp()<<"\n";//calculam fluxul maxim
        for(int i=1; i<=n; i++)// afisam muchiile care au ramas
            for(int j=n+1;j<=n+m; j++)
            {
                    if(cap[j][i]==1)
                     g<<i<<" "<<j-n<<"\n";
            }
    return 0;
}
