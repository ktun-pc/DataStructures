#include <stdio.h>
#include <stdlib.h>

// Bagli listenin her bir dugumu temsil eder
typedef struct Node
{
    // Dugumun sayisal degeri
    int value;
    // Bir sonraki dugumu isaret edern `pointer`
    struct Node* next;
} Node;

// Ekleme
Node * Add(Node *head, int value)
{
    // Eklenecek dugum icin bellekten yer ayiriyoruz
    Node *nodeToAdd = malloc(sizeof(Node));
    nodeToAdd->value = value;
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

    // Listedeki son elemanin sonrasina yeni elemani ekle ve ilk elemani geri dondur
    tmp->next = nodeToAdd;
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
        // Ilk elemani ilerlet
        head = head->next;
        // Gecici degiskendeki eski ilk elemani bellekten sil ve yeni ilk elemani geriye dondur 
        free(tmp);
        return head;
    }

    // Listeyi ilk elemandan baslayarak sondan bir onceki elemana kadar don
    while (tmp != NULL && tmp->next != NULL)
    {
        // Eger su anki eleman silinecek elemandan bir onceki elemansa
        if (tmp->next->value == value)
        {
            // Sonraki elemani degiskende tut 
            Node *nodeToDelte = tmp->next;
            // Simdiki elemanin sonrasina, silinecek elemandan sonrasini ata
            // 1 -> 2 -> 3
            // Burada su anki eleman 1, silinecek eleman 2 olarak dusunursek
            // 1'in sonrasina 3'u ata
            tmp->next = tmp->next->next;
            // Silinecek elemani yani 2 numarali elemani sil ve fonksiyondan cik
            // Son durumda liste 1 -> 3 seklinde baglanarak kopmaz ve 2 numarali dugum silinmis olur 
            free(nodeToDelte);
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

// Tum Listeyi Silme
void DeleteAll(Node *head)
{
    Node *tmp;

    // Su anki eleman NULL degilken
    while (head != NULL)
    {
        // Elemani geciyi elemana ata
        tmp = head;
        // Bir sonraki elemana gec
        head = head->next;
        // Gecicideki elemani sil
        free(tmp);
    }
}

// Iki sirali listedeki ortak degerleri yazdirma
void PrintCommonValues(Node *head1, Node *head2)
{
    // Iki liste de NULL degilken yani karsilastiracagimiz
    // degerler mevcutken
    while (head1 != NULL && head2 != NULL)
    {
        // Eger degerler ayni ise
        if (head1->value == head2->value)
        {
            // Ekrana yazdir ve ikisini de birer kez kaydir
            printf("%d\n", head1->value);
            head1 = head1->next;
            head2 = head2->next;
        }
        // Eger ilk listedeki deger daha kucukse ilk listeyi kaydir
        else if (head1->value < head2->value)
        {
            head1 = head1->next;
        }
        // Eger ikinci listedeki deger daha kucukse ikinci listeyi kaydir
        else
        {
            head2 = head2->next;
        }
    }
}

int main(void)
{
    Node *head1 = Add(NULL, 5);
    Add(head1, 10);
    Add(head1, 20);
    Add(head1, 50);

    Node *head2 = Add(NULL, 10);
    Add(head2, 30);
    Add(head2, 50);
    Add(head2, 70);

    // 10 50
    PrintCommonValues(head1, head2);

    DeleteAll(head1);
    DeleteAll(head2);
    return 0;
}
