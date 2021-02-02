#include "shared_mutex.h"
#include <stdio.h>

int i = 0;

int main() {
  // Init shared mutex by a name, which can be used by
  // any other process to access the mutex.
  // This function both creates new and opens an existing mutex.
  shared_mutex_t mutex = shared_mutex_init("/my-mutex");
  if (mutex.ptr == NULL) {
    return 1;
  }

  if (mutex.created) {
    printf("The mutex was just created\n");
  }

  // Use pthread calls for locking and unlocking.
  pthread_mutex_lock(mutex.ptr);
  printf("Press eny key to unlock the mutex\n");
  i++;
  pthread_mutex_unlock(mutex.ptr);

  printf("i=%d\n", i);

  sleep(100);

  // Closing is used to release local resources, used by a mutex.
  // It's still available to any other process.
  if (shared_mutex_close(mutex)) {
    return 1;
  }
  return 0;
}
