//  SPDX-License-Identifier: GPL-2.0-only
//  MLStreams                                                                                           
//  Copyright (c) 2001-2023, Bryan Hinton                                                               
//  All rights reserved. 
//
//  echoserv.cpp
//
//  Created by Bryan R. Hinton, on Mon Mar 25 2002, 19:38:56 CST
//
//  NOTES:  
//
//			The echoserver runs as a daemon.
//			After you are done testing it: 
//
//			1.  Kill the echoserver process
//			    pkill -9 echoserv
//
//			2.  Remove the local socket pathnames
//				rm /tmp/unix.statpath
//
///////////////////////////////////////////////////////////////

extern "C"
{
#include <sys/time.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <fcntl.h>
#include <netdb.h>
#include <signal.h>
#include <math.h>
#include <strings.h>
#include <sys/uio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/un.h>
}




// UNIX domain socket local filesystem pathnames
#define STAT_PATH "/tmp/unix.statpath"
#define STAT 3


// declare a typedef for a pointer to a function
// used by util_thread to setup stat, enq, and deq threads
typedef void* (*StartFunction)(void* arg);

// read some bytes terminated by a newline from a socket descriptor
int
Read_line(int sock_fd, char *buffer, int size)
{

   // init tmp pointer to beginning of buffer
   char *read_ptr = buffer;

   bool done = false;

   // number of bytes left in the array
   // that we "can" read. (i.e. empty space left in the array )
   int bytes_toread = size;

   // number of bytes just read
   int n;

   // handle interrupted system calls, subdivided reads
   // and terminated client connections
   do {

      n = read(sock_fd, read_ptr, bytes_toread);

      // if we read > 0 bytes
      if(n > 0) {
         // if the last byte read is not a newline
         if((*(read_ptr + n-1) != '\n') ) {
            // place the read ptr at the byte
            // after the last byte we just read
            read_ptr = (read_ptr + n);
            // decrement number of empty spaces
            // left in the array
            bytes_toread -= n;
            // keep going
            done = false;
         } else // we are done. we read a newline
            done = true;
      } else if(n == 0) {
         return 0; // other end terminated connection
      }
      // n < 0, i.e. n == -1



      else {
         if(errno == EINTR) // interrupted system call
            done = false; // keep going
         else
            return -1; // error, errno != EINTR
      }

   }
   while(!done && bytes_toread > 0);

   return 1;

}

// Write "n" bytes to a descriptor.
ssize_t
Writen(int fd, const char *vptr, size_t n)
{
   size_t		nleft;
   ssize_t		nwritten;
   const char	*ptr;

   // init ptr to beginning of array
   ptr = vptr;

   // number of bytes left to write
   nleft = n;

   while (nleft > 0) {
      if ( (nwritten = write(fd, ptr, nleft)) <= 0) {
         if (errno == EINTR) // interrupted system call
            nwritten = 0;		// call write() again
         else
            return(-1);			// error
      }

      nleft -= nwritten; // decrement number of bytes left to write
      ptr   += nwritten; // increment number of bytes written
   }
   return(n); // return number of bytes written
}

// enq service thread



// stat service thread
void*
stat_thread(void *arg)
{
   int fd = *((int*)(arg));

   sigset_t newset;
   // empty out signal set
   sigemptyset(&newset);

   // add appropriate sigs to block to set
   sigaddset(&newset, SIGUSR1);
   sigaddset(&newset, SIGUSR2);
   sigaddset(&newset, SIGCHLD);

   // block SIGUSR1, SIGUSR2, and SIGCHLD from this thread
   // we don't want this thread receiving the timer signal
   // or the SIGCHLD signal from the scheduler thread
   pthread_sigmask(SIG_BLOCK, &newset, NULL);

   ssize_t n;
   char line[4096];

   if(Read_line(fd, line, 4096) == 0)
      return 0;

   int opt;
   uid_t id;

   //sscanf(line, "%d %d" , &opt, &id);

   strcat(line, "\n");
   Writen(fd, line, strlen(line)); // tell client we read pid successfully from him
   //write_queue(fd, id, opt);
   close(fd);
}

// 3 servers in one.
// three threads are created on this function
// one thread for each type of server( enq, deq, stat )
// the function chooses the type of server from
// three predefined types based on the argument( arg )
void*
util_thread(void *arg)
{
   // SIGUSR1 and SIGUSR2 will be sent by the timer
   // in the scheduler thread. we don't want this thread
   // receiving those signals. in addition, we only
   // want the scheduler thread to receive SIGCHLD from
   // terminated child process in the scheduler thread
   sigset_t newset;
   sigemptyset(&newset);
   sigaddset(&newset, SIGUSR1);
   sigaddset(&newset, SIGUSR2);
   sigaddset(&newset, SIGCHLD);
   // mask signals from this thread
   pthread_sigmask(SIG_BLOCK, &newset, NULL);


   pthread_attr_t attr_object;
   pthread_attr_init(&attr_object);
   // give this thread system scheduling scope
   pthread_attr_setscope(&attr_object, PTHREAD_SCOPE_SYSTEM);

   int	listenfd, connfd;
   pid_t	childpid;
   socklen_t	clilen;
   struct sockaddr_un	cliaddr, servaddr;

   bzero(&servaddr, sizeof(servaddr)); // zero out the server address structure
   // create local UNIX domain stream socket
   listenfd = socket(AF_UNIX, SOCK_STREAM, 0);

   // depending on the type of server thread
   // which is inferred from the arg parameter to this function,
   // the subsequent if statements will set this this function pointer
   // to point to a service function that will be called when
   // an enq, deq, or stat request is received.
   // this saved writing code( duplicating ) for three
   // different server functions
   StartFunction s;

   // server type of thread
   int id = *((int*)(arg));

      s = stat_thread;
      // unlink local filesystem pathname
      unlink(STAT_PATH);
      // copy local filesystem pathname for UNIX
      // domain socket( stat ) into address structure
      strcpy(servaddr.sun_path, STAT_PATH);

   // protocol family: local unix domain
   servaddr.sun_family = AF_UNIX;
   // bind the protocol address to the socket
   bind(listenfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

   // begin accepting connections on the socket
   // 1024 = max # of connections queued on this socket
   listen(listenfd, 1024);

   pthread_t tid;

   // server code( loops forever )
   for ( ; ; ) {
      clilen = sizeof(cliaddr);
      // when a new connection arrives, accept will return a file
      // descriptor that can be used to read/write this connection
      if ( (connfd = accept(listenfd, (struct sockaddr *) &cliaddr, &clilen)) < 0) {
         if (errno == EINTR) // interrupted system call
            continue;
         else
            ; // error
      }

      // make a copy of the connected file descriptor
      // we are about to spawn a thread to service the client
      // and then we will listen on the connection for more requests.
      // if we don't make a copy of tmp_fd, and instead pass it's address
      // to the service thread, a context switch could occur and overwrite
      // the connected descriptor and then the service thread would
      // lose the connection
      int tmp_fd = connfd;

      // create service thread
      pthread_create(&tid, &attr_object, s, (void*)(&tmp_fd));
      // parent closes connected socket
   }

}

// null signal handler
void
nullhandler(int signo, siginfo_t *evp, void *ucontext)
{ }


int
main(int argc, char **argv)
{

   // remove socket pathnames from filesystem if they already exist
   remove(STAT_PATH);

   pid_t pid;

   // --setup daemon--
   // fork a child and let the parent terminate
   // this will run the child in the background
   // and ensure that the child is not a process
   // group leader( required for setsid() )
   if( (pid = fork()) != 0)
      exit(0);

   // create a new session. detach from
   // controlling terminal
   // process becomes session leader, group leader
   // of a new process group
   setsid();

   signal(SIGHUP, SIG_IGN);

   // fork again to ensure that the daemon cannot
   // aquire a controlling terminal in the future
   if( (pid = fork()) != 0)
      exit(0);

   // set file creation mask to 0
   umask(0);

   // close all open file descriptors
   for(int i = 0; i < 64; i++)
      close(i);

   // the actual sched thread will be setting up the timers,
   // so we don't want the main thread to receive timer signals
   sigset_t newmask;
   sigemptyset(&newmask);
   sigaddset(&newmask, SIGCHLD);
   sigaddset(&newmask, SIGUSR1);
   sigaddset(&newmask, SIGUSR2);
   sigprocmask(SIG_BLOCK, &newmask, NULL);

   // create utility threads
   pthread_t stat_tid;
   pthread_t enq_tid;
   pthread_t deq_tid;
   pthread_t sched_tid;

   int tmp, tmp2, tmp3;

   pthread_attr_t attr_object;
   pthread_attr_init(&attr_object);

   // system scheduling scope for the server threads
   pthread_attr_setscope(&attr_object, PTHREAD_SCOPE_SYSTEM);

   // create thread to listen for stat requests
   tmp3 = 3;
   pthread_create(&stat_tid, &attr_object, util_thread, (void*)(&tmp3));

   // wait on scheduler thread( i.e. forever )
   pthread_join(stat_tid, NULL);

   return 0;
}
