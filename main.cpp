#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
int NO_LO_VI = 0, EMPECE_A_VER = 1, TERMINE_DE_VER = 2;

struct GRAFO {
    vector<int> estado;
    vector<int> back_edges_inf_en;
    vector<int> back_edges_sup_en;
    vector<vector<int>> tree_edges;
    vector<pair<int,int>> back_edges;
    vector<vector<int>> m;
    vector<int> padre;
    vector<int> memo;
    vector<pair<int,int>> importantes;

    GRAFO(int cantBases) :
        estado(cantBases, NO_LO_VI),
        back_edges_inf_en(cantBases, 0),
        back_edges_sup_en(cantBases, 0),
        tree_edges(cantBases),
        padre(cantBases),
        m(cantBases),
        memo(cantBases, -1){}
};

void dfs(int v, int p, GRAFO &grafo) {
    grafo.estado[v] = EMPECE_A_VER;
    for (int u : grafo.m[v]) {
        if (grafo.estado[u] == NO_LO_VI) {
            grafo.padre[u] = v;
            grafo.tree_edges[v].push_back(u);
            dfs(u, v, grafo);
        } else if (u != p) {
            if (grafo.estado[u] == EMPECE_A_VER){
                grafo.back_edges_inf_en[v]++;
                grafo.back_edges.push_back({v,u});
            }
            else
                grafo.back_edges_sup_en[v]++;

        }
    }
    grafo.estado[v] = TERMINE_DE_VER;
}


int cubren(int v, int p, GRAFO &grafo) {
    if (grafo.memo[v] != -1) return grafo.memo[v];
    int res = 0;
    for (int hijo : grafo.tree_edges[v]) {
        if (hijo != p) {
            res += cubren(hijo, v, grafo);
        }
    }
    res -= grafo.back_edges_sup_en[v];
    res += grafo.back_edges_inf_en[v];
    grafo.memo[v] = res;
    return res;
}

int main() {
    int cantCasos, cantBases, cantEnlaces, U, V;
    cin >> cantCasos;
    for(int i = 0; i<cantCasos; i++){
        cin >> cantBases >> cantEnlaces;
        GRAFO grafo(cantBases);
        for(int j = 0; j<cantEnlaces;j++){
            cin >> U >> V;
            grafo.m[U].push_back(V);
            grafo.m[V].push_back(U);
        }

        dfs(0,-1, grafo);

        for(int u = 0; u < cantBases; u++){
            if(cubren(u, -1, grafo) == 1){
                grafo.importantes.push_back({min(u,grafo.padre[u]), max(u,grafo.padre[u])});
            }
        }

        if(grafo.importantes.size() == 0){
            cout<< 0 << endl;
        }
        if(grafo.importantes.size() > 0){
            for(int q = 0; q < grafo.back_edges.size(); q++){
                bool esImportante = false;
                int punta_inf = grafo.back_edges[q].first;
                int punta_sup = grafo.back_edges[q].second;
                for(int w = grafo.back_edges[q].first; w != punta_sup && !esImportante; w = grafo.padre[w]){
                    if(grafo.memo[w] == 1){
                        esImportante = true;
                        grafo.importantes.push_back({min(punta_inf,punta_sup), max(punta_inf,punta_sup)});
                    }
                }
            }
            cout << grafo.importantes.size() << endl;
            sort(grafo.importantes.begin(), grafo.importantes.end());
            for(int u = 0; u < grafo.importantes.size(); u++){
                cout<< grafo.importantes[u].first << " " << grafo.importantes[u].second << endl;
            }
        }
    }
    return 0;
}
