//
// Created by Sergio Shevchenko on 26/05/2020.
//

#ifndef MPI_WORD_COUNT_LINKED_LIST_H
#define MPI_WORD_COUNT_LINKED_LIST_H

#include <stdlib.h>
#include <stdio.h>

struct Node {
    void *data;
    struct Node *next, *prev;
};

struct LinkedList {
    struct Node *root, *tail;
    size_t _size;
};

static struct Node *ll_construct_node(void *data) {
    struct Node *temp = malloc(sizeof(struct Node));
    temp->data = data;
    temp->prev = NULL;
    temp->next = NULL;
    return temp;
}

static struct LinkedList *ll_construct_linked_list() {
    struct LinkedList *temp = malloc(sizeof(struct LinkedList));
    temp->root = NULL;
    temp->tail = NULL;
    temp->_size = 0;
    return temp;
}

/*
 * Locates a Node within the LinkedList based on the index.
 */
static struct Node *ll_find(struct LinkedList *list, unsigned int index) {
    if (index > list->_size)
        fprintf(stderr, "%s%d%s%d%c\n",
                "Error: Index Out of Bounds. Index was '",
                index, "\' but size is ", (int) list->_size, '.');
    else if (list->_size > 0)
        if (index == 0)
            return list->root;
        else if (index == list->_size - 1)
            return list->tail;
        else {
            struct Node *temp;

            if ((double) index / list->_size > 0.5) {
                // Seek from the tail.
                temp = list->tail;
                for (unsigned int i = (unsigned int) (list->_size - 1); i > index; i--)
                    temp = temp->prev;
            } else {
                // Seek from the root.
                temp = list->root;
                for (unsigned int i = 0; i < index; i++)
                    temp = temp->next;
            }

            return temp;
        }

    return NULL;
}

/*
 * Inserts a Node at the front of the LinkedList.
 */
static void ll_add(struct LinkedList *list, void *data) {
    struct Node *inserted = ll_construct_node(data);

    if (list->_size == 0) {
        list->root = inserted;
        list->root->next = NULL;
        list->root->prev = NULL;
        list->tail = list->root;
    } else {
        inserted->next = list->root;
        list->root->prev = inserted;
        list->root = inserted;
    }

    list->_size++;
}

/*
 * Inserts a Node at the end of the LinkedList.
 * O(1) complexity.
 */
static void ll_add_last(struct LinkedList *list, void *data) {
    if (list->_size == 0)
        ll_add(list, data);
    else {
        struct Node *added = ll_construct_node(data);
        added->prev = list->tail;
        list->tail->next = added;
        list->tail = added;
        list->_size++;
    }
}

/*
 * Inserts a Node at a given index inside the LinkedList.
 */
static int ll_add_at(struct LinkedList *list, unsigned int index, void *data) {
    if (index > list->_size) {
        fprintf(stderr, "%s%d%s%d%c\n",
                "Error: Index Out of Bounds. Index was '",
                index, "\' but size is ", (int) list->_size, '.');
        return 1;
    } else if (index == 0)
        ll_add(list, data);
    else if (index == list->_size)
        ll_add_last(list, data);
    else {
        struct Node *temp = ll_find(list, index),
                *added = ll_construct_node(data);
        added->prev = temp->prev;
        added->next = temp;
        temp->prev->next = added;
        temp->prev = added;
        list->_size++;
    }

    return 0;
}

/*
 * Clear the LinkedList of Nodes.
 * O(1) complexity.
 */
static void ll_clear(struct LinkedList *list) {
    list->root = NULL;
    list->tail = NULL;
    list->_size = 0;
}

// Remove's the first Node in the LinkedList.
// O(1) complexity.
static void ll_remove_first(struct LinkedList *list) {
    if (list->_size > 0) {
        if (list->_size == 1)
            ll_clear(list);
        else {
            list->root = list->root->next;
            list->root->prev = NULL;
            list->_size--;
        }
    }
}

// Remove's the last Node in the LinkedList.
// O(1) complexity.
static void ll_remove_last(struct LinkedList *list) {
    if (list->_size > 0) {
        if (list->_size == 1)
            ll_clear(list);
        else {
            list->tail = list->tail->prev;
            list->tail->next = NULL;
            list->_size--;
        }
    }
}

// Remove's a Node at a given index.
static int ll_remove_at(struct LinkedList *list, unsigned int index) {
    if (index >= list->_size) {
        fprintf(stderr, "%s%d%s%d%c\n",
                "Error: Index Out of Bounds. Index was '",
                index, "\' but size is ", (int) list->_size, '.');
        return 1;
    } else if (index == 0)
        ll_remove_first(list);
    else if (index == list->_size - 1)
        ll_remove_last(list);
    else {
        struct Node *temp = ll_find(list, index);
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
        list->_size--;
    }

    return 0;
}

// Remove's the first Node whose data matches the parameter, if it exists.
static int ll_remove(struct LinkedList *list, void *data) {
    struct Node *temp = list->root;
    while (temp != NULL) {
        if (temp->data == data) {
            if (list->_size == 1)
                ll_clear(list);
            else if (temp->prev == NULL)
                ll_remove_first(list);
            else if (temp->next == NULL)
                ll_remove_last(list);
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
                list->_size--;
            }

            return 0;
        }
        temp = temp->next;
    }

    return 1;
}

// Prints out the LinkedList to the terminal window.
// O(n) complexity.
static void ll_print(struct LinkedList *list) {
    printf("%c", '{');

    struct Node *temp = list->root;
    while (temp != NULL) {
        printf(" %s", (char *) temp->data);
        if (temp->next != NULL)
            printf("%c", ',');
        temp = temp->next;
    }

    printf(" }\n");
}

// Copies a given LinkedList and returns the cloned version.
// O(n) complexity.
static struct LinkedList *ll_clone(struct LinkedList *list) {
    if (list == NULL)
        return NULL;

    struct LinkedList *copy = ll_construct_linked_list();
    struct Node *root = list->root;

    while (root != NULL) {
        ll_add_last(copy, root->data);
        root = root->next;
    }

    return copy;
}

static size_t ll_size(struct LinkedList *list) {
    return list->_size;
}

#endif //MPI_WORD_COUNT_LINKED_LIST_H
