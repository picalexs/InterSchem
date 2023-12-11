#include <iostream>
#include <cmath>

#define infinit FLT_MAX
#define epsi 0.0001
using namespace std;

bool DifInf(float x)
{
    return fabs(infinit - fabs(x)) > infinit / 2.0;
}

float Logaritm(float x)
{
    if (x > epsi && DifInf(x))
        return log(x);
    else
        return infinit;
}
float Putere(float x, float y)
{
    float p = 1;
    int i;
    if (x == 0) return 0;
    else if (y == 0) return 1;
    else if (x == infinit || y == infinit) return infinit;
    else
    {
        for (i = 1; i <= y; i++)
            p *= x;
        return p;
    }
}
float Inmultit(float x, float y)
{
    if (fabs(x < epsi) || fabs(y) < epsi)
        return 0;
    else
        if (DifInf(x) && DifInf(y))
            return x * y;
    return infinit;
}
bool Egal(float x, float y)
{
    return x == y;
}

bool Diferit(float x, float y)
{
    return x != y;
}
bool MaiMic(float x, float y)
{
    return x < y;
}

bool MaiMare(float x, float y)
{
    return x > y;
}

float Plus(float x, float y)
{
    if (DifInf(x) && DifInf(y))
        return x + y;
    return infinit;
}

float Minus(float x, float y)
{
    if (DifInf(x) && DifInf(y))
        return x - y;
    return infinit;
}
float Impartit(float x, float y)
{
    if (fabs(y) > epsi) return x / y;
    return infinit;
}

float Sinus(float x)
{
    if (DifInf(x))  return sin(x);
    else return infinit;
}

float Cosinus(float x)
{
    if (DifInf(x))  return cos(x);
    else return infinit;
}
float Tangenta(float x)
{
    if (DifInf(x))
        if (fabs(Cosinus(x) > epsi))
            return Sinus(x) / Cosinus(x);
    return infinit;
}
float Cotangenta(float x)
{
    if (DifInf(x))
        if (fabs(Sinus(x) > epsi))
            return Cosinus(x) / Sinus(x);
    return infinit;
}
float Modul(float x)
{
    if (DifInf(x))
        return fabs(x);
    return infinit;
}

float Radical(float x)
{
    if (DifInf(x) && (x > epsi))
        return sqrt(x);
    return infinit;
}
