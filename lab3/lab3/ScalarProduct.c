#include <stdio.h>

#define MAXN 20

int arr1[MAXN];
int arr2[MAXN];
int n;
void input(){
    scanf("%d",&n);
    for(int i=0; i < n*2 ; i++){
        if (i<n) scanf("%d",&arr1[i]);
        else scanf("%d",&arr2[i-n]);
    }
}

long scalarPro(int* arr1, int* arr2){
    long res=0;
    for(int i =0;i<n;i++){
        res+= (long)arr1[i] * (long)arr2[i];
    }
    return res;
}

int main(int argc, char** argv){
    input();
    printf("The scalar product is %d\n" ,scalarPro(arr1,arr2));
    return 0;
}

