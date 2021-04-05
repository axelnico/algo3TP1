#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>

using namespace std;

struct Product {
    int weight;
    int resistance;
};


bool isAValidSolution();
vector<vector<vector<int>>> memoria2(int n, int r, int j) {
    vector<vector<vector<int>>> mem;
    for (int i; i < n; i++) {
        for (int i; i < r; i++) {
            for (int i; i < j; i++) {
                mem[i][r][j] = -1;
            }
        }
    }
    return mem;
}
bool resistsWeight(int i, int totalWeigth);

int calculateTotalWeightOfAddedProducts();

int BT(int i, int k);

int DP(int i, int r, int j, vector<vector<int>> &m);


int n = 5;
int R = 50;
vector<bool> partialSolution;
vector<Product> products;

int main(int argc, char** argv)
{
    cin >> n >> R;
    partialSolution.assign(n,false);
    for(int i = 0; i < n; i++){
        Product product;
        cin >> product.weight;
        cin >> product.resistance;
        products.push_back(product);
    }
    vector<vector<int>> memoria;
    for (int i = 0; i < n; i++) {
        memoria.push_back({});
        for (int j = 0; j < R; j++) {
            memoria[i].push_back(-1);
        }
    }
    int result = DP(n-1, 50, 0, memoria);
    cout << result << endl;
}


// Representacion es con un vector de booleanos, indicando en cada posicion si el producto se agrega o no
int BT(int i, int k) {
    if (i == n ) {
        return isAValidSolution() ? k : 0;
    }
    partialSolution[i] = false;
    int sinagregar = BT(i + 1,k);
    partialSolution[i] = true;
    int agregado = BT( i + 1, k + 1);
    return max(sinagregar,agregado);
}

bool resistsWeight(int i, int totalWeigth) {
    if(partialSolution[i]) {
        return (totalWeigth - products[i].weight) <= products[i].resistance;
    }
    // Si el producto no se agrego se interpreta como que resiste el peso
    return true;
}

int calculateTotalWeightOfAddedProducts() {
    // itera el arreglo y se queda con el peso de todos los elementos agregados
    int length = products.size();
    int i = 0;
    int total = 0;
    while (i < length) {
        if(partialSolution[i]) {
            total += products[i].weight;
        }
        i++;
    }
    return total;
}

bool isAValidSolution() {
    int j = 0;
    int totalWeigth = calculateTotalWeightOfAddedProducts();
    int weigthAbove = totalWeigth;
    while(j < n && resistsWeight(j,weigthAbove)) {
        if (partialSolution[j]) {
            weigthAbove = weigthAbove - products[j].weight;
        }
        j++;
    }
    // R es la resitencia del tubo
    return j == n && totalWeigth <= R;
}


int DP(int i, int r, int j, vector<vector<int>> &m) {
    if (i == -1) return 0;
    if (m[i][r-1] == -1) {
        if (i != -1 and (products[i].weight > r or products[i].resistance < j)) m[i][r-1] = DP(i-1, r, j, m);
        else m[i][r-1] = max(DP(i-1, r, j, m), DP(i-1, r - products[i].weight, products[i].weight + j, m) + 1);
    }
    return m[i][r-1];
}