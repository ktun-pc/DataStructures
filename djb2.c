#include <stdio.h>

// Daniel J. Bernstein Hash Fonksiyonu
unsigned long long djb2(unsigned char *str)
{
    unsigned long long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c; // hash = hash * 33 + c //
    
    return hash;
}

int main(void)
{
    printf("%llu", djb2("Data"));
    return 0;
}
