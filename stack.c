#include <stdio.h>
#include <stdlib.h>

// Yiginin maksimum buyuklugu
#define STACK_SIZE 2048

// Yigin yapisi
// LIFO: Last  In   First  Out
//       Son  Giren  Ilk  Cikar
typedef struct Stack
{
    // Yigindaki eleman sayisi
    int count;
    // Elemanlari tuttugumuz sayi dizi
    int items[STACK_SIZE];
} Stack;

// Olusturma
Stack * Create()
{
    Stack *stack = malloc(sizeof(Stack));
    // Yiginin baslangictaki eleman sayisi 0
    stack->count = 0;
    return stack;
}

// Ekleme
void Push(Stack *stack, int value)
{
    // Eger yigin dolu ise ekleme yapmadan fonksiyondan cik
    if (stack->count == STACK_SIZE)
        return;
    
    // Yiginin sonuna degeri ekle
    stack->items[stack->count] = value;
    // Eleman sayisi bir arttir
    stack->count++;
}

// Cikarma
int Pop(Stack *stack)
{
    // Eger yigin bos ise cikarma yapmadan fonksiyondan cik
    // Bir deger dondurmemiz gerektiginden dolayi geriye 0 dondurmeyi tercih ettim 
    if (stack->count == 0)
        return 0;

    // Eleman sayisini bir azalt
    stack->count--;
    // Sondaki elemani geriye dondur
    return stack->items[stack->count];
}

// Yazdirma
void Print(Stack *stack)
{
    for (int i = stack->count - 1; i >= 0; i--)
    {
        printf("%d\n", stack->items[i]);
    }
}

int main(void)
{
    Stack *stack = Create();    //
    Push(stack, 31);            // 31
    Push(stack, 69);            // 69 31
    Push(stack, 110);           // 110 69 31
 // printf("%d\n", Pop(stack)); // 69 31
 // printf("%d\n", Pop(stack)); // 31
 // printf("%d\n", Pop(stack)); //
    Print(stack);

    free(stack);
    return 0;
}
