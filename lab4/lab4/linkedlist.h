/* Tran Trung Duc - ITMO - P3202 */
#ifndef linkedlist.h
#define linkedlist.h
#include <stdio.h>
#include <stdlib.h>
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

struct Node* initNewNode(int x);
void list_addLast(struct LinkedList* ll,int x);
void list_addFirst(struct LinkedList* ll,int x);
void listFree(struct LinkedList* ll);
void list_deleteAt(struct LinkedList* ll,int x);
int list_length(struct LinkedList* ll);
struct Node* list_get(struct LinkedList* ll,int n);
struct Node* list_get(struct LinkedList* ll,int n);
void list_foreach(struct Node* newNode,void (*f)(int));
struct LinkedList* map(struct LinkedList* ll,int (*_f)(int));
struct LinkedList* map_mut(struct LinkedList* ll,int (*_f)(int));
int find_foldl(int res,int (*_f)(int,int),struct Node* newNode);
int foldl(int res,int (*_f)(int,int),struct LinkedList* ll);
struct LinkedList* iterate(int s,int lens,int (*f)(int));
void input(struct LinkedList* ll);

#endif // linkedlist
