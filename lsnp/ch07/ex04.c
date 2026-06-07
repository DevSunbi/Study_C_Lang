#include <stdio.h>
#include <unistd.h>
#include <signal.h>

int main( void)
{
   sigset_t sigset;
   sigset_t oldset;

   sigfillset( &sigset);
   sigprocmask( SIG_BLOCK, &sigset, &oldset);

   sigfillset( &sigset);
   sigdelset( &sigset, SIGINT);
   sigsuspend( &sigset);

   return 0;
}
