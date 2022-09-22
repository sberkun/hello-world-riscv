#include <stdint.h>


/* A lock is a __uint32_t that is set to 0 for unlocked, and 1 for locked */
void low_lock_aquire(volatile __uint32_t* lock);

/* A lock is a __uint32_t that is set to 0 for unlocked, and 1 for locked */
void low_lock_release(volatile __uint32_t* lock);

/* A semaphore is a __uint32_t that represents the counter */
void low_sema_down(volatile __uint32_t* sema);

/* A semaphore is a __uint32_t that represents the counter */
void low_sema_up(volatile __uint32_t* sema);