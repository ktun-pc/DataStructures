#include <stdio.h>
#include <stdlib.h>

// Hash tablosunun boyutu
#define TABLE_SIZE 10

// Hash tablosunun kayitlarini temsil eden yapi
typedef struct Entry
{
    // Hash degeri
    int hash;
    // Anahar, deger cifti
    int key;
    const char *value;
    // Sonraki kayiti isaret eden `pointer`
    struct Entry *next;
} Entry;

// Hash tablo yapisi
typedef struct Table
{
    Entry entries[TABLE_SIZE];
} Table;

// Hash fonksiyonu
int Hash(unsigned int key)
{
    return key % TABLE_SIZE;
}

// Tablo Olusturma
Table * CreateTable()
{
    Table *table = malloc(sizeof(Table));
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Her bir kayitin baslangictaki hash degeri -1
        // Bu o kayitin bos oldugunu gosteriyor
        table->entries[i].hash = -1;
        table->entries[i].key = -1;
        table->entries[i].value = NULL;
        table->entries[i].next = NULL;
    }

    return table;
}

// Tablo Silme
void DeleteTable(Table *table)
{
    Entry *tmp;
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Her kayitin `malloc` kullandigimiz alt kayitlarinin
        // bellek alanlarini `free` ile serbest birak
        while (table->entries[i].next != NULL)
        {
            tmp = table->entries[i].next;
            table->entries[i].next = table->entries[i].next->next;
            free(tmp);
        }
    }
}

// Ekleme
void Add(Table *table, unsigned int key, const char *value)
{
    // Anahtari hash fonksiyonu ile hashliyoruz
    int hash = Hash(key);
    // Egerki cikan hash degerindeki kayit bos ise oraya ekleme yap
    if (table->entries[hash].hash == -1)
    {
        table->entries[hash].hash = hash;
        table->entries[hash].key = key;
        table->entries[hash].value = value;
        return;
    }

    // Kayit bos degilse yeni kayit icin `malloc` ile bellekten yer ayir
    // Ve ilgili alanlarini ata
    Entry *entry = malloc(sizeof(Entry));
    entry->hash = hash;
    entry->key = key;
    entry->value = value;
    entry->next = NULL;

    // Hedef kayitin sonraki kayiti bos olana kadar `tmp` degiskenini ilerlet
    // Bu kisim da bagli listeye ekleme yapar gibi son elemanin sonrasina
    // yeni kayiti ekliyoruz
    Entry *tmp = &table->entries[hash];
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    tmp->next = entry;
}

// Veri Alma
const char * Get(Table *table, unsigned int key)
{
    int hash = Hash(key);
    // Hash indeksindeki kayiti gecici degiskene ata
    Entry *tmp = &table->entries[hash];
    // Kayin NULL degilken ve kayitin anahtari aradigimiz anahtar degilken
    while (tmp != NULL && tmp->key != key)
    {
        // Bir sonraki kayita gec
        tmp = tmp->next;
    }

    // Son durumda elimizdeki kayit NULL ise deger olarak geriye NULL dondur
    // Eger elimizde bir kayit varsa onun degerini dondur
    return (tmp == NULL) ? NULL : tmp->value;
}

// Yazdirma
void Print(Table *table)
{
    Entry *tmp;
    printf("HASH   KEY = VALUE\n");
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        // Eger kayit bos ise yazdirmadan sonrakine gec
        if (table->entries[i].hash == -1)
            continue;
        
        // Kayiti ekrana yazdir
        printf("%04d    %d = %s\n", table->entries[i].hash, table->entries[i].key, table->entries[i].value);
        
        // Eger kayitin al kayitlari varsa bunlari teker teker don
        tmp = table->entries[i].next;
        while (tmp != NULL)
        {
            // Alt kayitlar ayni hash degerine sahip olduklari icin tekrar hash degerini yazdirmadim
            // Buradaki ` (tmp->next == NULL ? '`' : '|') ` kismi tamamen ekrandaki cikti ile alakalidir
            printf("  %c-->  %d = %s\n", (tmp->next == NULL ? '`' : '|'), tmp->key, tmp->value);
            tmp = tmp->next;
        }
    }
    printf("\n");
}

int main(void)
{
    Table *table = CreateTable();
    Add(table, 2, "A");
    Add(table, 3, "B");
    Add(table, 1, "C");
    Add(table, 12, "D");
    Add(table, 22, "E");
    Print(table);
    
    DeleteTable(table);
    return 0;
}
