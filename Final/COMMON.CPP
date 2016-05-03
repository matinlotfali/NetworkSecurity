#ifdef QT_CORE_LIB
    #include <iostream>
    using namespace std;
#else
    #include <iostream.h>
#endif

#ifndef TEST_H

#include <math.h>

int PowMod(int a, unsigned int b, unsigned int n)
{
    long long c = (long long)pow(a,b);
    return c % n;

    int f = 1;
    int power = a % n;
    for(unsigned int i=0; i<sizeof(int) * 8; i++)
    {
        int s = 0x00000001 & (b >> i);
        if(s)
            f = (f*power)% n ;
        power = (power * power) % n;
    }
    return f;
}

bool getbit(long long a, int place)
{
    long long k;
    k = 1;
    k = k << place;
    k = a & k;
    k = k >> place;
    return k;
}

long long GetBitInString(char message[100],int index)
{
    int bitsInChar = (sizeof(char)*8);
    int bindex = index % bitsInChar;
    index = index / bitsInChar;
    int token = message[index];
    return getbit(token,bindex);
}

long long setbit(long long a, int place, int bit)
{
    long long k;
    k = 1;
    k = k << place;
    if(bit)
        k = a | k;
    else
        k = a & ~k;
    return k;
}

long long xorbit(long long a, int place, int bit)
{
    if(getbit(a,place) == bit)
        return setbit(a,place,0);
    else
        return setbit(a,place,1);
}

void RemoveChar(char text[100], int index)
{
    for(int i=index; text[i] != '\0'; i++)
        text[i] = text[i+1];
}
void InsertChar(char text[100], int index, char ch)
{
    int len = index;
    while(text[len] != '\0')
        len++;

    for(int i=len; i>=index; i--)
        text[i+1] = text[i];

    text[index] = ch;
}

void NormalizeString(char ptext[100])
{
    for(int i=0; ptext[i]!='\0'; i++)
        if(ptext[i]>='A' && ptext[i]<='Z')
        {
            ptext[i] += -'A'+'a';
        }
        else
            if(ptext[i]<'a' || ptext[i]>'z')
            {
                RemoveChar(ptext,i);
                i--;
            }
}
#define TEST_H
#else
void RemoveChar(char text[100], int index);
void InsertChar(char text[100], int index, char ch);
void NormalizeString(char ptext[100]);
#endif // TEST_H
