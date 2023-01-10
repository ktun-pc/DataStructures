#include <stdio.h>
#include <stdlib.h>

// Yiginin maksimum buyuklugu
#define STACK_SIZE 2048

// Yigin yapisi
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
    // Yiginin sonuna degeri ekle
    stack->items[stack->count] = value;
    // Eleman sayisi bir arttir
    stack->count++;
}

// Cikarma
int Pop(Stack *stack)
{
    // Eleman sayisini bir azalt
    stack->count--;
    // Sondaki elemani geriye dondur
    return stack->items[stack->count];
}

int main(void)
{
    Stack *stack = Create();    //
    Push(stack, 31);            // 31
    Push(stack, 69);            // 69 31
    Push(stack, 110);           // 110 69 31
    printf("%d\n", Pop(stack)); // 69 31
    printf("%d\n", Pop(stack)); // 31
    printf("%d\n", Pop(stack)); // 

    return 0;
}
