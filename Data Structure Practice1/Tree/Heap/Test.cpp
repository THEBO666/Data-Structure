#include <iostream>
#include <ostream>
#include <random>
#include <time.h>
#include "Heap.hpp"
#include <thread>


void TestTopk(int k)
{
    Heap<int> hp(k);
    FILE *fp = fopen("data.txt", "r");
    if(fp==NULL)
    {
        perror("fopen fail");
    }
    for(int i=0;i<k;i++)
    {
        fscanf(fp,"%d",&hp.a[i]);
    }
    for(int i=(k-1-1)/2;i>=0;i--)
    {
        hp.AdjustDown(hp.a,k,i);
    }
    int val=0;
    while(fscanf(fp,"%d",&val)!=EOF)
    {
        if(val>hp.a[0])
        {
            hp.a[0]=val;
            hp.AdjustDown(hp.a,k,0);
        }
    }

    for(int i=0;i<k;i++)
    {
        std::cout<<hp.a[i]<<" ";
    } 
    fclose(fp);
}
int main()
{
    // srand(time(0));
    // int res = rand();

    // int arr[] = {10, 8, 9, 6, 3, 45, 5, 8, 4, 15, 456, 16, 1526, 123, -9, 0};
    // Heap<int> hp(arr, 16);
    // std::cout << sizeof(arr) << std::endl;
    /*FILE *fp=fopen("data.txt","w");
    if(fp==NULL)
    {
        perror("fopen fail");
    }
    for(int i=0;i<10000;i++)
    {
        int x= rand()%10000;
        fprintf(fp,"%d\n",x);
    }
    fclose(fp);*/
    // TestTopk(10);
    int arr[]={1,5,9,7,8,6,3};
    Heap<int> hp;
    hp.AdjustUp(arr,6);
    for(int i=0;i<7;i++)
        std::cout<<arr[i]<<" ";
    return 0;
}
