#include <iostream>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;
ifstream f("f.in");
int viz[100],a[100][100],poz[100],dfs[100],rez[100];
bool cmp(int a,int b)
{
    return poz[a]<poz[b];
}
void DFS(int x,vector<vector<int> > la,vector<int> &rez)
{
    viz[x]=1;
    //cout<<x<<" ";
    rez.push_back(x);
    for(int i=0;i<la[x].size();i++)
        if(viz[la[x][i]]==0)
    {
        int y=la[x][i];
        DFS(y,la,rez);
    }
}
int main()
{
    int n,m;
    f>>n>>m;
    vector<int>viz(n+1);
    vector<vector<int> > la(n+1);
    for(int i=0;i<n;i++)
       {
           f>>dfs[i];
           poz[dfs[i]]=i;//retinem pozitia elem in dfs-ul dat pentru ordonarea din listele de adiacenta
       }

    for(int i=0;i<m;i++)
    {
        int x,y;
        f>>x>>y;
        la[x].push_back(y);
        la[y].push_back(x);
    }//am creat lista de adiacenta

    for(int i=1;i<=n;i++)
        sort(la[i].begin(),la[i].end(),cmp);//sortam lista de adiacenta

    vector<int> rez;
    DFS(1,la,rez);

    bool ok=true;
   // for(int i=0;i<n;i++)
     //   cout<<rez[i]<<" ";

    for(int i=0;i<n;i++)
        if(dfs[i]!=rez[i])
    {
        //cout<<i;
        ok=false;
        break;
    }
    cout<<int(ok);
    return 0;
}
