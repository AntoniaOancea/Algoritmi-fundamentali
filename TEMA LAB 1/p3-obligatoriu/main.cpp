#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>
#include<queue>
using namespace std;
ifstream f ("f.in");
int viz[100],tata[100],fin[100];
bool verif(vector<vector<int> > la,int n)
{
    for(int i=0;i<n;i++)
        if(la[i].size()!=0)return 1;
    return 0;
}
void dfs(int x,vector<vector<int> > la2,vector<int> &s)
{
    viz[x]=1;
    for(int i=0;i<la2[x].size();i++)
    {
        int y=la2[x][i];
        if(viz[y]==0)
        {
            tata[y]=x;
            dfs(y,la2,s);
        }
        else
        {
            if(fin[y]==0)//daca y nu e finalizat inseamna ca e muchie de intoarcere
            {
                int v=x;
                while(v!=y)
                {
                    s.push_back(v);
                    v=tata[v];//parcurg pe vectorul de tati si adaug elem in vectorul s pentru a afla ciclul
                }

            s.push_back(y);
            s.push_back(x);
            }
        }
    }
    fin[x]=1;
}
int main()
{
    int x,y,n;
    f>>n;
    vector<int> grad_intern(n,0);
    vector<vector<int> > la(n+1);
    vector<vector<int> > la2(n+1);
    int ct=0;
    while(f>>x>>y)
    {
        ct++;
        la[y].push_back(x);
        la2[y].push_back(x);//am facut o copie pentru ca in sortarea topologica eu sterg din lista de adiacenta la
        grad_intern[x]++;
    }
    //for(int i=0;i<n;i++)
      //  cout<<grad_intern[i]<<" "<<la[i].size()<<endl;
    queue<int> vf;
    for(int i=0;i<n;i++)
        if(grad_intern[i]==0)
            vf.push(i);//adaug in coada elem cu gradul intern 0
    vector<int>ord;
    while(!vf.empty())
    {
        int i=vf.front();
        vf.pop();
        if(grad_intern[i]==0)//pt fiecare elem din coada sterg muchiile(practic il sterg din graf)
            {
                ord.push_back(i);
                for(int j=la[i].size()-1;j>=0;j--)
                {
                    int y=la[i][j];
                    grad_intern[y]--;
                    la[i].pop_back();
                    if(grad_intern[y]==0)//adaug noile vf cu grad intern 0 in coada
                        vf.push(y);
                }
            }
    }
    for(int i=0;i<n;i++)
        fin[i]=0;
    vector<int> s;
    if(ct==0)//daca nu exista muchii afisez direct varfurile
        for(int i=0;i<n;i++)
            cout<<i<<" ";
    else
        if(ord.size()!=n)//inseamna ca exista ciclu
            {
                cout<<"Nu se pot efectua toate cursurile"<<endl;
                for(int i=0;i<n;i++)
                    if(viz[i]==0)
                        dfs(i,la2,s);
                cout<<"Ciclu: ";
                for(int i=s.size()-1;i>=0;i--)
                    if(i!=s.size()-1 && s[i]==s[s.size()-1])
                {
                    cout<<s[i]<<" ";
                    break;
                }
                else
                {
                        cout<<s[i]<<" ";
                 }
            }
    else
        for(int i=0;i<n;i++)//nu avem ciclu si afisez ordonarea din sortarea topologica
            cout<<ord[i]<<" ";
    return 0;
}
