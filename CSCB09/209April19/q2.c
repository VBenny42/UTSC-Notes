#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct array_list {
    int *contents;
    size_t capacity;      // Current capacity of the array
    size_t curr_elements; // Number of elements currently occupied in the array
};

int initialize(struct array_list *list) {
    if ((list->contents = (int *) calloc(5, sizeof(int))) == NULL) {
        perror("calloc");
        return -1;
    }
    list->capacity = 5;
    list->curr_elements = 0;
    return 0;
}

int add(int *int_list, int number, struct array_list *list) {
    if (number + list->curr_elements > list->capacity) {
        int *new_list;
        if ((new_list = (int *) calloc((2 * (number + list->curr_elements)), sizeof(int))) == NULL) {
            perror("calloc");
            return -1;
        }
        // Copy old contents to new array
        memcpy(new_list, list->contents, list->curr_elements * sizeof(int));
        // Free old declared array
        free(list->contents);
        // Copy new contents to new array
        memcpy((new_list + list->curr_elements), int_list, number * sizeof(int));
        list->contents = new_list;
        list->capacity = (2 * (number + list->curr_elements));
        list->curr_elements += number;
        return 0;
    }
    memcpy(list->contents + list->curr_elements, int_list, number * sizeof(int));
    list->curr_elements += number;
    return 0;
}

int main(void) {
    struct array_list list;
    initialize(&list);
    int a[11] = {2, 0, 9, 4, 5, 6, 7, 8, 9, 10, 11};
    add(a, 11, &list);
    // The loop below should print "2 0 9 4 5 6 7 8 9 10 11 "
    for(int i = 0; i < list.curr_elements; i++)
        printf("%d ", list.contents[i]);
    /* The program does some fancy stuff with the array here,
     * generates some output, and performs any remaining
     * cleanup before terminating.
     */
return 0; }