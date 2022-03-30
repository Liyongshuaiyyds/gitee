#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

struct foo {
	int             f_count;
	pthread_mutex_t f_lock;
	int             f_id;
	/* ... more stuff here ... */
};

struct foo *
foo_alloc(int id) /* allocate the object */
{
	struct foo *fp;

	if ((fp = malloc(sizeof(struct foo))) != NULL) {
		fp->f_count = 1;
		fp->f_id = id;
		if (pthread_mutex_init(&fp->f_lock, NULL) != 0) {
			free(fp);
			return(NULL);
		}
		/* ... continue initialization ... */
	}
	return(fp);
}

void
foo_hold(struct foo *fp) /* add a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	fp->f_count++;
	pthread_mutex_unlock(&fp->f_lock);
}

void
foo_release(struct foo *fp) /* release a reference to the object */
{
	pthread_mutex_lock(&fp->f_lock);
	if (--fp->f_count == 0) { /* last reference */
		pthread_mutex_unlock(&fp->f_lock);
		pthread_mutex_destroy(&fp->f_lock);
		free(fp);
	} else {
		pthread_mutex_unlock(&fp->f_lock);
	}
}

void *
thr_fn1(void *arg)
{
	struct foo * data = (struct foo *) arg;
        while (1) {
	  sleep(1);
          foo_hold(data);
          printf("thread 1: ID is %lu value: %d\n", (unsigned long)pthread_self(), data->f_count);
	}

}

void *
thr_fn2(void *arg)
{
	struct foo * data = (struct foo *) arg;
        while (1) {
	  sleep(1);
          foo_hold(data);
          printf("thread 2: ID is %lu value: %d\n", (unsigned long)pthread_self(), data->f_count);
	}

}


int main()
{
  int             err;
  pthread_t       tid1, tid2;
  struct foo * data = foo_alloc(1);

  err = pthread_create(&tid1, NULL, thr_fn1, (void*)data);
  if (err != 0)
    printf("can't create thread 1\n");
  err = pthread_create(&tid2, NULL, thr_fn2, (void*)data);
  if (err != 0)
     printf("can't create thread 2");

  while(1) {
      sleep(1);
  }
  return 0;
}








