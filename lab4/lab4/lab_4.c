/* Tran Trung Duc - ITMO - P3202 */
#include "linkedlist.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
void function(int a){printf("%d ",a);return;}
void __function(int a){printf("%d\n",a);return;}
int square(int a){return (a*a);}
int cube(int a){return a*a*a;}
int _func(int x,int a){return x+a;}
int max(int x,int a){return ((x>a)?x:a);}
int min(int x,int a){return ((x>a)?a:x);}
int module(int x){return abs(x);}
int power(int base){return base*2;}

bool bool_save(struct LinkedList* ll,const char* filename){
    FILE* fw = fopen(filename,"w");
    if (!fw) return false;
    struct Node* newNode = ll->head;
    while (newNode!=NULL){
        fprintf(fw,"%d ",newNode->data);
        newNode = newNode->next;
    }
    fclose(fw);
    return true;
}
bool bool_load(struct LinkedList** ll,const char* filename){
    int x;
    FILE* fr = fopen(filename,"r");
    if (fr){
        while (fscanf(fr,"%d",&x)== 1){list_addLast(ll,x);}
        fclose(fr);
        return true;
    }
    else return false;
}
bool bool_serialize(struct LinkedList* ll,const char* filename){
    FILE* fw = fopen(filename,"wb+");
    if (!fw) return false;
    struct Node* newNode = ll->head;
    while (newNode!=NULL){
        int x = newNode->data;
        fwrite(&x,sizeof(int),1,fw);
        newNode = newNode->next;
    }
    fclose(fw);
    return true;

}
bool bool_deserialize(struct LinkedList** ll,const char* filename){
    int x;
    FILE* fr = fopen(filename,"rb");
    if (fr){
        while (fread(&x,sizeof(int),1,fr)>0){list_addLast(ll,x);}
        fclose(fr);
        return true;
    }
    else
    {
        fclose(fr);
        return false;
    }
    //fclose(fr);
}

int main(int argc, char** argv)
{
    struct LinkedList* ll = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    struct LinkedList* ll2 = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    ll->head = NULL;
    ll->tail = NULL;
    ll->length =0;
    input(ll);
    //.3 for each
    printf("Test for each : \n");
    void (*f)(int);
    f = function;
    list_foreach(ll->head,(*f));
    puts("");
    f = __function;
    list_foreach(ll->head,(*f));
    f = function;
    //.4 map
    printf("Test map : \n");
    int (*_f)(int);
    _f= square;
    struct LinkedList* duc = map(ll,(*_f));
    list_foreach(duc->head,(*f));
    puts("");
    _f = cube;
    duc = map(ll,(*_f));
    list_foreach(duc->head,(*f));
    puts("");

    //.5 test foldl
    printf("Test foldl : \n");
    int (*_fu)(int,int);
    _fu= _func;
    int tmp = foldl(0,(*_fu),ll);
    printf("SUM = %d\n",tmp);
    _fu = min;
    printf("MIN = %d\n",foldl(2147483647,(*_fu),ll));
    _fu = max;
    printf("MAX = %d\n",foldl(-2147483647,(*_fu),ll));

    //.6 test map_mut
    printf("Test map_mut : \n");
    _f = module;
    ll = map_mut(ll,(*_f));
    list_foreach(ll->head,(*f));
    puts("");
    //.7 iterate
    printf("Test iterate \n");
    _f = power;
    ll2 = iterate(1,10,(*_f));
    f = function;
    list_foreach(ll2->head,(*f));
    puts("");
    //.8
    bool ok = bool_save(ll,"output.txt");
    //.9
    struct LinkedList* lil = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    lil->head = NULL;
    lil->tail = NULL;
    lil->length =0;
    bool_load(lil,"output.txt");
    list_foreach(lil->head,(*f));
    puts("");
    //.11.12
    ok = bool_serialize(ll,"output1.bin");
    struct LinkedList* lil1 = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    lil1->head = NULL;
    lil1->tail = NULL;
    lil1->length =0;
    ok = bool_deserialize(lil1,"output1.bin");
    list_foreach(lil1->head,(*f));
    //15
    listFree(ll);
    return;
}

