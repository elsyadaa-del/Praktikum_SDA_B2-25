#include <iostream>
using namespace std;

int main() {
    int angka [7] = {2,3,5,7,11,13,17};
    int n = 7;

    cout << "\nArray asli: ";
    for (int i = 0; i <n; i++){
        cout << angka[i] << " ";
    }
    cout << endl;

    cout << "\nAlamat memori setiap elemen:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "angka[" << i << "] = " << &angka[i] << " [" << angka[i] << "]" << endl;
    }

    int *ptr_pertama = angka;
    int *ptr_terakhir = &angka[n-1];
    int temp;

    while (ptr_pertama < ptr_terakhir) {
        temp = *ptr_pertama;
        *ptr_pertama = *ptr_terakhir;
        *ptr_terakhir = temp;
        ptr_pertama++;
        ptr_terakhir--;
    }
    
    cout << "\nArray setelah dibalik: ";
    for (int i = 0; i < n; i++) {
        cout << angka[i] << " ";
    }
    cout << endl;

    cout << "\nAlamat memori setelah dibalik: " << endl;
    for (int i = 0; i < n; i++) {
        cout << "angka[" << i << "] = " << &angka[i] << " [" << angka[i] << "]" << endl;
    }

    return 0;
}