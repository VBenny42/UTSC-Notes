#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>

struct file {
    char *name;
    struct file *next;
};

void printlist(struct file *head) {
    for (struct file *temp = head; temp != NULL; temp = temp->next) {
        printf("%s -> ", temp->name);
    }
    printf("\n");
}

struct file *create(char *name) {
    struct file *node = (struct file *) calloc(1, sizeof(struct file));
    node->name = (char *) calloc(strlen(name) + 1, sizeof(char));
    strcpy(node->name, name);
    node->next = NULL;
    return node;
}

struct file *add(struct file *node, struct file *head) {
    if (head == NULL) {
        return node;
    }
    node->next = head;
    return node;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        fprintf(stderr, "Incorrect number of arguments\n");
    }
    if (chdir(argv[1]) == -1) {
        perror("chdir");
        return -1;
    }
    DIR *folder;
    folder = opendir(".");
    struct dirent *entry;
    struct file *head = NULL;
    if (folder == NULL) {
        fprintf(stderr, "Unable to read directory\n");
        return -1;
    }
    while ((entry = readdir(folder))) {
        if ((strcmp(entry->d_name, ".") == 0) || (strcmp(entry->d_name, "..") == 0)) {
            continue;
        }
        head = add(create(entry->d_name), head);
    }
    // printlist(head);
    return 0;
}