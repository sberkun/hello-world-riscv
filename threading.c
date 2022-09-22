#include "threading.h"


/* A lock is a __uint32_t that is set to 0 for unlocked, and 1 for locked */
void low_lock_aquire(volatile __uint32_t* lock) {
    __sync_synchronize();
    __uint32_t x = 1;
    do {
        asm volatile (
          "amoswap.w.aq %0, %1, (%2)" // aq = aquire sematics
          : "=r" (x) // outputs
          : "0"(x), "r"(lock) //inputs
          // "0" means will use same register for input x and output x 
          : // clobbers
        );
    } while (x != 0);
    __sync_synchronize();
}

/* A lock is a __uint32_t that is set to 0 for unlocked, and 1 for locked */
void low_lock_release(volatile __uint32_t* lock) {
    __sync_synchronize();
    asm volatile (
        "amoswap.w.rl x0, x0, (%0)" // rl = release sematics
        : // outputs
        : "r"(lock) //inputs
        : // clobbers
    );
    __sync_synchronize();
}

/* A semaphore is a __uint32_t that represents the counter */
void low_sema_down(volatile __uint32_t* sema) {
    __sync_synchronize();
    __uint32_t x = 0;
    do {
        asm volatile (
          "amoswap.w.aq %0, x0, (%1)" // aq = aquire sematics
          : "=r"(x) // outputs
          : "r"(sema) //inputs 
          : // clobbers
        );
    } while (x == 0);

    // x represents the value of the counter before we set it to 0
    // want to add x-1 back to the counter
    x -= 1;
    asm volatile (
        "amoadd.w.rl x0, %0, (%1)" // rl = release sematics (releasing x-1)
        : // outputs
        : "r"(x), "r"(sema) //inputs
        : // clobbers
    );
    __sync_synchronize();
}

/* A semaphore is a __uint32_t that represents the counter */
void low_sema_up(volatile __uint32_t* sema) {
    __sync_synchronize();
    asm volatile (
        "li t0, 1\n"
        "amoadd.w.rl x0, t0, (%0)" // rl = release sematics
        : // outputs
        : "r"(sema) //inputs
        : "t0" // clobbers
    );
    __sync_synchronize();
}

