#include <iostream>
#include <cmath>
using namespace std;
int main()
{
     float n=0;
     cin>> n;
     if(n<=1)
     {
         cout << "n nu este prim!";
     }
     else
     {
         if(n==2)
         {
             cout << "n este prim";
         }
         else
         {
             if(n%2==0)
             {
                 cout << "n nu este prim!";
             }
             else
             {
                 float i=3;
                 while(i*i<=n)
                 {
                     if(n%i!=0)
                     {
                         i=i+1;
                     }
                     else
                     {
                         cout << "n nu e prim";
                     }
                 }
                 cout << "n este prim";
             }
         }
     }
     return 0;
}
