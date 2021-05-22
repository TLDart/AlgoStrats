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

void tj(int u) {
    //cout << u << endl;
    low[u] = dfscounter;
    dfs[u] = dfscounter;
    dfscounter++;
    S.push_back(u);
    for (int i = 0; i < v[u]->nbg.size(); i++) {
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


int main() {
    int tt;
    int n, m, q;
    int a, b, w;
    cin >> tt;
    while (tt--) {
        cin >> n >> m >> q;
        dfs.assign(n, -1); low.assign(n, 0); visited.assign(n, 0);
        v.clear();

        for (int i = 0; i < n; i++) {
            v.push_back(new Node(i));
        }
        for (int i = 0; i < m; i++) {
            cin >> a >> b >> w;
            a--; //Index fitting (0-start)
            b--;
            v[a]->updateNbg(w, b);
        }
        /* for (Node* n : v) {
            cout << "--------" << endl;
            cout << n->id << endl;
            cout << "--------" << endl;
            for (pair<int, int> k : n->nbg) {
                cout << k.first << " " << k.second << endl;
            }
        } */
        dfscounter = 0;
        nrCircuit = 0;
        bigCircuit = 0;
        for (int i = 0; i < n; i++) {
            if (dfs[i] == -1) {
                S.clear();
                tj(i);
            }
        }
        /* for (int i : dfs){
            cout << i << " ";
        }
        cout << endl;
        for (int i : low){
            cout << i << " ";
        }
        cout << endl;
        for(auto k : Scc){
            cout << "->>" << endl;
            for(auto l :k ){
                cout << l << " " ;
            }
            cout << endl;
        } */

        if (q < 3) {
            if (q == 1) {
                cout << nrCircuit << endl;
            }
            if (q == 2) {
                cout << nrCircuit << " " <<  bigCircuit << endl;

            }

        }
        else {//Run Kruskal


             if (q == 3) {
                cout << nrCircuit << " " <<  bigCircuit << endl;
            }
            if (q == 4) {
                cout << nrCircuit << " " <<  bigCircuit << endl;

            }

        }
    }

}