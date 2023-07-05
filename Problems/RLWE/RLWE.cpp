#include <iostream>
using namespace std;

int* polyMulti(int a[], int a_size, int b[], int b_size);
void printPoly(int poly[], int size);

int main(){

    int tempPoly1[4] = {3, 4, 2, 4};
    int tempPoly2[4] = {8, 4, 2, 5};

    int* poly = polyMulti(tempPoly1, 4, tempPoly2, 4);

    printPoly(poly, 7);

    return 0;
}

int* polyMulti(int a[], int a_size, int b[], int b_size){

    int ansLength = a_size + b_size -1;
    int* ans = new int[ansLength];

    for(int i=0; i<ansLength; i++){
        ans[i] = 0;
    }

    for(int i=0; i<a_size; i++){
        for(int j=0; j<b_size; j++){
            ans[i+j] += a[i] * b[j];
        }
    }

    return ans;
}

void printPoly(int poly[], int size){
    for (int i=0; i<size; i++){

       cout << poly[i];

       if(i != 0){
            cout << "x^" << i ;
       }

       if (i != size-1){
           cout << " + ";
       }
    }
    cout << "\n";
}