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
        free(list->contents); // Free old declared array
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