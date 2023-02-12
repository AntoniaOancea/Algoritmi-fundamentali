#include <iostream>
#include<fstream>
#include<cstring>
#include<vector>
#include<list>
using namespace std;
ifstream f("cuvinte.in");
ofstream g("cuvinte.out");
int k;
vector<int> tata(100,0);
vector<int> h (100,0);
int n;

//calculez distanta levenshtein
int levenshteinDistance (string a,string b)
{
    int olddiag,lastdiag;
    int lena=a.size();
    int lenb=b.size();
    int* col = new int[lena + 1];
    for(int i=1;i<=lena;i++)
        col[i]=i;
    for(int i=1;i<=lenb;i++)
    {
        col[0]=i;
        for(int j=1,lastdiag=i-1;j<=lena;j++)
        {
            olddiag=col[j];
            col[j]=min(min(col[j]+1,col[j-1]+1),lastdiag+(a[j-1]==b[i-1]? 0 : 1));
            lastdiag=olddiag;
        }
    }
    return col[lena];
}

int main()
{
    string cuv;
    cout<<"k=";
    cin>>k;
    vector<string> cuvinte(100);
    vector<vector<pair<int,int> > > minime(100); /// minime[i] va retine toate perechile de 2 cuvinte care au distanta levenshtein egala cu i
    while(f>>cuv)
    {
        n++;
        cuvinte[n]=cuv;
    }
    for(int i=1;i<=n;i++)
        tata[i]=i;
    int dist[100][100];
    int m=n;
    int a=-1,b=-1;
    int minim;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
            if(j<i)
                dist[i][j]=dist[j][i];
            else
                if(i==j)
                    dist[i][j]=0;
            else
               {
                   dist[i][j]=levenshteinDistance(cuvinte[i],cuvinte[j]);
                   minime[dist[i][j]].push_back(make_pair(i,j));
               }
    }
    int poz1=1;
    int poz2=0;
    while(m>=k)
    {
        a=-1;b=-1;

        while(minime[poz1].size()<=poz2 || tata[minime[poz1][poz2].first]==tata[minime[poz1][poz2].second])//caut urmatoarea perche prin vectorul de minime
        {
            if(minime[poz1].size()<=poz2)
                {poz2=0;poz1++;}
            else
                poz2++;
        }

        a=minime[poz1][poz2].first;
        b=minime[poz1][poz2].second;
        poz2++;

        m--;
        for(int i=1;i<=n;i++)//cei ce au acelasi tata cu b vor ajunge copiii tatalui lui a
            if(tata[i]==tata[b])
                tata[i]=tata[a];
    }

    //afisez cuvintele grupate in clasa in functie de parinte
    for(int i=1;i<=n;i++)
        if(tata[i]==i)
    {
        for(int j=1;j<=n;j++)
            if(tata[j]==i)
                cout<<cuvinte[j]<<" ";
        cout<<endl;
    }

    while(minime[poz1].size()<=poz2 || tata[minime[poz1][poz2].first]==tata[minime[poz1][poz2].second]) //caut urmatoarea pereche pentru a afla distanta dintre clase
        {
            if(minime[poz1].size()<=poz2)
                {poz2=0;poz1++;}
            else
                poz2++;
        }
    cout<<poz1;//distanta dintre clase
    return 0;
}
