#include <iostream>
using namespace std;

void tukar(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int main () {
    int x, y;

    cout << "Masukkan angka:" << endl;
    cout << "x: ";
    cin >> x;
    cout << "y: ";
    cin >> y;

    cout << "\nSebelum ditukar:" << endl;
    cout << "x = " << x << ",y = " << y << endl;
    tukar (&x, &y);

    cout << "Setelah ditukar:" << endl;
    cout << "x = " << x << ", y = " << y << endl;

    return 0;
}