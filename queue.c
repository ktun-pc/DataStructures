#include <stdio.h>
#include <stdlib.h>

// Kuyrugun maksimum buyuklugu
#define QUEUE_SIZE 2048

// Kuyruk yapisi
// FIFO: First  In   First  Out
//        Ilk  Giren  Ilk  Cikar
typedef struct Queue
{
    // Kuyrukdaki eleman sayisi
    int count;
    // Elemanlari tuttugumuz sayi dizi
    int items[QUEUE_SIZE];
} Queue;

// Olusturma
Queue * Create()
{
    Queue *queue = malloc(sizeof(Queue));
    // Kuyrugun baslangictaki eleman sayisi 0
    queue->count = 0;
    return queue;
}

// Ekleme
void Enqueue(Queue *queue, int value)
{
    // Eger kuyruk dolu ise ekleme yapmadan fonksiyondan cik
    if (queue->count == QUEUE_SIZE)
        return;
    
    // Kuyrugun sonuna degeri ekle
    queue->items[queue->count] = value;
    // Eleman sayisi bir arttir
    queue->count++;
}

// Cikarma
int Dequeue(Queue *queue)
{
    // Eger kuyruk bos ise cikarma yapmadan fonksiyondan cik
    // Bir deger dondurmemiz gerektiginden dolayi geriye 0 dondurmeyi tercih ettim 
    if (queue->count == 0)
        return 0;
    
    // Ilk elemani degere ata
    int value = queue->items[0];

    // Kuyruktaki elemanlari bir geriye kaydir
    for (int i = 1; i < queue->count; i++)
    {
        queue->items[i - 1] = queue->items[i];
    }

    // Eleman sayisini bir azalt
    queue->count--;
    // Ilk elemani geriye dondur
    return value;
}

// Yazdirma
void Print(Queue *queue)
{
    for (int i = 0; i < queue->count; i++)
    {
        printf("%d\n", queue->items[i]);
    }
}

int main(void)
{
    Queue *queue = Create();        //
    Enqueue(queue, 31);             // 31
    Enqueue(queue, 69);             // 31 69
    Enqueue(queue, 110);            // 31 69 110
 // printf("%d\n", Dequeue(queue)); // 31 69
 // printf("%d\n", Dequeue(queue)); // 31
 // printf("%d\n", Dequeue(queue)); //
    Print(queue);

    free(queue);
    return 0;
}
