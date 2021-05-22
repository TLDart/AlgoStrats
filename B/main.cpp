// Duarte Dias 2018293526
// Maria Dias 2018274188
#include <iostream>
#include <cmath>

#define MODULO 1000000007
using namespace std;
long cached = 0;
int tt, n, h, H, hidx;
int dpu[60001][501];
int dpd[60001][501];

int mod_abs(int a, int mod) { return ((a % mod) + mod) % mod; }
int mod_add(int a, int b, int mod) { return (mod_abs(a, mod) + mod_abs(b, mod)) % mod; }
int mod_sub(int a, int b, int mod) { return mod_add(a, -b, mod); }

void solve() {
    int sol = 0, sum, i, j;
    dpu[hidx][0] = 1;
    for (i = 0; i < n - 1; i++) {
        sum = 0;
        for (j = hidx + i; j < H - 1; j++) {
            sum = mod_add(sum, dpu[j][i], MODULO);
            dpu[j + 1][i + 1] = sum;
            sum = mod_sub(sum, dpu[j - (h - 2)][i], MODULO);  // -1 because of using h-1 and an extra -1 because of index adjusting
            if (sum == 0) {
                break;
            }
        }

        sum = 0;
        for (; j > h - 1; j--) {
            sum = mod_add(sum, dpu[j][i], MODULO);
            dpd[j - 1][i + 1] = mod_add(dpd[j - 1][i + 1], sum, MODULO);
            if (j + (h - 2) < H )
                sum = mod_sub(sum, dpu[j + (h - 2)][i], MODULO);  // -1 because of using h-1 and an extra -1 because of index adjusting
        }

        sum = 0;
        for (int j = min(i * (h - 1) - 1, H); j > h - 1; j--) {
            sum = mod_add(sum, dpd[j][i], MODULO);
            dpd[j - 1][i + 1] = mod_add(dpd[j - 1][i + 1], sum, MODULO);
            if (j + (h - 2) < H )
                sum = mod_sub(sum, dpd[j + (h - 2)][i], MODULO);  // -1 because of using h-1 and an extra -1 because of index adjusting
        }

    }


    for (int i = 0; i < n; i++) {
        sol = mod_add(sol, dpd[hidx][i], MODULO);
    }
    cout << sol << endl;

}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> tt;
    while (tt--) {
        cin >> n >> h >> H;
        hidx = h - 1;
        std::fill(dpu[0], dpu[H] + n, 0);
        std::fill(dpd[0], dpd[H] + n, 0);
        solve();
    }
}