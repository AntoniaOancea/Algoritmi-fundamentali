#include<fstream>
#include<vector>
using namespace std;
ifstream f("disjoint.in");
ofstream g("disjoint.out");
vector<int>tata,h,reprezentanti;
int Find(int u)
{
    if (tata[u]==0)return u;
    tata[u]=Find(tata[u]);
    return tata[u];
}
void Union(int repU, int repV)
{

    if(repU==repV)return;
    else
        tata[repU]=repV;

}
int main()
{
    int n,m;
    f>>n>>m;
    reprezentanti.resize(n+1,0);
    tata.resize(n+1,0);
    h.resize(n+1,0);
    for(int i=0;i<m;i++)
    {
        int cod,x,y;
        f>>cod>>x>>y;
        int repU=Find(x);
        int repV=Find(y);
        if(cod==1)
        {
            Union(repU,repV);
            reprezentanti[repV]++;
            int ct=0;
            for(int i=1;i<=n;i++)
                ct+=reprezentanti[i];
            g<<"Numar de multimi: "<<n-ct<<endl;
        }
        else
        {
            if(repU==repV)
                g<<"DA\n";
            else
                g<<"NU\n";
        }
    }
    return 0;
}
