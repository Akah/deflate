#include "llist.h"

llist *llist_create(void *new_data)
{
    struct node *new_node;

    llist *new_list = (llist *)malloc(sizeof (llist));
    *new_list = (struct node *)malloc(sizeof (struct node));

    new_node = *new_list;
    new_node->data = new_data;
    new_node->next = NULL;
    return new_list;
}

void llist_free(llist *list)
{
    struct node *curr = *list;
    struct node *next;

    while (curr != NULL) {
        next = curr->next;
        free(curr);
        curr = next;
    }

    free(list);
}

void llist_push(llist *list, void *data)
{
    if (list == NULL || *list == NULL) {
        printf("error: pushing to null list\n");
    }

    struct node *head = *list;
    struct node *new_node = malloc(sizeof(struct node));
    new_node->data = data;
    new_node->next = NULL;


    while (head->next != NULL) {
	head = head->next;
    }

    head->next = new_node;
}

void* llist_pop(llist *list)
{
    // void* popped;
    struct node *head = *list;

    while (head->next->next != NULL) {
	head = head->next;
    }

    free(head->next);
    head->next = NULL;

    return NULL;
}

void* llist_last(llist* list)
{
    struct node *head = *list;
    while (head->next != NULL) {
	head = head->next;
    }
    return head;
}

void *llist_shift(llist *list)
{
    void *popped_data;
    struct node *head = *list;

    if (list == NULL || head->data == NULL)
        return NULL;

    popped_data = head->data;
    *list = head->next;

    free(head);

    return popped_data;
}

bool llist_is_empty(llist* list)
{
    struct node *head = *list;
    return head->data == NULL && head->next == NULL;
}

void llist_print(llist *list, void (*print)(void *))
{
    struct node *curr = *list;
    while (curr != NULL) {
        print(curr->data);
        curr = curr->next;
    }
    putchar('\n');
}

void llist_print_int(void* pointer)
{
    if (pointer == NULL)
	return;
    char* num = pointer;
    printf("%d\n", atoi(num));
}

void print_string(void* pointer)
{
    if (pointer == NULL)
	return;
    printf("%s\n", (char*) pointer);
}

void print_pointer(void* pointer)
{
    if (pointer == NULL)
	return;
    printf("%p\n", pointer);
}
