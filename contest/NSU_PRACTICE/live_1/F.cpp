#include <bits/stdc++.h>

using namespace std;

#define LOGSZ 17
int tree[(1<<LOGSZ)+1];
int N = (1<<LOGSZ);

void update(int x, int v){
    while(x <= N) {
        tree[x] += v;
        x += (x&-x);
    }
}

int sum(int x) {
    int res = 0;
    while(x) {
        res += tree[x];
        x -= (x&-x);
    }

    return res;
}

int main() {
    ios_base::sync_with_stdio(0);
    //freopen("in.txt", "r", stdin);
    int t, b, p, q, i, j;
    char ch;

    cin >> t;
    for(int x = 0; x < t; x++) {
        memset(tree, 0, sizeof tree);
        cin >> b >> p >> q;

        for(int k = 0; k < p+q; k++) {
            cin >> ch >> i >> j;
            if(ch == 'P') {
                update(i, j);
            } else {
                cout << sum(j) - sum(i-1) << "\n";
            }
        }
    }

    return 0;
}
