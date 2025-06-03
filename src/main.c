#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <assert.h>
#include <mxml.h>

void work(void) {
  const char path[] = "./test.xml";
  mxml_node_t *xml = mxmlLoadFilename(NULL, NULL, path);
  if (xml == NULL) {
    fprintf(stderr, "ERROR : cant load test file with path \"%s\"", path);
    exit(EXIT_FAILURE);
  }
  mxmlDelete(xml);
}

void *thread_task(void *args) {
  (void)(args);
  work();
	pthread_exit(NULL);
}

int main(void) { // main 1
  work();
}

// int main(void) { // main 2
//   // work(); <- comment 1
// 	pthread_t thread;
// 	assert(pthread_create(&thread, NULL, thread_task, NULL) == 0);
// 	assert(pthread_join(thread, NULL) == 0);
// 	return EXIT_SUCCESS;
// }

// #define NB_THREADS 3
// int main(void) { // main 3
//   // work(); <- comment 2
// 	pthread_t threads[NB_THREADS];
// 	for (size_t i = 0; i < NB_THREADS; ++i) {
//   	assert(pthread_create(&threads[i], NULL, thread_task, NULL) == 0);
// 	}
// 	for (size_t i = 0; i < NB_THREADS; ++i) {
//   	assert(pthread_join(threads[i], NULL) == 0);
// 	}
// 	return EXIT_SUCCESS;
// }
