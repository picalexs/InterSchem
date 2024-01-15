#include <iostream>
#include <cmath>
using namespace std;
int main()
{
     float v[100]={0}, x=0, i=0;
     cin>> x;
     while(i<x)
     {
         v[i]=i, i=i+1;
     }
     float i=0;
     while(i<x)
     {
         cout << v[i];
         i=i+1;
     }
     return 0;
}
