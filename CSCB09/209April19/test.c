#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

int main(void)
{
	int i = 0;
	printf("Broccoli\n");
	int r = fork();
	printf("Cucumbers\n");
	if (r == 0) {
		printf("Kale\n");
		int k = fork();
		if (k >= 0) {
			printf("Peppers\n");
		}
	} else if (r > 0) {
		wait(NULL);
		printf("Cabbage\n");
		while(fork() == 0) {
			printf("Carrots\n");
			i++;
			if(i == 3) break;
		}
		i = 0;
		while(fork() > 0) {
			printf("Spinach\n");
			i++;
			if(i == 2) break;
		}
	}
	return 0;
}