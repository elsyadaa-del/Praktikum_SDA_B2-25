#include <iostream>
#include <string>
using namespace std;

// Struktur Node untuk Circular Linked List Perpustakaan
struct BukuNode {
    string judulBuku;
    BukuNode* next;

    // Constructor
    BukuNode(string judul) {
        judulBuku = judul;
        next = nullptr;
    }
};

// Fungsi insert di akhir Circular Linked List untuk membangun data
BukuNode* tambahBuku(BukuNode* head, string judul) {
    BukuNode* newNode = new BukuNode(judul);
    if (head == nullptr) {
        newNode->next = newNode;
        return newNode;
    }
    
    BukuNode* temp = head;
    while (temp->next != head) {
        temp = temp->next;
    }
    temp->next = newNode;
    newNode->next = head;
    return head;
}

bool cariBuku(BukuNode* head, string judulDicari) {
    if (head == nullptr) {                          

        return false;
    }

    BukuNode* temp = head;

    do {
        if (temp->judulBuku == judulDicari) {
            return true;
        }
        temp = temp->next;
    } while (temp != head);

    return false;
}
// Implementasi ini saya tambahkan karena struktur yang digunakan adalah circular linked list
// Sehingga tidak memiliki penanda akhir berupa nullptr, jika pencarian dilakukan seperti pada linked list biasa
// maka perulangan bisa terus berjalan tanpa henti, karena itu diperlukan kondisi berhenti yang jelas, yaitu saat pointer kembali ke Head
// menandakan bahwa seluruh node sudah ditelurusi satu putaran penuh

// Selain itu saya menggunakan perulangan do-while pada circular linked list ini karena, node pertama tetap harus diperiksa,
// kalo pake while, pengecekan kondisi dilakukan di awal sehingga berpotensi melawan node Head atau bisa jadi membuat logikanya menjadi rumit
// jadi kalau pakai do-while, node pertama pasti diperiksa duluan, lalu perulangan akan berhenti ketika pointer sudah balik ke Head
int main() {
    BukuNode* head = nullptr;
    
    head = tambahBuku(head, "Struktur Data dengan C++");
    head = tambahBuku(head, "Pengantar Algoritma");
    head = tambahBuku(head, "Pemrograman Berorientasi Objek");
    head = tambahBuku(head, "Sistem Basis Data");

    string buku1 = "Pengantar Algoritma";
    string buku2 = "Kalkulus Lanjut";

    cout << "Mencari buku '" << buku1 << "': " 
         << (cariBuku(head, buku1) ? "Ditemukan" : "Tidak Ditemukan") << endl; 
         // Harusnya output: Ditemukan

    cout << "Mencari buku '" << buku2 << "': " 
         << (cariBuku(head, buku2) ? "Ditemukan" : "Tidak Ditemukan") << endl; 
         // Harusnya output: Tidak Ditemukan

    return 0;
}