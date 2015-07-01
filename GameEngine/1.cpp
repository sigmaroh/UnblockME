#include<cstdlib>
#include<iostream>
using namespace std;
void printvalue(int a,int b)
{
    cout<<a<<" "<<b<<endl;
}
int main()
{
    int i, j, a[10]={0,1,2,3}, b[10]={0,1,2,3};
    for(i=0;i<5;i++)
    for(j=0;j<5;j++)
    {
        printvalue(a[i],b[j]);

    }
    system("pause");
}
