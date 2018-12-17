/* Tran Trung Duc - ITMO - P3202 */
#include <stdio.h>
#include <stdlib.h>
//make elements
struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
};
struct LinkedList{
    struct Node* head;
    struct Node* tail;
    int length;
};
//init newNode
struct Node* initNewNode(int x){
    struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));
    newNode->data = x;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
//add element to last
void list_addLast(struct LinkedList* ll,int x){
   struct Node* newNode = initNewNode(x);
   if (ll->tail == NULL){
        ll->tail = newNode;
        if (ll->head == NULL) ll->head = newNode;
        ll->length ++;
        return;
   }
   (ll->tail)->next = newNode;
   newNode->prev = ll->tail;
   ll->tail = newNode;
   ll->length++;
}
//add element to first
void list_addFirst(struct LinkedList* ll,int x){
    struct Node* newNode = initNewNode(x);
    if (ll->head == NULL){
        ll->head = newNode;
        if (ll->tail == NULL) ll->tail = newNode;
        ll->length++;
        return;
    }
    (ll->head)->prev = newNode;
    newNode->next = ll->head;
    ll->head = newNode;
    ll->length++;
}
//free list
void listFree(struct LinkedList* ll){
    struct Node* newNode = ll->head;
    struct Node* tmp ;
    while (newNode != ll->tail){
        tmp = newNode->next;
        free(newNode);
        newNode = tmp;
    }
    free(ll->tail);
}
//length of list
int list_length(struct LinkedList* ll){
    int x = ll->length;
    return x;
}
//get n-th element of list
struct Node* list_get(struct LinkedList* ll,int n){
    if (n>=ll->length) return NULL;
    int tmp =0;
    struct Node* res = ll->head;
    while (tmp <= n){
        if (tmp==n) return res;
        tmp++;
        res = res->next;
    }
    return NULL;
}
//sum of elements
int list_sum(struct LinkedList* ll){
    int res = 0;
    if ((ll->head == NULL) && (ll->tail==NULL)) return 0;
    struct Node* tmp = ll->head;
    if (tmp == ll->tail) return tmp->data;
    do{
        res += tmp->data;
        tmp = tmp->next;
    }
    while (tmp != ll->tail);
    res+= ll->tail->data;
    return res;
}

//for-each
void list_foreach(struct Node* newNode,void (*f)(int)){

    if (newNode->next == NULL) {
        f(newNode->data);
        return;
    }
    do{
        f(newNode->data);
        newNode = newNode->next;
    }
    while (newNode!=NULL);
    return;
}
//map
struct LinkedList* map(struct LinkedList* ll,int (*_f)(int)){
    struct LinkedList* ll2 = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    ll2->head = NULL;
    ll2->tail = NULL;
    ll2->length =0;

    struct Node* newNode = ll->head;
    if (ll->head == ll->tail) {int x = _f(newNode->data);list_addLast(ll2,x);return ll2;}
    do{
        int x = _f(newNode->data);
        list_addLast(ll2,x);
        newNode = newNode->next;
    }
    while (newNode!=NULL);
    return ll2;
};
//map_mut
struct LinkedList* map_mut(struct LinkedList* ll,int (*_f)(int)){
    struct Node* newNode = ll->head;
    if (ll->head == ll->tail) {
        int x = _f(newNode->data);
        newNode->data = x;
        return ll;
    }
    do{
        int x = _f(newNode->data);
        newNode->data = x;
        newNode = newNode->next;
    }
    while (newNode!=NULL);
    return ll;
};
//foldl
int find_foldl(int res,int (*_f)(int,int),struct Node* newNode){
    if (newNode == NULL ) return res;
    res = find_foldl(_f(res,newNode->data),(*_f),newNode->next);
    return res;
}
int foldl(int res,int (*_f)(int,int),struct LinkedList* ll){
    res = find_foldl(res,(*_f),ll->head);
    return res;
}
//intenate
struct LinkedList* iterate(int s,int lens,int (*f)(int)){
    struct LinkedList* ll2 = (struct LinkedList*) malloc(sizeof(struct LinkedList));
    ll2->head = NULL;
    ll2->tail = NULL;
    ll2->length =0;
    for(int i=0;i<lens;i++){
        list_addLast(ll2,s);
        s = f(s);
    }
    return ll2;
};
//delete at adress
void list_deleteAt(struct LinkedList* ll,int x){
    int i =0;
    struct Node* newNode = ll->head;
    while (i!=x){
        newNode = newNode->next;
        i++;
    }
    if (newNode==ll->head) {
        ll->head = newNode->next;
        ll->head->prev = NULL;
     }
     else if (newNode == ll->tail){
        ll->tail = newNode->prev;
        ll->tail->next = NULL;
     }
     else {
        newNode->next->prev = newNode->prev;
        newNode->prev->next = newNode->next;
        free(newNode);
     }
}
//at to ll at index
void list_addAt(struct LinkedList* ll,int index){

}
void input(struct LinkedList* ll){
    int x;
    int n =0;
    int arr[100];
    while (scanf("%d",&x) == 1){
        arr[n] = x;
        n++;
    }
    for(int i=n-1;i>=0;i--) list_addLast(ll,arr[i]);
}
