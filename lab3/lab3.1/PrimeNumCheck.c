//PrimeNumCheck
#include <stdio.h>

unsigned long n ;


unsigned long check(char *arr){
    int n = strlen(arr);
    if(n > 19) return -1;
    unsigned long res = 0;
    for(int i = 0; i < n; i++){
        int x = arr[i] - '0';
        if(('0' <= arr[i]) && (arr[i] <= '9')) res = (res * 10) + x;
        else return -1;
    }
    return res;
}

void input(){
    char* input[100];
    scanf("%s",&input);
    n = check(input);
}

int is_prime(unsigned long n){
    if (n<2) return 0;
    if (n<4) return 1;
    if (n%2==0 || n%3==0) return 0;
    size_t i = 5;
    size_t w = 2;
    while (i*i<=n){
        if (n%i == 0) return 0;

        i+=w;
        w= 6-w;
    }
    return 1;
}

int main(int argc, char** argv){
    do{
        input();
        if (n == -1 ) printf("Wrong input\n");
        else break;
    }
    while (1);

    if (is_prime(n) == 0) printf("NO");
    else printf("YES");

    return 0;
}
