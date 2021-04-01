#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <chrono>
#include <set>
#include <map>

using namespace std;

bool isAValidSolution(int i, int n);

bool resistsWeight(int i, int n, int totalWeigth);

int calculateTotalWeightOfAddedProducts(int i, int n);

int main(int argc, char** argv)
{
	
}

// Representacion es con un vector de booleanos, indicando en cada posicion si el producto se agrega o no
int BT(int i, int n, int k) {
    if (i == n) {
        return isAValidSolution(i,n) ? k : 0;
    }
    //return max(BT,BT);
}

bool resistsWeight(int i, int n, int totalWeigth) {
    bool agregado = true;
    // resistencia del producto i
    int resistencia = 100;
    if(agregado) {
        return totalWeigth <= resistencia;
    }
    // Si el producto no se agrego se interpreta como que resiste el peso
    return true;
}

int calculateTotalWeightOfAddedProducts(int i, int n) {
    // itera el arreglo y se queda con el peso de todos los elementos agregados
    return 0;
}

bool isAValidSolution(int i, int n) {
    int j = 0;
    int totalWeigth = calculateTotalWeightOfAddedProducts(i,n);
    int weigthAbove = totalWeigth;
    while(j < n && resistsWeight(i,n,weigthAbove)) {
       // if(agregado){
        //    weigthAbove - peso del producto
        //}
        j++;
    }
    // R es la resitencia del tubo
    int R = 0;
    return j == n && totalWeigth <= R;
}
