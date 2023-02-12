#include <iostream>
#include<vector>
#include<fstream>
#include<stack>
using namespace std;
ifstream f("ctc.in");
ofstream g("ctc.out");
int culoare[100],n;
// 0=alb, 1=gri, 2=negru
void DFS(int x,vector<vector<int> > la,stack<int> &s)
{
    culoare[x]=1;
    for(int i=0;i<la[x].size();i++)
        if(culoare[la[x][i]]==0)
    {
        int y=la[x][i];
        DFS(y,la,s);
    }
    culoare[x]=2;
    s.push(x);
}
void DFST(int x,vector<vector<int> > lat, int ct, int culoare[100],vector<vector<int> > &ctc)
{
    culoare[x]=1;
    for(int i=0;i<lat[x].size();i++)
        if(culoare[lat[x][i]]==0)
    {
        int y=lat[x][i];
        DFST(y,lat,ct,culoare,ctc);
    }
    culoare[x]=2;
    ctc[ct].push_back(x);
}
int main()
{
    int x,y,m;
    f>>n>>m;
    vector<vector<int> >la;
    la.resize(n+1);
    vector<vector<int> >lat;
    lat.resize(n+1);
    for(int i=0;i<m;i++)//am creat lista de adiacenta a grafului G si a lui Gt
        {
            f>>x>>y;
            la[x].push_back(y);
            lat[y].push_back(x);
        }

    stack<int> s;
    for(int i=1;i<=n;i++)
        if(culoare[i]==0)
            DFS(i,la,s); //facem dfs pe g si punem in stiva nodurile la finalizarea lor

    /*vector<int> viz;
    viz.resize(n+1);
    for(int i=0;i<=n;i++)
        viz[i]=0;*/

    int ct=0; //numarul de ctc
    for(int i=1;i<=n;i++)
      culoare[i]=0;
    vector<vector<int> > ctc(n);
    while(s.empty()==false)//cat timp mai avem elem in stiva
        {
            int v=s.top();
            s.pop();
            if(culoare[v]==0)
            {
                //cout<<v<<" ";
                ct++;
                DFST(v,lat,ct,culoare,ctc);//apelam dfst de nodul nevizitat
            }
        }
    g<<ct<<endl;
    for(int i=1;i<=ct;i++)
    {
        for(int j=0;j<ctc[i].size();j++)
            g<<ctc[i][j]<< " ";
        g<<endl;
    }
    return 0;
}
