#include <iostream>
#include <cstdio>

using namespace std;

void Reverse(int a[],int left,int right)
{
    while(left<right)
    {
        int temp=a[left];
        a[left]=a[right];
        a[right]=temp;
        left++;
        right--;
    }
}

void Converse(int a[],int n,int p)
{
    Reverse(a,0,p-1);
    Reverse(a,p,n-1);
    Reverse(a,0,n-1);
}
int main()
{
    int data[50];
    int n,p;
    cin>>n>>p;
    for(int i=0;i<n;i++)
        cin>>data[i];
    Converse(data,n,p);
    for(int i=0;i<n;i++)
    {
        cout<<data[i]<<" ";
    }
}