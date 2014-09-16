#include<bits/stdc++.h>

using namespace std;

int main() {
    //ios_base::sync_with_stdio(0);
    //freopen("in.txt", "r", stdin);
    string in;
    bool dotflag;
    int t, l, r, sp, dot, other, digitafterdot, zeroafterdot;

    cin >> t;
    getline(cin, in);

    for(int i = 0; i < t; i++) {
        dotflag = false;
        getline(cin, in);

        int zeros = 0, zdot = 0;
        for(int j = 0; j < in.size(); j++) {
            if(in[j] == '0') zeros++;
            if(in[j] == '.') zdot++;
        }

        if((in.size() == zeros + zdot) && (zdot <= 1)) {
            cout << "0\n";
            continue;
        }

        l = r = 0;
        sp = dot = other = digitafterdot = zeroafterdot = 0;
        for(int j = 0; j < in.size(); j++) {
            if(in[j] == ' ') {
                l = j+1;
            } else break;
        }

        r = in.size();
        for(int j = in.size() - 1; j >= 0; j--) {
            if(in[j] == ' ') {
                r = j;
            } else break;
        }

        if(in[l] == '+') l++;
        //cout << l << " " << r << endl;

        for(int j = l; j < r; j++) {
            //flag &= (in[j] >= '0' && in[j] <= '9');
            if(in[j] == ' ') {
                sp++;
            } else if (in[j] == '.') {
                dotflag = true;
                dot++;
            } else if (in[j] >= '0' && in[j] <= '9') {
                if(dotflag) {
                    digitafterdot++;
                    if(in[j] == '0') zeroafterdot++;
                }
            } else other++;
        }

        if(sp == 0 && other == 0 && dot <= 1 && (digitafterdot == zeroafterdot)) {
            //cout << "valid\n";
            bool zero = false;

            for(int j = l; j < r; j++) {
                if(in[j] == '.') break;
                if(!zero && in[j] == '0') {
                    continue;
                } else {
                    zero = true;
                    cout << in[j];
                }
            }
            cout << "\n";
        } else {
            cout << "invalid input\n";
        }

//        cout << in.substr(l, r-l+1) << " " << atof(in.substr(l, r-l+1).c_str()) << endl;
//        if(flag) {
//            bool zero = false;
//
//            for(int j = l; j < r; j++) {
//                if(!zero && in[j] == '0') {
//                    continue;
//                } else {
//                    zero = true;
//                    cout << in[j];
//                }
//            }
//            cout << "\n";
//        } else cout << "invalid input\n";
    }

    return 0;
}
