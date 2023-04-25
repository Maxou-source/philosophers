/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mparisse <mparisse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/16 20:13:20 by mparisse          #+#    #+#             */
/*   Updated: 2023/04/16 20:14:54 by mparisse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* CELEBP27 */
#define _OPEN_THREADS
#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void *thread(void *arg) {
  char *ret;
  printf("thread() entered with argument '%s'\n", (char *)arg);
  if ((ret = (char*) malloc(20)) == NULL) {
    perror("malloc() error");
    exit(2);
  }
  strcpy(ret, "This is a test");
  pthread_exit(ret);
}

main() {
  pthread_t thid;
  void *ret;

  if (pthread_create(&thid, NULL, thread, "thread 1") != 0) {
    perror("pthread_create() error");
    exit(1);
  }

  if (pthread_join(thid, &ret) != 0) {
    perror("pthread_create() error");
    exit(3);
  }

  printf("thread exited with '%s'\n", ret);
}