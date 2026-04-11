//Analisis Kompleksitas
// n = jumlah elemen array
// Hitung manual (Pseudocode + Cost)
// Pseudocode                       Cost    Best Case (min A[0])   Worst Case (min di akhir)
// min <- A[0]                       c1             1                         1
// for i = 1 .. n-1                  c2             n                         n
//   if A[i] <- min                  c3            n-1                       n-1
//     min = A[i]                    c4             0                        n-1
//   return min                      c5             1                         1


//Total Operasi:
// Tmin(n) = c1 + c2(n-1) + c3(n-1) + c4(0) + c5
//         = (c2 + c3)(n-1) + (c1+c5)
//         = 0(n)

// Tmax(n) = c1 + c2(n-1) + c3(n-1) + c4(n-1) + c5
//         = (c2 + c3 + c4)(n-1) + (c1 +c5)
//         = 0(n)

// (Best Case = 0(n) terjadi jika elemen pertama adalah yang terkecil.)
// (Worst Case = 0(n) terjadi jika array terurut menurun (descending).)
#include <iostream>
using namespace std;

int findmin(int arr[], int n, int &minIndeks) {
    int min = arr[0];
    minIndeks = 0;

    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            minIndeks = i;
        }
    }

    return min;
}

int main() {
    int fibonacci[8] = {1,1,2,3,5,8,13,21};
    int n = sizeof(fibonacci) / sizeof (fibonacci[0]);
    int minIndeks;

    int hasil = findmin (fibonacci, n, minIndeks);
    
    cout << "== Find Minimum ==" << endl;
    cout << "Array Fibonacci: ";
    for(int x : fibonacci) cout << x << " ";
    cout << "Nilai Minimum: " << hasil << endl;
    cout << "Indeks Minimum: " << minIndeks << endl;

    return 0;
}