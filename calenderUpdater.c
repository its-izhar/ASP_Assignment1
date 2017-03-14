/**
* @Author: Izhar Shaikh <izhar>
* @Date:   2017-03-06T17:03:58-05:00
* @Email:  izharits@gmail.com
* @Filename: calenderUpdater.c
* @Last modified by:   izhar
* @Last modified time: 2017-03-14T19:45:26-04:00
* @License: MIT
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>




int main(int argc, char const *argv[])
{
  int fd[2] = {-1, -1};

  #define P1WR fd[1]    // Process-1 write end
  #define P2RD fd[0]    // Process-2 read end

  // Create a pipe
  if( pipe(fd) < 0 ){
    perror("pipe");
    exit(1);
  }

  // Child process - 1
  int pid = fork();
  if(pid < 0){
    perror("Child: EmailFilter");
    exit(1);
  }
  else if(pid == 0)
  {
    // Child process (emailFilter)
    close(P2RD);
    dup2(P1WR, STDOUT_FILENO);        // Reditrect STDOUT to write end of the pipe
    // Execute the process here
    execlp("./emailFilter", "emailFilter", NULL);
    // Unexpected exit
    perror("exec error");
    exit(1);
  }

  // Child process - 2
  pid = fork();
  if(pid < 0){
    perror("Child: calenderFilter");
    exit(1);
  }
  else if(pid == 0)
  {
    // Child process (emailFilter)
    close(P1WR);
    dup2(P2RD, STDIN_FILENO);         // Reditrect STDIN to read end of this process
    // Execute the process here
    execlp("./calenderFilter", "calenderFilter", NULL);
    // Unexpected exit
    perror("exec error");
    exit(1);
  }
  // close both the ends in parent
  close(P1WR);
  close(P2RD);

  // wait for both processes to end
  wait(NULL);
  wait(NULL);

  return 0;
}
