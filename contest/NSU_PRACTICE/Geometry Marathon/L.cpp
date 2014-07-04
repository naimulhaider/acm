#include<bits/stdc++.h>
using namespace std;

double PI = acos(-1);

int main(){
    int kase;
    scanf( "%d", &kase );
    for( int z=1; z<=kase; z++ ){
        double r1, r2, h, p;
        scanf( "%lf %lf %lf %lf", &r1, &r2, &h, &p );
        double x = (h*r2) / (r1-r2);
        double Rf = (r2*(p+x))/x;
        double Vb = PI * (Rf*Rf) * (x+p);
        Vb /= 3;
        double Vs = PI * (r2*r2) * x;
        Vs /= 3;
        double res = Vb - Vs;
        printf( "Case %d: %.8lf\n", z, res );
    }

    return 0;
}
