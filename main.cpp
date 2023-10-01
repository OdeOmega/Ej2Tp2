#include <iostream>
#include <vector>
#include <limits>
#include<list>
using namespace std;

using ll = long long;
const ll inf = LLONG_MAX;


ll buscar(pair<int,int> actual, pair<int,int> destino, vector<vector<int>> &bsas, ll t){
    if(actual == destino){
        return 0;
    }

    int filas = bsas.size();
    int columnas = bsas[0].size();

    list<pair<int,int>> nuevosNodos; //lista de los nodos que agregué en el último paso
    nuevosNodos.push_back(actual); //agrego la pos inicial

    vector<vector<ll>> distancia(filas, vector<ll>(columnas,-1));
    distancia[actual.first][actual.second] = t;

    vector<vector<bool>> visitado(filas,vector<bool>(columnas,false)); //voy guardando los visitados
    visitado[actual.first][actual.second] = true; //agrego la pos inicial como visitada


    while(!nuevosNodos.empty()){//siempre que agregue un nodo, trato de avanzar desde el
        pair<int,int> primero = nuevosNodos.front();
        ll tActual = distancia[primero.first][primero.second];
        // A continuación agrego los vecinos revisando que:
        //  -Esten en rango de la ciudad
        //  -No tenga programada una manifestacion o si tiene que no haya empezado
        //  -No haya sido visitada ya
        if(primero.first+1<bsas.size() && (bsas[primero.first+1][primero.second] == 0 || t+1 < bsas[primero.first+1][primero.second]) && !visitado[primero.first+1][primero.second]){
            pair<int,int> bajar = {primero.first+1,primero.second};
            nuevosNodos.emplace_back(bajar);
            visitado[primero.first+1][primero.second] = true;
            distancia[primero.first+1][primero.second] = tActual+1;
            if(bajar == destino){
                return distancia[primero.first+1][primero.second];
            }
        }
        if(primero.first-1 >= 0 && (bsas[primero.first-1][primero.second] == 0 || t+1 < bsas[primero.first-1][primero.second]) && !visitado[primero.first-1][primero.second]){
            pair<int,int> subir = {primero.first-1,primero.second};
            nuevosNodos.emplace_back(subir);
            visitado[primero.first-1][primero.second] = true;
            distancia[primero.first-1][primero.second] = tActual+1;
            if(subir == destino){
                return distancia[primero.first-1][primero.second] ;
            }
        }
        if(primero.second+1<bsas[0].size() && (bsas[primero.first][primero.second+1] == 0 || t+1 < bsas[primero.first][primero.second+1]) && !visitado[primero.first][primero.second+1]){
            pair<int,int> derecha = {primero.first,primero.second+1};
            nuevosNodos.emplace_back(derecha);
            visitado[primero.first][primero.second+1] = true;
            distancia[primero.first][primero.second+1] = tActual+1;
            if(derecha == destino){
                return distancia[primero.first][primero.second+1];
            }
        }
        if(primero.second-1>=0 && (bsas[primero.first][primero.second-1] == 0 || t+1 < bsas[primero.first][primero.second-1]) && !visitado[primero.first][primero.second-1]){
            pair<int,int> izquierda = {primero.first,primero.second-1};
            nuevosNodos.emplace_back(izquierda);
            visitado[primero.first][primero.second-1] = true;
            distancia[primero.first][primero.second-1] = tActual+1;
            if(izquierda == destino){
                return distancia[primero.first][primero.second-1];
            }
        }
        nuevosNodos.pop_front();
    }
    int a = 0;
    return -1;
}

int main() {
    int cantTest, tiempo, hospitalX, hospitalY, pacienteX, pacienteY,filas,columnas;
    cin>>cantTest;
    for(int t = 0; t<cantTest; t++){
        cin>> filas >> columnas;
        vector<vector<int>> bsas(filas,vector<int>(columnas,0));
        for(int i = 0; i<filas; i++){
            for(int j = 0; j<columnas;j++){
                cin>>tiempo;
                bsas[i][j] = tiempo;
            }
        }
        cin>> hospitalX >> hospitalY >> pacienteX >> pacienteY;

        pair<int,int> hospital = {hospitalX,hospitalY};
        pair<int,int> paciente = {pacienteX,pacienteY};

        ll ida = buscar(hospital,paciente,bsas,0);
        ll vuelta;
        if(ida != -1){
            vuelta = buscar(paciente,hospital,bsas,ida);
        }
        if(ida == -1 || vuelta == -1){
            cout << "IMPOSIBLE" << endl;
        }
        else{
            cout << ida << " " << vuelta<< endl;
        }
    }
    return 0;
}

