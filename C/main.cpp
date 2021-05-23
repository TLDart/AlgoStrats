#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Node {
public:
    vector<pair<int, int>> nbg;
    int id;
    Node(int n) {
        this->id = n;
        this->nbg = {};
    }
    void updateNbg(int w, int n) { this->nbg.push_back(make_pair(w, n)); }
};


vector<int> dfs, low, S, visited;
vector<Node*> v;
vector<vector<int>> Scc;
int dfscounter = 0;
int bigCircuit = 0, nrCircuit = 0;

class UF {
public:
    vector<int> parent, rank;

    UF(int N) {
        parent.assign(N, 0);
        for (int i = 0; i < N; i++) //make_set operation
            parent[i] = i;
        rank.assign(N, 0);
    }

    int findS(int a) {
        //cout << a << endl;
        if (parent[a] != a) {
            parent[a] = findS(parent[a]);
        }
        return parent[a];
    }
    void UnionS(int a, int b) {
        linkS(findS(a), findS(b));
    }

    void linkS(int a, int b) {
        if (rank[a] > rank[b]) {
            parent[b] = a;
        }
        else {
            parent[a] = b;
        }
        if (rank[a] == rank[b]) {
            rank[b]++;
        }
    }
};

void tj(int u) {
    low[u] = dfscounter;
    dfs[u] = dfscounter;
    dfscounter++;
    S.push_back(u);
    for (size_t i = 0; i < v[u]->nbg.size(); i++) {
        int el = v[u]->nbg[i].second;
        if (dfs[el] == -1) {
            tj(el);
            low[u] = min(low[u], low[el]);
        }
        else if (std::find(S.begin(), S.end(), el) != std::end(S)) {
            low[u] = min(low[u], dfs[el]);
        }
    }
    if (low[u] == dfs[u]) {

        vector<int> C = {};
        int k;
        do {
            k = S.back();
            C.push_back(k);
            S.pop_back();
        } while (k != u);
        if (C.size() > 1) {
            Scc.push_back(C);
            bigCircuit = max(bigCircuit, (int)C.size());
            nrCircuit++;
        }
    }

}

int kk(vector<vector<int>> &a, int n) {
    int weight = 0;
    UF uf(n);
    sort(a.begin(), a.end());
    for (size_t i = 0; i < a.size(); i++) {
        if (uf.findS(a[i][1]) != uf.findS(a[i][2])) {
            weight += a[i][0];
            uf.UnionS(a[i][1], a[i][2]);
        }
    }
    return weight;
}

int main() {
    int tt;
    int n, m, q;
    int a, b, w;
    cin >> tt;
    while (tt--) {
        cin >> n >> m >> q;
        dfs.assign(n, -1); low.assign(n, 0); visited.assign(n, 0);
        v.clear();
        Scc.clear();

        for (int i = 0; i < n; i++) {
            v.push_back(new Node(i));
        }
        for (int i = 0; i < m; i++) {
            cin >> a >> b >> w;
            a--; //Index fitting (0-start)
            b--;
            v[a]->updateNbg(w, b);
        }
        dfscounter = 0;
        nrCircuit = 0;
        bigCircuit = 0;
        for (int i = 0; i < n; i++) {
            if (dfs[i] == -1) {
                S.clear();
                tj(i);
            }
        }
         if (q < 3) {
            if (q == 1) {
                cout << nrCircuit << endl;
            }
            if (q == 2) {
                cout << nrCircuit << " " << bigCircuit << endl;

            }

        }
        else {//Run Kruskal
            int total = 0, longest = 0, res = 0;
            vector<int> sccID = {};
            sccID.assign(n, -1);
            for (size_t i = 0; i < Scc.size(); i++) {
                for (size_t k = 0; k < Scc[i].size(); k++) {
                    sccID[Scc[i][k]] = i;
                }
            }
            for (vector<int> scc : Scc) {
                vector<vector<int>> comp = {};
                for (size_t i = 0; i < scc.size(); i++) {
                    for (size_t k = 0; k < v[scc[i]]->nbg.size(); k++) {
                        int el = v[scc[i]]->nbg[k].second;
                        //cout << sccID[scc[i]] << " " << sccID[el] <<" " <<  scc[i] << " " << el << endl;
                        if (sccID[scc[i]] == sccID[el]) {
                            comp.push_back({ v[scc[i]]->nbg[k].first, scc[i], v[scc[i]]->nbg[k].second });
                        }
                    }

                }
                res = kk(comp, n);
                longest = max(longest, res);
                total += res;
            }


            if (q == 3) {
                cout << nrCircuit << " " << bigCircuit << " " << longest << endl;
            }
            if (q == 4) {
                cout << nrCircuit << " " << bigCircuit << " " << longest << " " << total << endl;

            }

        }
    }

}