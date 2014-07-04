#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;

struct point{
    double x,  y;
    point(double _x, double _y): x(_x), y(_y){}
};

double dist( point a, point b ) {
    return hypot( a.x - b.x , a.y - b.y );
}

double norm ( double x, double y ) {
    return sqrt( x * x + y * y );
}

bool insideRectangle( point a , point b, point p ) {
    if( p.x > a.x && p.x < b.x && p.y > b.y && p.y < a.y ) return 1;
    return 0;
}

double gta( point a, point b, point c ) {
    double s1 = dist( a, b ) , s2 = dist( a,c ) , s3 = dist(b, c);
    double s = (s1 + s2 + s3) * 0.5;
    double ret = (s - s1) * (s - s2) * (s - s3);
    ret *= s;
    return sqrt( ret );
}

bool insideCircle( point o, double r, point p ) {
    return norm( o.x - p.x , o.y - p.y ) < r;
}

bool insideTriangle( point a, point b, point c, point p ) {
    double ar1 = gta(a,b,c);
    double ar2 = gta(a,b,p) + gta(a,c,p) + gta(b,c,p);
    return fabs( ar2 - ar1 ) < EPS;
}

int main() {

//    freopen("input.in", "r" ,stdin);

    char c;
    vector<point> fig[15];
    char typ[15];
    double crad[15];
    int ind = 0;
    while( cin >> c ) {
        if( c == '*' ) break;
        if( c == 'r' ) {
            double x1,y1,x2,y2;
            cin >> x1>>y1>>x2>>y2;
            point a(x1,y1), b(x2,y2);
            fig[ind].push_back( a );
            fig[ind].push_back( b );
            typ[ind] = 'r';
        } else if( c == 'c' ) {
            double x1 , y1, r;
            cin >> x1 >> y1 >> r;
            point o(x1,y1);
            fig[ind].push_back( o );
            crad[ind] = r;
            typ[ind] = 'c';
        } else {
            double x1,y1,x2,y2,x3,y3;
            cin >> x1>>y1>>x2>>y2>>x3>>y3;
            point a(x1,y1);
            point b(x2,y2);
            point c(x3,y3);
            fig[ind].push_back(a);
            fig[ind].push_back(b);
            fig[ind].push_back(c);
            typ[ind] = 't';
        }
        ind++;
    }

    double x , y;
    int cnt = 1;
    while(  cin >> x >> y ) {
        if( fabs(x-9999.9) < EPS && fabs(y-9999.9)<EPS ) break;
//        cout << x << " " << y << endl;
        point k(x,y);
        bool ok = 0;
        for( int i=0 ; i < ind; i++ ) {
            if( typ[i] == 'c' ) {
                if( insideCircle(fig[i][0],crad[i],k) ) {
                    ok = 1;
                    cout<<"Point "<< cnt <<" is contained in figure "<<i+1<<"\n";
                }
            } else if ( typ[i] == 'r' ) {
                if( insideRectangle(fig[i][0],fig[i][1],k) ) {
                    ok = 1;
                    cout<<"Point "<< cnt <<" is contained in figure "<<i+1<<"\n";
                }
            } else {
                if( insideTriangle( fig[i][0],fig[i][1],fig[i][2],k ) ) {
                    ok = 1;
                    cout<<"Point "<< cnt <<" is contained in figure "<<i+1<<"\n";
                }
            }
        }

        if( !ok ) {
            cout << "Point "<< cnt <<" is not contained in any figure\n";
        }

        cnt++;
    }

    return 0;
}
