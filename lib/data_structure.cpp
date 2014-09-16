/** BIT WITH RANGE UPDATE **/

#define MAX 100005
int N = MAX;
int data[ MAX ], dataMul[ MAX ] , dataAdd[ MAX ];

void update(int at, int by) {
    while (at < N) {
        data[at] += by;
        at |= (at + 1);
    }
}

int query(int at) {
    int res = 0;
    while (at >= 0) {
        res += data[at];
        at = (at & (at + 1)) - 1;
    }
    return res;
}

int getind(int x) {
    int idx = 0, mask = N;
    while(mask && idx < N) {
        int t = idx + mask;
        if(x >= data[t]) { idx = t; x-=data[t];}
        mask>>= 1;
    }
    return idx;
}

int value(int idx){
    int tot=data[idx];
    if( idx>0 ){
        int z=idx-(idx&-idx); idx--;
        while( idx!=z ) tot-=data[idx], idx-=(idx&-idx);
    }
    return tot;
}

void internalUpdate(int at, int mul, int add) {
    while (at < N) {
        dataMul[at] += mul;
        dataAdd[at] += add;
        at |= (at + 1);
    }
}

void updateRange(int left, int right, int by) {
    internalUpdate(left, by, -by * (left - 1));
    internalUpdate(right, -by, by * right);
}

int queryOfRange(int at) {
    int mul = 0;
    int add = 0;
    int start = at;
    while (at >= 0) {
        mul += dataMul[at];
        add += dataAdd[at];
        at = (at & (at + 1)) - 1;
    }
    return mul * start + add;
}

