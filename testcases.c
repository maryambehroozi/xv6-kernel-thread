#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"

#define NUM_THREADS 10
#define SLEEP_TIME 5
#define SLEEP_TIME1 1000

lock_t lock, lock1, lock2;
int shared_counter = 0, shared_resource = 0;

void thread_function_concurrent(void* arg1, void* arg2) {
  for (int i = 0; i < 100; ++i) {
    lk_acquire(&lock);
    shared_counter++;
    lk_release(&lock);
    sleep(SLEEP_TIME);
  }
  exit();
}

void thread_function1(void* arg1, void* arg2) {
  lk_acquire(&lock1);
  printf(1, "Thread 1 acquired lock1\n");
  sleep(SLEEP_TIME1);

  lk_acquire(&lock2);
  printf(1, "Thread 1 acquired lock2\n");
  shared_resource++;
  printf(1, "Thread 1 incremented shared resource: %d\n", shared_resource);
  sleep(SLEEP_TIME1);

  lk_release(&lock2);
  printf(1, "Thread 1 released lock2\n");
  lk_release(&lock1);
  printf(1, "Thread 1 released lock1\n");
  exit();
}

void thread_function2(void* arg1, void* arg2) {
  lk_acquire(&lock2);
  printf(1, "Thread 2 acquired lock2\n");
  sleep(SLEEP_TIME1);

  lk_acquire(&lock1);
  printf(1, "Thread 2 acquired lock1\n");
  shared_resource++;
  printf(1, "Thread 2 incremented shared resource: %d\n", shared_resource);
  sleep(SLEEP_TIME1);

  lk_release(&lock1);
  printf(1, "Thread 2 released lock1\n");
  lk_release(&lock2);
  printf(1, "Thread 2 released lock2\n");
  exit();
}

int main(int argc, char *argv[]) {
  lk_init(&lock);

  for (int i = 0; i < NUM_THREADS; i++) {
    th_create(&thread_function_concurrent, (void*) 0, (void*)0);
  }

  for (int i = 0; i < NUM_THREADS; i++) {
    th_join();
  }
  printf(1, "Final value of shared counter: %d\n", shared_counter);

  lk_init(&lock1);
  lk_init(&lock2);

  int tid1 = th_create(&thread_function1, (void*)0, (void*)0);
  int tid2 = th_create(&thread_function2, (void*)0, (void*)0);
  th_join(tid1);
  th_join(tid2);
  printf(1, "Final value of shared resource: %d\n", shared_resource);
  
  

  exit();
  return 0;
}

