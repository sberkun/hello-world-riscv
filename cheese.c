
#include <stdio.h>


void low_lock_aquire(volatile __uint32_t* lock) {
    __sync_synchronize();
    asm (
        "li t0, 1\n"
        "1:\n"
        "amoswap.w.aq t0, t0, (%0)\n"
        "bnez t0, 1b"
        : // outputs
        : "r"(lock) //inputs
        : "t0" // clobbers
    );
    __sync_synchronize();
}

void low_lock_release(volatile __uint32_t* lock) {
    __sync_synchronize();
    asm (
        "amoswap.w.rl x0, x0, (%0)"
        : // outputs
        : "r"(lock) //inputs
        : // clobbers
    );
    __sync_synchronize();
}


volatile __uint32_t main_lock;
volatile int cheese = 0;

void thread_entry(int cid, int nc)
{
  // multi-threaded programs override this function.
  // for the case of single-threaded programs, only let core 0 proceed.

  low_lock_aquire(&main_lock);
  int banana = cheese;
  printf("hello from core! ");
  printf("This is core %d of %d\n", cid, nc);
  cheese = banana + 1;
  low_lock_release(&main_lock);
  

  while (cid != 0);
}

int fib(int n) {
  if (n < 2) {
    return n;
  }
  return fib(n-1) + fib(n-2);
}

int main() {
    
    int fib_result = fib(30);
    low_lock_aquire(&main_lock);
    printf("I like cheese too %d %d\n", cheese, fib_result);
    low_lock_release(&main_lock);
    return 0;
}

