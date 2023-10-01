#include <iostream>
#include <vector>
#include <limits>
using namespace std;

using ll = long long;
const ll inf = 1e18;

pair<int,int> p,h;

//vector<vector<vector<int>>> m;
int filas, columnas;

int buscar(pair<int,int> actual, int t, vector<vector<bool>> recorrido, pair<int,int> destino,vector<vector<int>> &bsas, vector<vector<vector<int>>> &m){
    if(m[t][actual.first][actual.second] != -1){ //Ya llegue alguna vez con el mismo tiempo
        return m[t][actual.first][actual.second];
    }
    else{
        if(actual == destino){ //Legué a destino, devuelvo el tiempo
            return t;
        }
        if(t >= bsas[actual.first][actual.second] && bsas[actual.first][actual.second] != 0){ //Hay maifestación y llegué tarde
            m[t][actual.first][actual.second] = inf;
            return inf;
        }
        if(actual.first < 0 || actual.second < 0 || actual.first >= filas || actual.second >= columnas){ //Me fui de rando de la matriz
            return inf;
        }
        if(recorrido[actual.first][actual.second]){ //En esta mismo camino ya pasé por ahí
            return inf;
        }
        else{
            recorrido[actual.first][actual.second] = true;
            //Acá abajo intento de acceder un lugar de la memoria que no se si existe, está bien que el
            //Buscar devuelve inf pero no tiene donde guardarlo
            ll a,b,c,d;
            if(actual.first+1 < m[0].size() && ! recorrido[actual.first+1][actual.second]){
                m[t+1][actual.first+1][actual.second] = buscar({actual.first+1,actual.second}, t + 1,recorrido, destino, bsas, m);
                a = m[t+1][actual.first+1][actual.second];
            }
            else{
                a = inf;
            }
            if(actual.first-1 >= 0 && !recorrido[actual.first-1][actual.second]){
                m[t+1][actual.first-1][actual.second] = buscar({actual.first-1,actual.second}, t + 1,recorrido, destino, bsas, m);
                b = m[t+1][actual.first-1][actual.second];
            }
            else{
                b = inf;
            }
            if(actual.second+1 < m[0][0].size() && !recorrido[actual.first][actual.second+1]){
                m[t+1][actual.first][actual.second+1] = buscar({actual.first,actual.second+1}, t + 1,recorrido, destino, bsas, m);
                c = m[t+1][actual.first][actual.second+1];
            }
            else{
                c = inf;
            }
            if(actual.second-1 >= 0 && !recorrido[actual.first][actual.second-1]){
                m[t+1][actual.first][actual.second-1] = buscar({actual.first,actual.second-1}, t + 1,recorrido, destino, bsas, m);
                d = m[t+1][actual.first][actual.second-1];
            }
            else{
                d = inf;
            }
            recorrido[actual.first][actual.second] = false;
            return min(a,min(b,min(c,d)));
        }
    }
}

int main() {
    int cantTest, tiempo, hospitalX, hospitalY, pacienteX, pacienteY;
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
        vector<vector<vector<int>>> m(filas*columnas,vector<vector<int>>(filas,vector<int>(columnas,-1)));
        vector<vector<bool>> recorrido(filas,vector<bool>(columnas,false));
        pair<int,int> hospital = {hospitalX,hospitalY};
        pair<int,int> paciente = {pacienteX,pacienteY};
        int aber = buscar(hospital,0,recorrido,paciente,bsas,m);
        cout<< aber<<endl;
    }
    return 0;
}
