#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;
ifstream f ("retea2.in");
ofstream g ("retea2.out");
struct bloc{
    int x, y;
};
struct centrala{
    int x, y;
};
vector <bloc> blocuri(2001);
vector <centrala> centrale(2001);
vector<double>dist(2001);
vector<bool>viz(2001);
// distanta euclidiana dintre 2 puncte
double distanta_euclidiana (int x1,int y1,int x2,int y2){
    return sqrt((double)(x1-x2)*(double)(x1-x2) + (double)(y1-y2)*(double)(y1-y2));
}
int main() {
    int n, m;
    double cost = 0;
    f >> n >> m;
    for (int i = 0; i< n; i++)
        f >> centrale[i].x >> centrale[i].y;
    for (int i=0; i < m; i++){
        dist[i] = 99999;
        f >> blocuri[i].x >> blocuri[i].y;
    }
    // creare vector de distante
    for (int i=0; i<n; i++)
        for (int j = 0; j < m; j++){
            // cautare cea mai apropiata centrala de fiecare bloc
             dist[j] = min(dist[j], distanta_euclidiana(blocuri[j].x,blocuri[j].y,centrale[i].x,centrale[i].y));
    }
    // parcurgem blocurile
    int poz  = -1;
    for (int i=0; i<m; i++){
        double min_dist = 99999;
        for (int j=0; j<m; j++){
            if (dist[j] < min_dist && viz[j] == false)
           {
                // cel mai apropiat bloc nevizitat
                min_dist = dist[j];
                poz = j;
            }
        }
        viz[poz] = true;
        cost += min_dist;

        for (int j=0; j<m; j++)
            if (viz[j] == false)
                // bloc nevizitat
                dist[j] = min(dist[j], distanta_euclidiana(blocuri[poz].x,blocuri[poz].y, blocuri[j].x, blocuri[j].y));
    }
    // afisare cost minim (arbore partial de cost minim)
    g <<fixed<<setprecision(6)<<cost;
    return 0;
}
