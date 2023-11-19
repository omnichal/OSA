#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/types.h>

int main()
{
pid_t child_process = fork();
if (child_process < 0){
printf("fork failed");
return 1;
}
if (child_process == 0){
printf("child process is executing (PID %d) " , getpid());
}else{
printf("Parent process (PID %d) created with child PID: %d \n",getpid(),child_process);
sleep(10);
printf("parent process exiting PID %d ", getpid());
system("ps");
}
return 0;

}
