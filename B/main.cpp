// Duarte Dias 2018293526
// Maria Dias 2018274188
#include <iostream>

#define MODULO 1000000007
using namespace std;
int tt, n, h, H;
int dpu[60001][501];
int dpd[60001][501];

int mod_abs(int a, int mod) { return ((a % mod) + mod) % mod; }
int mod_add(int a, int b, int mod) { return (mod_abs(a, mod) + mod_abs(b, mod)) % mod; }
int mod_sub(int a, int b, int mod) { return mod_add(a, -b, mod); }

int solver(int ch, int k, bool up) {
    if (ch > H || ch < h || k >= n)  // Max Height, Min Height conditions, Index starts at 0, therefore n -1
        return 0;
    if (ch == h && k != 0)  // Ground level
        return 1;
    if (up) {
        if (dpu[ch][k] != -1) {
            return dpu[ch][k];
        }
    } else {
        if (dpd[ch][k] != -1) {
            return dpd[ch][k];
        }
    }

    int res = 0;

    // Go Up
    if (up) {
        for (int i = 1; i < h; i++) {
            if ((ch + i) - ((h - 1) * ((n - 1) - (k + 1))) <= h) res = mod_add(res, solver(ch + i, k + 1, true), MODULO);
            // res += solver(ch + i, k + 1, true);
        }
    }

    // Go Down
    for (int i = 1; i < h; i++) {
        res = mod_add(res, solver(ch - i, k + 1, false), MODULO);
        // res += solver(ch - i, k + 1, false);
    }
    /* cout << res << std::endl;
    cout << "----" << endl; */
    if (up) {
        dpu[ch][k] = res;
    } else {
        dpd[ch][k] = res;
    }

    return res;
    // return res;
}

void solve() {
    int res = solver(h, 0, true);
    cout << res << endl;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> tt;
    while (tt--) {
        cin >> n >> h >> H;
        std::fill(dpu[0], dpu[H] + n, -1);
        std::fill(dpd[0], dpd[H] + n, -1);
        solve();
    }
}