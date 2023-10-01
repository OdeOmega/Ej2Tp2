#include <iostream>
#include <vector>
#include <limits>
using namespace std;

using ll = long long;
const ll inf = LLONG_MAX;

pair<int,int> p,h;


ll buscar(pair<int,int> actual, ll t, vector<vector<bool>> recorrido, pair<int,int> destino,vector<vector<int>> &bsas, vector<vector<vector<ll>>> &m,int &filas, int &columnas){
    if(m[t][actual.first][actual.second] != -1){ //Ya llegue alguna vez con el mismo tiempo
        return m[t][actual.first][actual.second];
    }
    else{
        if(actual == destino){ //Legué a destino, devuelvo el tiempo
            return t;
        }
        if(t >= bsas[actual.first][actual.second] && bsas[actual.first][actual.second] != 0){ //Hay manifestación y llegué tarde
            //m[t][actual.first][actual.second] = inf;
            ll INF = inf;
            return INF;
        }
        if(actual.first < 0 || actual.second < 0 || actual.first >= filas || actual.second >= columnas){ //Me fui de rando de la matriz
            ll INF = inf;
            return INF;
        }
        if(recorrido[actual.first][actual.second]){ //En esta mismo camino ya pasé por ahí
            ll INF = inf;
            return INF;
        }
        else{
            recorrido[actual.first][actual.second] = true;
            //Acá abajo intento de acceder un lugar de la memoria que no se si existe, está bien que el
            //Buscar devuelve inf pero no tiene donde guardarlo
            ll a,b,c,d;
            if(actual.first+1 < m[0].size() && ! recorrido[actual.first+1][actual.second]){
                m[t+1][actual.first+1][actual.second] = buscar({actual.first+1,actual.second}, t + 1,recorrido, destino, bsas, m,filas, columnas);
                a = m[t+1][actual.first+1][actual.second];
            }
            else{
                a = inf;
            }
            if(actual.first-1 >= 0 && !recorrido[actual.first-1][actual.second]){
                m[t+1][actual.first-1][actual.second] = buscar({actual.first-1,actual.second}, t + 1,recorrido, destino, bsas, m,filas, columnas);
                b = m[t+1][actual.first-1][actual.second];
            }
            else{
                b = inf;
            }
            if(actual.second+1 < m[0][0].size() && !recorrido[actual.first][actual.second+1]){
                m[t+1][actual.first][actual.second+1] = buscar({actual.first,actual.second+1}, t + 1,recorrido, destino, bsas, m,filas, columnas);
                c = m[t+1][actual.first][actual.second+1];
            }
            else{
                c = inf;
            }
            if(actual.second-1 >= 0 && !recorrido[actual.first][actual.second-1]){
                m[t+1][actual.first][actual.second-1] = buscar({actual.first,actual.second-1}, t + 1,recorrido, destino, bsas, m,filas, columnas);
                d = m[t+1][actual.first][actual.second-1];
            }
            else{
                d = inf;
            }
            recorrido[actual.first][actual.second] = false;
            m[t][actual.first][actual.second] = min(a,min(b,min(c,d)));
            return min(a,min(b,min(c,d)));
        }
    }
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
        vector<vector<vector<ll>>> m(filas*columnas+1,vector<vector<ll>>(filas,vector<ll>(columnas,-1)));
        vector<vector<vector<ll>>> mm(filas*columnas+1,vector<vector<ll>>(filas,vector<ll>(columnas,-1)));
        vector<vector<bool>> recorrido(filas,vector<bool>(columnas,false));
        pair<int,int> hospital = {hospitalX,hospitalY};
        pair<int,int> paciente = {pacienteX,pacienteY};
        ll ida = buscar(hospital,0,recorrido,paciente,bsas,m,filas,columnas);
        ll vuelta = inf;
        if(ida != inf){
            vuelta = buscar(paciente,ida,recorrido,hospital,bsas,mm,filas,columnas);
        }
        if(ida == inf || vuelta == inf){
            cout << "IMPOSIBLE" << endl;
        }
        else{
            cout<< ida << " " << vuelta << endl;
        }
    }
    return 0;
}

