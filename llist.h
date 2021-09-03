#ifndef LLIST_H
#define LLIST_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct node {
    void *data;
    struct node *next;
};

typedef struct node * llist;

/* llist_create: Create a linked list */
llist *llist_create(void *data);

/* llist_free: Free a linked list */
void llist_free(llist *list);

int llist_add_inorder(void *data, llist *list, int (*comp)(void *, void *));
/* llist_push: Add to head of list */
void llist_push(llist *list, void *data);

bool llist_is_empty(llist *list);

/* llist_pop: remove and return end of linked list */
void *llist_pop(llist *list);

/* llist_shift: remove and return head of linked list */
void *llist_shift(llist *list);

void* llist_last(llist* list);

/* llist_print: print linked list */
void llist_print(llist *list, void (*print)(void *data));


void llist_print_int(void* pointer);

void print_string(void* pointer);

void print_pointer(void* pointer);

#endif
