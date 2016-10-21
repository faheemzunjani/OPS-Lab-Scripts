#include<stdio.h>
#include<pthread.h>

void *thread_fn(void *arg){
  long id =(long) arg;
  printf("Starting thread %ld\n", id);
  sleep(5);
  printf("Exiting thread %ld\n", id);
  return NULL;
}

int main(){
 pthread_t t1,t2;
 
 pthread_create(&t1,NULL,thread_fn,(void *)1);
 pthread_create(&t2,NULL,thread_fn,(void *)2);
 pthread_join(t1,NULL);
 printf("Exiting main\n");
 return 0;
}
