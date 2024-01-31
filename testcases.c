#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"


lock_t* lk;



void add(void* arg1, void* arg2) {
  lk_acquire(lk);
  int num1 = *(int*)arg1;
  int num2 = *(int*)arg2;
  printf(1, "%d + %d = %d\n", num1, num2, num1 + num2);
  lk_release(lk); 
  exit();
}
void sub(void* arg1, void* arg2) {
  lk_acquire(lk);
  int num1 = *(int*)arg1;
  int num2 = *(int*)arg2;
  printf(1, "%d - %d = %d\n", num1, num2, num1 - num2);
  lk_release(lk); 
  exit();
}
void mul(void* arg1, void* arg2) {
  lk_acquire(lk);
  int num1 = *(int*)arg1;
  int num2 = *(int*)arg2;
  printf(1, "%d * %d = %d\n", num1, num2, num1 * num2);
  lk_release(lk); 
  exit();
}


int main(int argc, char *argv[])
{
  lk_init(lk) ; 
  printf(1, "test executing threads with lock :\n");
  int arg1 = 9, arg2 = 1 ; 
  th_create(&add, (void *)&arg1, (void *)&arg2);
  th_create(&sub, (void *)&arg1, (void *)&arg2);
  th_create(&mul, (void *)&arg1, (void *)&arg2);
  int arg3 = 4 , arg4 = 2;
  th_create(&add, (void *)&arg3, (void *)&arg4);
  th_create(&sub, (void *)&arg3, (void *)&arg4);
  th_create(&mul, (void *)&arg3, (void *)&arg4);
  int arg5 = 7 ,  arg6 = 4;
  th_create(&add, (void *)&arg5, (void *)&arg6);
  th_create(&sub, (void *)&arg5, (void *)&arg6);
  th_create(&mul, (void *)&arg5, (void *)&arg6);
  th_join();
  th_join();
  th_join();
  th_join();
  th_join();
  th_join();
  th_join();
  th_join();
  th_join();
  exit() ; 
}






// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------



// #include "types.h"
// #include "user.h"

// #define THREAD_COUNT 5
// #define WORK_DURATION 50

// int global_counter = 0;  // Global counter to distinguish between different threads

// void threadFunction(void *arg1, void *arg2) {
//     int thread_id = *(int *)arg1;
//     int work_time = *(int *)arg2;
//     printf(1, "Thread %d: Starting task for %d ticks\n", thread_id, work_time);

//     // Simulate task processing by sleeping
//     sleep(work_time);

//     printf(1, "Thread %d: Task completed\n", thread_id);
//     exit();  // Thread exits after finishing the task
// }

// int main(int argc, char *argv[]) {
//     int i;
//     int pid;
//     int duration = WORK_DURATION;

//     for (i = 0; i < THREAD_COUNT; ++i) {
//         pid = fork();  

//         if (pid < 0) {
//             printf(1, "Fork failed\n");
//             exit();
//         } else if (pid == 0) {
//             global_counter++;  
//             int thread_id = global_counter;

        
//             void *stack = malloc(4096);
//             if (!stack) {
//                 printf(1, "Failed to allocate stack\n");
//                 exit();
//             }

//             clone(threadFunction, &thread_id, &duration, stack);

//             while (1) {
//                 sleep(100);
//             }

//             free(stack);
//             exit();
//         }
//     }

//     for (i = 0; i < THREAD_COUNT; ++i) {
//         wait(); 
//     }

//     printf(1, "All threads have completed their tasks\n");

//     exit();
// }




// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------




// #include "types.h"
// #include "stat.h"
// #include "user.h"
// #include "fcntl.h"
// #define SLEEP_DURATION 100

// lock_t* lock;

// void task1(void* arg1, void* arg2) {
//   int shouldLock = *(int*)arg1;
//   if (shouldLock) lk_acquire(lock);
//   printf(1, "Task1: Execution %s\n", shouldLock ? "with lock" : "without lock");
//   sleep(SLEEP_DURATION);
//   if (shouldLock) lk_release(lock);
//   exit();
// }

// void task2(void* arg1, void* arg2) {
//   int shouldLock = *(int*)arg1;
//   if (shouldLock) lk_acquire(lock);
//   printf(1, "Task2: Execution %s\n", shouldLock ? "with lock" : "without lock");
//   sleep(SLEEP_DURATION);
//   if (shouldLock) lk_release(lock);
//   exit();
// }

// void task3(void* arg1, void* arg2) {
//   int shouldLock = *(int*)arg1;
//   if (shouldLock) lk_acquire(lock);
//   printf(1, "Task3: Execution %s\n", shouldLock ? "with lock" : "without lock");
//   sleep(SLEEP_DURATION);
//   if (shouldLock) lk_release(lock);
//   exit();
// }

// int main(int argc, char *argv[]) {
//   lk_init(lock);
//   int arg1 = 1, arg2 = 1;

//   printf(1, "Controlled execution (with locks):\n");
//   th_create(&task1, (void *)&arg1, (void *)&arg2);
//   th_create(&task2, (void *)&arg1, (void *)&arg2);
//   th_create(&task3, (void *)&arg1, (void *)&arg2);
//   th_join();
//   th_join();
//   th_join();

//   exit();
// }



// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
// ------------------------------------------------------------
