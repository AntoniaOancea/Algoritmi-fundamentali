#include <iostream>
#include<vector>
#include<queue>
using namespace std;
typedef pair<int,double> pi;
typedef pair<double,int> pi1;
/*typedef pair<int,double> pi;
typedef pair<double,int> pi1;
class Solution {
public:
    double maxProbability(int n, vector<vector<int> >& edges, vector<double>& succProb, int start, int end) {
        vector<vector<pi> > adj(n);
        for(int i=0;i<edges.size();i++)
        {
            adj[edges[i][0]].push_back({edges[i][1],succProb[i]});
            adj[edges[i][1]].push_back({edges[i][0],succProb[i]});
        }
        priority_queue<pi1,vector<pi1> > pq;
        pq.push({1.00,start});//initially taking probabaility as 1 therfore pushing 1.00 and start
        vector<double> dist(n,0.00); // storing maximum probability
        dist[start]=1.00;//initially taking probabaility as 1
        while(!pq.empty())
        {
            double wt=pq.top().first;
            int node=pq.top().second;
            pq.pop();
            for(int i=0;i<adj[node].size();i++)
            {
                int itp=adj[node][i].first;
                int its=adj[node][i].second;
                if(dist[itp]<dist[node]*its) // if probability greater than present then pushing in the priority queue.
                {
                    dist[itp]=dist[node]*its;
                    pq.push({dist[itp],itp});
                }
            }
        }
        return dist[end];
    }
};*/
double maxProbability(int n, vector<vector<int> >& edges, vector<double>& succProb, int start, int end) {
        vector<vector<pi> > adj(n);
        for(int i=0;i<edges.size();i++)
        {
            adj[edges[i][0]].push_back({edges[i][1],succProb[i]});
            adj[edges[i][1]].push_back({edges[i][0],succProb[i]});
        }
        priority_queue<pi1,vector<pi1> > pq;
        pq.push({1.00,start});//initially taking probabaility as 1 therfore pushing 1.00 and start
        vector<double> dist(n,0.00); // storing maximum probability
        dist[start]=1.00;//initially taking probabaility as 1
        while(!pq.empty())
        {
            double wt=pq.top().first;
            int node=pq.top().second;
            pq.pop();
            for(int i=0;i<adj[node].size();i++)
            {
                int itp=adj[node][i].first;
                int its=adj[node][i].second;
                if(dist[itp]<dist[node]*its) // if probability greater than present then pushing in the priority queue.
                {
                    dist[itp]=dist[node]*its;
                    pq.push({dist[itp],itp});
                }
            }
        }
        return dist[end];
    }
int main()
{
    vector<vector<int> >edges;//=[[0,1],[1,2],[0,2]];
    edges[0].push_back(0);
    edges[0].push_back(1);
    edges[1].push_back(1);
    edges[1].push_back(2);
    edges[2].push_back(0);
    edges[2].push_back(2);
    vector<double> succProb;//=[0.5,0.5,0.2];
    succProb.push_back(0.5);
    succProb.push_back(0.5);
    succProb.push_back(0.2);
    cout << maxProbability(3,edges , succProb,0,2);
    return 0;
}
