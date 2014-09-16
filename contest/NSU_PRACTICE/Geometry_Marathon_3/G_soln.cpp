#include <cmath>
#include <cstdio>
#include <vector>
#include <algorithm>
using std::pair;
using std::vector;

inline double sqr(const double x) { return x*x; }
inline double dist(const double x1, const double y1, const double x2, const double y2)
  { return std::sqrt(sqr(x1-x2) + sqr(y1-y2)); }
inline double angle(const double A, const double B, const double C)
  { return std::acos((sqr(A)+sqr(B)-sqr(C))/(2*A*B)); }
inline int sign(const double x)
{
  static const double EPS = 1e-8;
  if (x > EPS) return 1;
  return x < -EPS ? -1 : 0;
}
const int MAXN = 1000;
const double PI = std::acos(-1.0);
int n;
bool covered[MAXN];
double arc, pol, R[MAXN], A[MAXN], B[MAXN];
vector< pair<double, double> > seg, cover;
inline void getarea(const int i, const double lef, const double rig)
{
  arc += 0.5 * R[i] * R[i] * (rig-lef - std::sin(rig-lef));
  const double x1 = A[i] + R[i] * std::cos(lef), y1 = B[i] + R[i] * std::sin(lef);
  const double x2 = A[i] + R[i] * std::cos(rig), y2 = B[i] + R[i] * std::sin(rig);
  pol += x1*y2 - x2*y1;
}
int main()
{
    freopen( "input.txt", "r", stdin );

  scanf("%d", &n);
  for (int i = 0; i < n; ++i)
  {
    scanf("%lf%lf%lf", A+i, B+i, R+i);
    for (int j = 0; j < i; ++j)
      if (!sign(R[i]-R[j]) && !sign(A[i]-A[j]) && !sign(B[i]-B[j]))
      {
        R[i] = .0;
        break;
      }
  }
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < n; ++j)
      if (i != j && sign(R[j]-R[i]) >= 0 && sign(dist(A[i], B[i], A[j], B[j])-(R[j]-R[i])) <= 0)
      {
        covered[i] = true;
        break;
      }
  for (int i = 0; i < n; ++i) if (sign(R[i]) && !covered[i])
  {
    seg.clear();
    for (int j = 0; j < n; ++j) if (i != j && sign(R[i]) && !covered[i])
    {
      const double d = dist(A[i], B[i], A[j], B[j]);
      if (sign(d-(R[j]+R[i])) >= 0 || sign(d-std::abs(R[j]-R[i])) <= 0)
        continue;
      const double alpha = std::atan2(B[j]-B[i], A[j]-A[i]);
      const double beta = angle(R[i], d, R[j]);
      const pair<double, double> tmp(alpha-beta, alpha+beta);
      if (sign(tmp.first) <= 0 && sign(tmp.second) <= 0)
        seg.push_back(pair<double, double>(2*PI+tmp.first, 2*PI+tmp.second));
      else if (sign(tmp.first) < 0)
      {
        seg.push_back(pair<double, double>(2*PI+tmp.first, 2*PI));
        seg.push_back(pair<double, double>(0, tmp.second));
      }
      else
        seg.push_back(tmp);
    }

    std::sort(seg.begin(), seg.end());
    double rig = 0;
    for (vector< pair<double, double> >::iterator iter = seg.begin(); iter != seg.end(); ++iter)
    {
      if (sign(rig - iter->first) >= 0)
        rig = std::max(rig, iter->second);
      else
      {
        getarea(i, rig, iter->first);
        rig = iter->second;
      }
    }
    if (!sign(rig))
      arc += R[i]*R[i]*PI;
    else
      getarea(i, rig, 2*PI);
  }
  printf("%.3f", pol/2.0 + arc);
}
