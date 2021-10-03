int is_present_helper(FILE *f, int needle, long file_pos) {
    if (file_pos == -1L) {
        return 0;
    }
    fseek(f, file_pos, SEEK_SET);
    node root;
    fread(&root, sizeof(root), 1, f);
    if (root.key == needle) {
        return 1;
    }
    if (root.key > needle) {
        return is_present_helper(f, needle, root.left);
    }
    else {
        return is_present_helper(f, needle, root.right);
    }
}

int is_present(FILE *f, int needle) {
    return is_present_helper(f, needle, 0);
}