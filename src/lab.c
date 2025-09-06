#include "lab.h"
#include <stdio.h>
#include <stdlib.h>

/**
 * Node structure for the circular linked list
 * AI Use: Written by own
 */
typedef struct Node {
    void *data;
    struct Node *next;
} Node;

/**
 * List structure containing the sentinel node and size
 * AI Use: Written by own
 */
struct List {
    Node *head;  // Sentinel node
    size_t size;
};

/**
 * Creates a new circular list with a sentinel node
 * AI Use: Written by own
 */
List *list_create(ListType type) {
    if (type != LIST_LINKED_SENTINEL) {
        return NULL;
    }

    List *list = malloc(sizeof(List));

    // Create sentinel node
    list->head = malloc(sizeof(Node));
    if (!list->head) {
        free(list);
        return NULL;
    }

    list->head->data = NULL;
    list->head->next = list->head;  // Points to itself when empty
    list->size = 0;

    return list;
}

/**
 * Destroys the list and frees all memory
 * AI Use: Assisted by AI
 */
void list_destroy(List *list, FreeFunc free_func) {
    if (!list) return;

    Node *current = list->head->next;  
    while (current != list->head) { 
        Node *next = current->next;
        if (free_func) {
            free_func(current->data);
        }
        free(current);
        current = next;
    }
    free(list->head);  // Free sentinel node
    free(list);
}

/**
 * Appends an element to the end of the list
 * AI Use: Written by own
 */
bool list_append(List *list, void *data) {
    if (!list) return false;

    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return false;

    new_node->data = data;
    
    Node *current = list->head;
    while (current->next != list->head) {
        current = current->next;
    }
    
    new_node->next = list->head;  // Point to sentinel
    current->next = new_node;
    list->size++;
    
    return true;
}

/**
 * Inserts an element at the specified index
 * AI Use: Written by own
 */
bool list_insert(List *list, size_t index, void *data) {
    if (!list || index > list->size) return false;

    Node *new_node = malloc(sizeof(Node));
    if (!new_node) return false;

    new_node->data = data;
    
    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    new_node->next = current->next;
    current->next = new_node;
    list->size++;
    
    return true;
}

/**
 * Removes and returns the element at the specified index
 * AI Use: Assisted by AI
 */
void *list_remove(List *list, size_t index) {
    if (!list || index >= list->size) return NULL;

    Node *current = list->head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    Node *to_remove = current->next;
    void *data = to_remove->data;
    current->next = to_remove->next;
    free(to_remove);
    list->size--;
    
    return data;
}

/**
 * Returns the element at the specified index
 * AI Use: Written by own
 */
void *list_get(const List *list, size_t index) {
    if (!list || index >= list->size) return NULL;

    Node *current = list->head->next;  // Skip sentinel
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    
    return current->data;
}

/**
 * Returns the current size of the list
 * AI Use: Written by own
 */
size_t list_size(const List *list) {
    return list ? list->size : 0;
}

/**
 * Checks if the list is empty
 * AI Use: Written by own
 */
bool list_is_empty(const List *list) {
    return list ? list->size == 0 : true;
}
