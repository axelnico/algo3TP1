#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>

using namespace std;

// Estructura para modelar los productos
struct Producto {
    int peso;
    int resistencia;
};

bool todosLosProductosResistenPeso(int i, int pesoTotal);

bool esSolucionValida(int pesoTotal);

int PD(int i, int r);

bool resistePeso(int i, int pesoTotal);

int BTPodas(int i, int k, int p);

int FB(int i, int k, int p);

// n es la cantidad de productos
int n;
// R es la resistencia del tubo
int R;
// Se usa en BTPodas para ir almacenando el valor maximo encontrado hasta el momento
int maxValue = 0;
// Vector que representa los productos que se agregaron y los que no. Si esta en true la posicion i
// quiere decir que el producto i se agrego. Caso contrario el producto no se agrego
vector<bool> solucionParcial;
vector<Producto> productos;
vector<vector<int>> memoriaPD;

const int UNDEFINED = -1;

int main(int argc, char** argv)
{
    // Leemos el parametro que indica el algoritmo a ejecutar.
    map<string, string> algoritmosImplementados = {
            {"FB", "Fuerza Bruta"}, {"BTPodas", "Backtracking con podas"}, {"PD", "Programacion dinámica"}
    };

    if (argc < 2){
        cerr << "Uso: ./jambotubos algoritmo" << endl;
        return 0;
    }

    // Verificar que el algoritmo pedido exista.
    if (algoritmosImplementados.find(argv[1]) == algoritmosImplementados.end())
    {
        cerr << "Algoritmo no encontrado: " << argv[1] << endl;
        cerr << "Los algoritmos existentes son: " << endl;
        for (auto& algDesc: algoritmosImplementados) cerr << "\t- " << algDesc.first << ": " << algDesc.second << endl;
        return 0;
    }
    string algoritmo = argv[1];

    // Lectura del input
    cin >> n >> R;
    for(int i = 0; i < n; i++){
        Producto producto;
        cin >> producto.peso;
        cin >> producto.resistencia;
        productos.push_back(producto);
    }

    int resultado;
    auto inicio = chrono::steady_clock::now();
    if (algoritmo == "FB"){
        solucionParcial.assign(n, false);
        resultado = FB(0,0,0);
    }
    else if (algoritmo == "BTPodas") {
        solucionParcial.assign(n, false);
        resultado = BTPodas(0,0,0);
    }
    else if (algoritmo == "PD") {
        memoriaPD = vector<vector<int>>(n+1, vector<int>(R+1, UNDEFINED));
        resultado = PD(n,R);
    }
    auto fin = chrono::steady_clock::now();
    double tiempo = chrono::duration<double,milli>(fin - inicio).count();

    // Imprimimos el tiempo de ejecucion por stderr
    clog << tiempo << endl;

    // Imprimimos el resultado por stdout
    cout << resultado << endl;
    return 0;
}


// Algoritmo de fuerza bruta. i representa el producto que se esta analizando, k la cantidad
// de productos agregados al momento y p el peso acumulado de los productos agregados
int FB(int i, int k, int p) {
    if (i == n ) {
        return esSolucionValida(p) ? k : 0;
    }
    solucionParcial[i] = false;
    int sinAgregar = FB(i + 1,k, p);
    solucionParcial[i] = true;
    int agregado = FB( i + 1, k + 1, p + productos[i].peso);
    return max(sinAgregar,agregado);
}

// Algoritmo de backtracking con podas. Utiliza los mismos parametros que el de FB
int BTPodas(int i, int k,int p) {
    // Poda por factibilidad: Si el peso acumulado supera la resitencia del tubo, la solucion parcial ya no es valida
    if(p > R) return 0;
    // Poda por factibilidad: Si alguno de los productos agregados no resiste el peso por encima del mismo, la solucion parcial ya no es valida
    if(!todosLosProductosResistenPeso(i, p)) return 0;
    // Poda por optimalidad: Si agregando incluso todos los productos que no revise, no supero al maximo encontrado, entonces ya no puedo alcanzar el optimo
    if(k + (n-i) <= maxValue) return 0;
    if (i == n ) {
        if(k > maxValue) maxValue = k;
        return k;
    }
    solucionParcial[i] = false;
    int sinagregar = BTPodas(i + 1,k,p);
    solucionParcial[i] = true;
    int agregado = BTPodas( i + 1, k + 1, p + productos[i].peso);
    return max(sinagregar,agregado);
}

// Devuelve verdadero si y solo si el producto i resiste el pesoTotal (sin incluir el peso del mismo producto)
// o el producto no se agrego
bool resistePeso(int i, int pesoTotal) {
    if(solucionParcial[i]) {
        return (pesoTotal - productos[i].peso) <= productos[i].resistencia;
    }
    return true;
}

// Devuelve verdadero si y solo si todos los productos hasta el i resisten el peso encima de cada uno de ellos
bool todosLosProductosResistenPeso(int i, int pesoTotal) {
    int j = 0;
    int pesoEncima = pesoTotal;
    while(j < i && resistePeso(j, pesoEncima)) {
        if (solucionParcial[j]) {
            pesoEncima = pesoEncima - productos[j].peso;
        }
        j++;
    }
    return j == i;
}

// Devuelve verdadero si y solo si todos los productos resisten el peso encima de ellos y el peso total no supera la resistencia del tubo
bool esSolucionValida(int pesoTotal) {
    return todosLosProductosResistenPeso(n, pesoTotal) && pesoTotal <= R;
}

// Algoritmo de programacion dinamica. Se llama con los valores i = n y r = R. Al parametro r se le va restando
// el peso de los productos agregados
int PD(int i, int r){
    if (i == 0) return 0;
    if(memoriaPD[i][r] == UNDEFINED){
        if(productos[i - 1].peso > r or productos[i - 1].resistencia < R - r) {
            memoriaPD[i][r] = PD(i-1,r);
        } else {
            memoriaPD[i][r] = max(PD(i-1,r), PD(i-1, r - productos[i - 1].peso) + 1);
        }
    }
    return memoriaPD[i][r];
}
