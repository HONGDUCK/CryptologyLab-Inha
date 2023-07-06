#include <iostream>
using namespace std;

int* polyMulti(int a[], int a_size, int b[], int b_size);
int* polyDiv(int a[], int a_size, int b[], int b_size);
void printPoly(int poly[], int size);

int main(){

    /* TEST1
    int tempPoly1[4] = {3, 4, 2, 4};
    int tempPoly2[4] = {8, 4, 2, 5};

    int* poly = polyMulti(tempPoly1, 4, tempPoly2, 4);

    printPoly(poly, 7);
    */
    
    int tempPoly1[4] = {4,3,2,1};
    int tempPoly2[3] = {1,0,1};

    polyDiv(tempPoly1, 4, tempPoly2, 3);

    return 0;
}

int* polyDiv(int a[], int a_size, int b[], int b_size){
    if(a_size < b_size){
        /*Error 처리*/
        cout << "Error Try Again\n";

        return nullptr;
    }

    int* tempArr = new int[a_size];
    for(int i=0; i<a_size; i++){
        tempArr[i] = a[i];
    }

    int* divisor = new int[b_size-1];
    int index = a_size-1;
    int indexForDivisor = 1;
    while (index >= b_size-1){
        int divNum = tempArr[index] / b[b_size - 1];
        tempArr[index] = 0;

        divisor[b_size-1 - indexForDivisor] = divNum;

        for(int i=1; i<=b_size; i++){
            tempArr[index - i] = tempArr[index - i] - (b[b_size-1 - i] * divNum);
        }

        index--;
        indexForDivisor++;
    }

    /* print */
    //printPoly(divisor, b_size-1); /* 몫 */
    //printPoly(tempArr, a_size); /* 나머지 */

    return nullptr;
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