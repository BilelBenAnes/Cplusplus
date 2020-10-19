#include <iostream>
using namespace std;

double minmaxdurch(int &min, int &max, int &durchnitt ,int arrsize, const int arr[]){
for (int i = 0; i < arrsize; i++)
{
    durchnitt+=arr[i];
    
    if(arr[i]>max){
        max=arr[i];
    }else if(arr[i]<min){
        min=arr[i];
    }
}
    return durchnitt/arrsize;  
}

int main(int argc, char const *argv[])
{
    int arr[]={4 , 6 ,7 ,8};
    
     int min =arr[0];
    int  max=0;
    int arrsize=4;
    int durchnitt=0;
   minmaxdurch( min,max,durchnitt,arrsize, arr);
   cout << min<< " "<<durchnitt<<" "<< max;
    
    return 0;
}
