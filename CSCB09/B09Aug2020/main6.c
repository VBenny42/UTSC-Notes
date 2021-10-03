// parent code after both forks, part (c) 
close(ltr[0]);  // Closing pipes because parent doesn't use them
close(ltr[1]);
close(rtl[0]);
close(rtl[1]);
wait(NULL);
wait(NULL);
