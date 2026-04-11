
int FindMin(int arr[], int n, int &minIndex) {
    int min = arr[0];
    minIndex = 0;
    
    for (int i = 1; i < n; i++) {
        if (arr[i] < min) {
            min = arr[i];
            minIndex = i;
        }
    }
    
    return min;
}

int main() {
    // Array dengan 8 elemen bilangan Fibonacci
    int fibonacci[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int n = 8;
    int minIndex;
    
    cout << "Array Fibonacci: ";
    for (int i = 0; i < n; i++) {
        cout << fibonacci[i] << " ";
    }
    cout << endl;
    
    int minValue = FindMin(fibonacci, n, minIndex);
    
    cout << "Nilai minimum: " << minValue << endl;
    cout << "Berada pada indeks ke-" << minIndex << endl;
    
    return 0;
}