#include <iostream>
#include<fstream>
#include<vector>
#include<map>
#include<queue>
using namespace std;
ifstream f("f.in");
int n;
bool dfs(vector<vector<int> > dislikes, vector<int> &grup, int v, int grp )
{
    if(grup[v]==-1)grup[v]=grp;
    else
        return grup[v] == grp;
    for(int x=0;x<dislikes[v].size();x++)
        if(!dfs(dislikes,grup,dislikes[v][x], 1-grp))
            return false;
    return true;
}
bool possibleBipartition(int n, vector<vector<int> >dislikes,vector<int> &grup)
{

    for(int i=1;i<=n;i++)
    {
        if(grup[i]==-1 && !dfs(dislikes,grup,i,0))
            return false;
    }
    return true;
}

int main()
{
    int x,y;
    f>>n;
    vector<vector<int> > dislikes;
    dislikes.resize(n+1);
    while(f>>x>>y)
    {

        dislikes[x].push_back(y);
        dislikes[y].push_back(x);
    }
    vector<int> grup(n+1,-1); //0-gr 1 , 1-gr 2
    if(possibleBipartition(n,dislikes,grup))
    {
        cout<<"true"<<endl;
        for(int i=1;i<=n;i++)
            if(grup[i]==0)
                cout<<i<<" ";
        cout<<endl;
        for(int i=1;i<=n;i++)
            if(grup[i]==1)
                cout<<i<<" ";
    }
    else
        cout<<"false";
    return 0;
}
