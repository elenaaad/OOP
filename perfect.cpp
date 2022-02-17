#include <iostream>
using namespace std;

int perfect (int x)
{
  int d, s = 0;
  for (d=1; d<=x/2; d++)
  {
    if (x%d == 0) s+=d;
    d++;
  }

  if (x==s) return 1;
  return 0;
 }

 int main ()
 {
    int a, b;
 cin>>a>>b;
 int i;
 for (i=a; i<=b; i++)
   if ( perfect(i)==1)cout<<i;

return 0;
}