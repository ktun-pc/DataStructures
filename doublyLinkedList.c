#include <stdio.h>
#include <stdlib.h>

// Cift yonlu bagli listenin her bir dugumu temsil eder
typedef struct Node
{
    // Dugumun sayisal degeri
    int value;
    // Bir onceki dugumu isaret eden `pointer`
    struct Node *prev;
    // Bir sonraki dugumu isaret edern `pointer`
    struct Node* next;
} Node;

// Ekleme
Node * Add(Node *head, int value)
{
    // Eklenecek dugum icin bellekten yer ayiriyoruz
    Node *nodeToAdd = malloc(sizeof(Node));
    nodeToAdd->value = value;
    nodeToAdd->prev = NULL;
    nodeToAdd->next = NULL;

    // Eger listenin ilk elemani NULL ise
    if (head == NULL)
    {
        // Listenin ilk elemanina yeni dugumu ata ver geri dondur
        head = nodeToAdd;
        return head;
    }

    // Eger listede eleman varsa listede son elemani bul
    Node *tmp = head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }

    // Listedeki son elemanin sonrasina yeni elemani ekle
    tmp->next = nodeToAdd;
    // Yeni dugumun oncesine son elemani bagla ve ilk elemani geri dondur
    nodeToAdd->prev = tmp;
    return head;
}

// Guncelleme
void Update(Node *head, int oldValue, int newValue)
{
    // Listenin ilk elemanindan baslayarak tum elemanlar icin
    while (head != NULL)
    {
        // Eger su anki isaret ettigimiz eleman ile eski deger esit ise
        if (head->value == oldValue)
        {
            // Degeri yeni deger ile degistir ve fonksiyondan cik
            head->value = newValue;
            return;
        }

        head = head->next;
    }
}

// Silme
Node * Delete(Node *head, int value)
{
    // Gecici degiskene ilk elemani ata
    Node *tmp = head;
    
    // Eger deger ilk elemanda ise
    if (head->value == value)
    {
        // Ilk elemani ilerlet ve oncesini NULL a isaretle
        head = head->next;
        head->prev = NULL;
        // Gecici degiskendeki eski ilk elemani bellekten sil ve yeni ilk elemani geriye dondur 
        free(tmp);
        return head;
    }

    // Listeyi ikinci elemandan baslayarak don
    tmp = head->next;
    while (tmp != NULL)
    {
        // Eger su anki eleman silinecek elemansa
        if (tmp->value == value)
        {
            // Silinecek elemanin oncesinin sonrasina, silinecek elemanin sonrasini ata
            tmp->prev->next = tmp->next;

            // Eger silinecek elemanin sonrasi varsa
            if (tmp->next != NULL)
            {
                // Silinecek elemanin sonrasinin oncesine, silinecek elemanin oncesini ata
                tmp->next->prev = tmp->prev;
            }

            // Silinecek elemanin bellegini serbest birak
            free(tmp);
            return head;
        }

        tmp = tmp->next;
    }
}

// Yazma
void Print(Node *head)
{
    // Tum elemanlari don ve hepsinin sayisal degerini ekrana yazdir
    while (head != NULL)
    {
        printf("%d\n", head->value);
        head = head->next;
    }
}

// Bulma
Node * Find(Node *head, int value)
{
    // Su anki eleman NULL degilken ve degeri aradigimiz degere esit degilken
    while (head != NULL && head->value != value)
    {
        // Elemana sonrakini ata
        head = head->next;
    }

    // Su anki elemani geri dondur
    // Eger bu noktada tum listeyi doner ve aradigimiz degeri bulamazsak
    // Geriye NULL degeri dondurulur
    return head;
}

int main(void)
{
    Node *head = NULL;
    head = Add(head, 31);       // 31
    head = Add(head, 69);       // 31 69
    Print(head);
    head = Delete(head, 31);    // 69
    Update(head, 69, 110);      // 110
    Print(head);
    Node *node = Find(head, 110);
    node->value = 31;           // 31
    Print(head);
    return 0;
}
