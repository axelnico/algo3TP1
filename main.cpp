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

bool allProductsResistWeight(int i,int totalWeigth);

bool isAValidSolution(int totalWeigth);

int PD(int i, int r);

bool resistsWeight(int i, int totalWeigth);

int BTPodas(int i, int k, int p);

int BT(int i, int k, int p);

int n;
int R;
int maxValue = 0;
vector<bool> partialSolution;
vector<Product> products;
vector<vector<int>> memoriaPD;

const int UNDEFINED = -1;

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
    //memoriaPD = vector<vector<int>>(n+1, vector<int>(R+1, UNDEFINED));
    //int result = BT(0,0,0);
    //int result = PD(n,R);
    int result = BTPodas(0,0,0);
    cout << result << endl;
}


// Representacion es con un vector de booleanos, indicando en cada posicion si el producto se agrega o no
int BT(int i, int k, int p) {
    if (i == n ) {
        return isAValidSolution(p) ? k : 0;
    }
    partialSolution[i] = false;
    int sinagregar = BT(i + 1,k, p);
    partialSolution[i] = true;
    int agregado = BT( i + 1, k + 1, p + products[i].weight);
    return max(sinagregar,agregado);
}

int BTPodas(int i, int k,int p) {
    if(p > R) return 0;
    if(!allProductsResistWeight(i,p)) return 0;
    if(k + (n-i) <= maxValue) return 0;
    if (i == n ) {
        if(k > maxValue) maxValue = k;
        return k;
    }
    partialSolution[i] = false;
    int sinagregar = BTPodas(i + 1,k,p);
    partialSolution[i] = true;
    int agregado = BTPodas( i + 1, k + 1, p + products[i].weight);
    return max(sinagregar,agregado);
}

bool resistsWeight(int i, int totalWeigth) {
    if(partialSolution[i]) {
        return (totalWeigth - products[i].weight) <= products[i].resistance;
    }
    // Si el producto no se agrego se interpreta como que resiste el peso
    return true;
}

bool allProductsResistWeight(int i,int totalWeigth) {
    int j = 0;
    int weigthAbove = totalWeigth;
    while(j < i && resistsWeight(j,weigthAbove)) {
        if (partialSolution[j]) {
            weigthAbove = weigthAbove - products[j].weight;
        }
        j++;
    }
    return j == i;
}

bool isAValidSolution(int totalWeigth) {
    return allProductsResistWeight(n,totalWeigth) && totalWeigth <= R;
}

int PD(int i, int r){
    if (i == 0) return 0;
    if(memoriaPD[i][r] == UNDEFINED){
        if(products[i-1].weight > r or products[i-1].resistance < R  -r) {
            memoriaPD[i][r] = PD(i-1,r);
        } else {
            memoriaPD[i][r] = max(PD(i-1,r),PD(i-1,r-products[i-1].weight) + 1);
        }
    }
    return memoriaPD[i][r];
}
