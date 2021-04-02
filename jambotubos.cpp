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


bool isAValidSolution(bool partialSolution[], int R, int n, vector<Product*> products);

bool resistsWeight(bool partialSolution[],int i,vector<Product*> products, int totalWeigth);

int calculateTotalWeightOfAddedProducts(bool partialSolution[], vector<Product*> products);

int BT(int i, int k);

int n = 5;
int R = 50;
bool partialSolution[5];
vector<Product*> products;

int main(int argc, char** argv)
{
    Product* product1 = new Product();
    product1->weight = 10;
    product1->resistance = 45;
    products.push_back(product1);
    Product* product2 = new Product();
    product2->weight = 20;
    product2->resistance = 8;
    products.push_back(product2);
    Product* product3 = new Product();
    product3->weight = 30;
    product3->resistance = 15;
    products.push_back(product3);
    Product* product4 = new Product();
    product4->weight = 10;
    product4->resistance = 2;
    products.push_back(product4);
    Product* product5 = new Product();
    product5->weight = 15;
    product5->resistance = 30;
    products.push_back(product5);
    int result = BT(0,0);
    cout << result << endl;
}




// Representacion es con un vector de booleanos, indicando en cada posicion si el producto se agrega o no
int BT(int i, int k) {
    if (i == n - 1 ) {
        return isAValidSolution(partialSolution,R, n, products) ? k : 0;
    }
    partialSolution[i] = false;
    int sinagregar = BT(i + 1,k);
    partialSolution[i] = true;
    int agregado = BT( i + 1, k + 1);
    return max(sinagregar,agregado);
}

bool resistsWeight(bool partialSolution[],int i,vector<Product*> products, int totalWeigth) {
    if(partialSolution[i]) {
        return totalWeigth <= products[i]->resistance;
    }
    // Si el producto no se agrego se interpreta como que resiste el peso
    return true;
}

int calculateTotalWeightOfAddedProducts(bool partialSolution[], vector<Product*> products) {
    // itera el arreglo y se queda con el peso de todos los elementos agregados
    int length = products.size();
    int i = 0;
    int total = 0;
    while (i < length) {
        if(partialSolution[i]) {
            total += products[i]->weight;
        }
        i++;
    }
    return total;
}

bool isAValidSolution(bool partialSolution[], int R, int n, vector<Product*> products) {
    int j = 0;
    int totalWeigth = calculateTotalWeightOfAddedProducts(partialSolution,products);
    int weigthAbove = totalWeigth;
    if (partialSolution[0]) {
        weigthAbove = weigthAbove - products[0]->weight;
    }
    while(j < n && resistsWeight(partialSolution,j,products,weigthAbove)) {
        if (partialSolution[j]) {
            weigthAbove = weigthAbove - products[j]->weight;
        }
        j++;
    }
    // R es la resitencia del tubo
    return j == n && totalWeigth <= R;
}
