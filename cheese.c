
#include <stdio.h>
#include "threading.h"


volatile __uint32_t main_lock = 0;
volatile __int32_t main_sema = 0;
volatile int counter = 0;
int NUM_THREADS_TO_WAIT_FOR = 8;

void thread_entry(int cid, int nc)
{
  // multi-threaded programs override this function.
  // for the case of single-threaded programs, only let core 0 proceed.

  low_lock_aquire(&main_lock);
  int temp = counter;
  printf("hello from core! ");
  printf("This is core %d of %d\n", cid, nc);
  counter = temp + 1;
  low_lock_release(&main_lock);
  
  low_sema_up(&main_sema);

  while (cid != 0);
}

int main() {
    // wait for all threads to complete
    for (int a = 0; a < NUM_THREADS_TO_WAIT_FOR; a++) {
      low_sema_down(&main_sema);
    }
    
    low_lock_aquire(&main_lock);
    printf("Hello from main!\n");
    printf("Value of lock-protected counter: %d\n", counter);
    printf("Value of sema: %d\n", main_sema);
    low_lock_release(&main_lock);
    return 0;
}

