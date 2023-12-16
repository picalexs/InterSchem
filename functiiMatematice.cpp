#include <iostream>
#include <cmath>
#include <string>

#define infinit FLT_MAX
#define epsi 0.0001
using namespace std;

bool DifInf(double x)
{
    return fabs(infinit - fabs(x)) > infinit / 2.0;
}

double Logaritm(double x)
{
    if (x > epsi && DifInf(x))
        return log(x);
    else
        return infinit;
}
double Putere(double x, double y)
{
    double p = 1;
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
double Inmultit(double x, double y)
{
    if (fabs(x < epsi) || fabs(y) < epsi)
        return 0;
    else
        if (DifInf(x) && DifInf(y))
            return x * y;
    return infinit;
}
bool Egal(double x, double y)
{
    return x == y;
}

bool Diferit(double x, double y)
{
    return x != y;
}
bool MaiMic(double x, double y)
{
    return x < y;
}

bool MaiMare(double x, double y)
{
    return x > y;
}

double Plus(double x, double y)
{
    if (DifInf(x) && DifInf(y))
        return x + y;
    return infinit;
}

double Minus(double x, double y)
{
    if (DifInf(x) && DifInf(y))
        return x - y;
    return infinit;
}
double Impartit(double x, double y)
{
    if (fabs(y) > epsi) return x / y;
    return infinit;
}

double Sinus(double x)
{
    if (DifInf(x))  return sin(x);
    else return infinit;
}

double Cosinus(double x)
{
    if (DifInf(x))  return cos(x);
    else return infinit;
}
double Tangenta(double x)
{
    if (DifInf(x))
        if (fabs(Cosinus(x) > epsi))
            return Sinus(x) / Cosinus(x);
    return infinit;
}
double Cotangenta(double x)
{
    if (DifInf(x))
        if (fabs(Sinus(x) > epsi))
            return Cosinus(x) / Sinus(x);
    return infinit;
}
double Modul(double x)
{
    if (DifInf(x))
        return fabs(x);
    return infinit;
}

double Radical(double x)
{
    if (DifInf(x) && (x > epsi))
        return sqrt(x);
    return infinit;
}

bool esteSpatiu(const char &ch)
{
	return ch == ' ';
}

bool esteOperator(const char& ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '<' || ch == '>';
}
bool esteOperatorLung(const string& token)
{
	return token == "==" || token == "!=" || token == "<=" || token == ">=" || token == "&&" || token == "||";
}   

bool esteFunctie(const string& token) {
    return token == "sin" || token == "cos" || token == "ln" || token == "tg" || token == "ctg" || token == "abs" || token=="sqrt";
}

bool esteCifra(const char& ch) {
    return ch >= '0' && ch <= '9';
}

bool esteNumar(const string& token)
{
    int nrPuncte = 0;
    if(token.empty())
		return false;
    if (token[0] != '-' && !esteCifra(token[0]))
        return false;
    for (int i = 1; i < token.size(); i++) {
        if (token[i] == '.') {
            nrPuncte++;
            if(nrPuncte>1)
				return false;
        }
        else if (!esteCifra(token[i]))
            return false;
    }
    return true;
}