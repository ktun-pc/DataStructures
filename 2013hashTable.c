#include <stdio.h>
#include <stdlib.h>

// Tablo boyutu
#define SIZE 11

// Tablodaki her bir musteri yapisi 
typedef struct Customer
{
    // Musteri numarasi
    int no;
    // Musteri adi
    char *firstName;
    // Musteri soyadi
    char *lastName;
} Customer;

// Hash tablosu
Customer table[SIZE];

void Init()
{
    for (int i = 0; i < SIZE; i++)
    {
        table[i].no = -1;
    }
}

// Hash Fonksiyonu
int Hash(int no)
{
    // Musterini numarasini asagidaki islemde kaybettigimizden dolayi
    // karesini basta aliyoruz
    int sq = no * no;
    
    // c = 10^n Buradaki `n` no degiskeninin basamak sayisi
    int c = 1;
    while (no)
    {
        c *= 10;
        no /= 10;
    }

    return (sq % c) % SIZE;
}

// Ekleme
void Add(int no, const char *firstName, const char *lastName)
{
    // Musterini numarasini hash fonksiyonuna gonderiyoruz
    int hash = Hash(no);

    // Eger cikan indeksdeki musteri bos ise oraya alanlari ata ve fonksiyondan cik
    if (table[hash].no == -1)
    {
        table[hash].no = no;
        table[hash].firstName = firstName;
        table[hash].lastName = lastName;
        return;
    }

    // Bastan sona her bir indeksi kontrol et
    for (int i = 0; i < SIZE; i++)
    {
        // Eger i hash ile esit degilse ve tablonun i indeksli girdisi bos ise 
        // Alanlari ata ve fonksiyondan cik
        if (i != hash && table[i].no == -1)
        {
            table[i].no = no;
            table[i].firstName = firstName;
            table[i].lastName = lastName;
            return;
        }
    }

    // Bu anda hicbir `return` calismamis yani girdi eklenememistir
    // Bu durumda tablo dolu mesajini ekrana bas
    printf("Tablo dolu\n");
}

// Bulma
int Find(int no)
{
    int hash = Hash(no);

    // Eger hash indeksli girdi ile `no` degiskeni esitse
    // 1 adimda girdi bulunuyor
    if (table[hash].no == no)
    {
        return 1;
    }

    // Her bir indeksteki girdinin numarasini `no` ile karsilastir
    for (int i = 0; i < SIZE; i++)
    {
        // Eger hash i ile esit degilse ve numaralar ayniysa
        if (i != hash && table[i].no == no)
        {
            // Geriye:
            //      Eger i, hash indeksinden kucukse i + 2 dondur
            //      Eger i, hashden buyukse geriye i + 1 dondur
            return i + 1 + (i < hash);
        }
    }

    // Bu noktada girdi bulunamamistir, -1 degeri ile donus yap
    return -1;
}

int main(void)
{
    Init();
    Add(1, "Kadir", "Alemdar");
    Add(2, "Atalay", "Bas");
    Add(3, "Ali Hakan", "Coban");
    Add(9, "Akif", "Cakir");
    Add(11, "A", "B");
    Add(12, "A", "B");

    printf("%d\n",  Find(1));   // Hash:  (1 * 1)  %  10 % 11 =  1   Index:  1  Find: 1
    printf("%d\n",  Find(2));   // Hash:  (2 * 2)  %  10 % 11 =  4   Index:  4  Find: 1
    printf("%d\n",  Find(3));   // Hash:  (3 * 3)  %  10 % 11 =  9   Index:  9  Find: 1
    printf("%d\n",  Find(9));   // Hash:  (9 * 9)  %  10 % 11 =  1   Index:  0  Find: 2
    printf("%d\n", Find(11));   // Hash: (11 * 11) % 100 % 11 = 10   Index: 10  Find: 1
    printf("%d\n", Find(12));   // Hash: (12 * 12) % 100 % 11 =  0   Index:  2  Find: 3
    return 0;
}
