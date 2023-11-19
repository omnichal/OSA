#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // Fork returns process id
    // in parent process
    pid_t child_pid = fork();

    // Parent process
    if (child_pid > 0) {
        printf("Parent process (PID %d) created with child PID: %d\n", getpid(), child_pid);

        // Parent process sleeps for 50 seconds
        sleep(5);
        
        // Print a message before the parent process exits
        printf("Parent process exiting (PID %d)\n", getpid());
	system("ps");
    }

    // Child process
    else {
        printf("Child process (PID %d) exited\n", getpid());

        // Child process exits immediately
        exit(0);
    }

    return 0;
}
