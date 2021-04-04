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

bool resistsWeight(int i, int totalWeigth);

int calculateTotalWeightOfAddedProducts();

int BTPodas(int i, int k);

int BT(int i, int k);

int n = 5;
int R = 50;
int maxValue = 0;
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
    //int result = BT(0,0);
    int result = BTPodas(0,0);
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

int BTPodas(int i, int k) {
    if (i == n ) {
        if(isAValidSolution()){
            if(k > maxValue) maxValue = k;
            return k;
        }
        return 0;
    }
    if(calculateTotalWeightOfAddedProducts() > R) return 0;
    if(k + (n-i) <= maxValue) return 0;
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
