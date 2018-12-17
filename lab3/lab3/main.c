#include <stdio.h>
#include <stdlib.h>

int main()
{
    int x = 10;
    size_t t = sizeof(int);
    printf("%z \n",t);
    return 0;
}

unsigned long convert(char *arr){
    int n = strlen(arr);
    if(n > 19) return -1;
    unsigned long res = 0;
    for(int i = 0; i < n; i++){
    int x = arr[i] - '0';
        if(('0' <= arr[i]) && (arr[i] <= '9'))
        res = (res * 10) + ((arr[i]) - ('0'));
        else return -1;
    }
    return res;
}

void input(){
    char input[100];
    scanf("%s",input);
    unsigned long n = convert(input);
}