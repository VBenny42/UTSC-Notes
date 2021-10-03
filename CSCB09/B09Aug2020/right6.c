// right child code , part (b) 
close(ltr[1]);  // Close unnecessary writing end
dup2(ltr[0], STDIN_FILENO);
close(ltr[0]);  // Close duplicate fd
close(rtl[0]);  // Close unnecessary reading end
dup2(rtl[1], STDOUT_FILENO);
close(rtl[1])   // Close duplicate fd
execlp("right", "right", (char*)NULL); 
exit(1);
