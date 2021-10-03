int fork_fn()
{
    for (int i = 0; i < 5; i++) {
        if (fork() == 0) {
            compute(i);
        }
    }
    for (int i = 0; i < 5; i++){
        // wait(NULL), waits for any child process. In for loop to wait 5 times for each child.
        wait(NULL);
    }
    return 0;
}