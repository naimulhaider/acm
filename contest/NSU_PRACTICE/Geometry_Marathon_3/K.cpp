#include<bits/stdc++.h>
using namespace std;

const double EPS = 1e-6;
const double PI = acos(-1);

struct point {
    double x, y;
    point() { x =0.0, y = 0.0; }
    point( double _x, double _y ) : x(_x) , y(_y){}

    bool operator < (point other) const {
        if( fabs(x-other.x) > EPS )
            return x < other.x;
        return y < other.y;
    }

    bool operator == (point other) const{
        return ( fabs(x-other.x) < EPS && fabs((y-other.y)) < EPS );
    }
};

struct line{
    double a, b, c;
    line ( double _a , double _b, double _c ) : a(_a), b(_b), c(_c){}
    line( point p1, point p2 ) {
        if( fabs(p1.x-p2.x) < EPS ) {
            a = 1.0, b = 0.0, c = -p1.x;
        } else {
            a = -(double)(p1.y-p2.y) / (p1.x-p2.x);
            b = 1.0;
            c = -(double) (a*p1.x) - p1.y;
        }
    }
};

struct segment {int x1, y1, x2, y2;};
struct item { double y1, y2;int triangle_id;};

void intersect (segment s1, segment s2, vector<point> & res) {
	line l1 ( s1.y1-s1.y2, s1.x2-s1.x1, l1.a*s1.x1+l1.b*s1.y1 ),
		l2 ( s2.y1-s2.y2, s2.x2-s2.x1, l2.a*s2.x1+l2.b*s2.y1 );
	double det1 = l1.a * l2.b - l1.b * l2.a;
	if (abs (det1) < EPS)  return;
	point p ( (l1.c * 1.0 * l2.b - l1.b * 1.0 * l2.c) / det1,
		(l1.a * 1.0 * l2.c - l1.c * 1.0 * l2.a) / det1 );
	if (p.x >= s1.x1-EPS && p.x <= s1.x2+EPS && p.x >= s2.x1-EPS && p.x <= s2.x2+EPS)
		res.push_back (p);
}
double segment_y (segment s, double x) {
	return s.y1 + (s.y2 - s.y1) * (x - s.x1) / (s.x2 - s.x1);
}
bool eq (double a, double b) {return abs (a-b) < EPS;}
vector<item> c;
bool cmp_y1_y2 (int i, int j) {
	const item & a = c[i];
	const item & b = c[j];
	return a.y1 < b.y1-EPS || abs (a.y1-b.y1) < EPS && a.y2 < b.y2-EPS;
}

int n;
vector<segment> a (2005*3);

double getUnionArea() {
    for (size_t i=0; i<a.size(); ++i) if (a[i].x1 > a[i].x2)
			swap (a[i].x1, a[i].x2),  swap (a[i].y1, a[i].y2);
	vector<point> b; b.reserve (n*n*3);
	for (size_t i=0; i<a.size(); ++i) for (size_t j=i+1; j<a.size(); ++j)
			intersect (a[i], a[j], b);
	vector<double> xs (b.size());
	for (size_t i=0; i<b.size(); ++i) xs[i] = b[i].x;
	sort (xs.begin(), xs.end());
	xs.erase (unique (xs.begin(), xs.end(), &eq), xs.end());
	double res = 0;
	vector<char> used (n); vector<int> cc (n*3); c.resize (n*3);
	for (size_t i=0; i+1<xs.size(); ++i) {
		double x1 = xs[i],  x2 = xs[i+1];
		size_t csz = 0;
		for (size_t j=0; j<a.size(); ++j) if (a[j].x1 != a[j].x2)
				if (a[j].x1 <= x1+EPS && a[j].x2 >= x2-EPS) {
					item it = { segment_y (a[j], x1), segment_y (a[j], x2), (int)j/3 };
					cc[csz] = (int)csz; c[csz++] = it;
				}
		sort (cc.begin(), cc.begin()+csz, &cmp_y1_y2);
		double add_res = 0;
		for (size_t j=0; j<csz; ) {
			item lower = c[cc[j++]];
            used[lower.triangle_id] = true; int cnt = 1;
			while (cnt && j<csz) {
				char & cur = used[c[cc[j++]].triangle_id]; cur = !cur;
				if (cur)  ++cnt;  else  --cnt;
			}
			item upper = c[cc[j-1]];
			add_res += upper.y1 - lower.y1 + upper.y2 - lower.y2;
		} res += add_res * (x2 - x1) / 2;
	}
//	cout.precision (8); cout << fixed << res;
    return res;
}

void addTriangle( int i, int x1, int y1, int x2, int y2, int x3, int y3 ) {
    segment s1 = { x1,y1,x2,y2 }; segment s2 = { x1,y1,x3,y3 };
    segment s3 = { x2,y2,x3,y3 };
    a[i*3] = s1; a[i*3+1] = s2; a[i*3+2] = s3;
}

int main() {

    scanf( "%d", &n );

    for( int i=0; i < n; i++ ) {
        double x, y, m;
        scanf( "%lf %lf %lf" ,&x, &y, &m );
        addTriangle( i, x, y, x+m, y, x, y+m );
    }

    printf( "%.1lf\n" , getUnionArea() );

    return 0;
}
