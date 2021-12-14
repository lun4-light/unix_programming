#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

#define N 100000000


/* 기본 변수 정의 */
unsigned int s = 0;
pthread_mutex_t mutex;

void *c(void *d) {
    int i;
    for (i = 0; i < N; i++) {
        /* critical section 진입 */
        pthread_mutex_lock(&mutex);     // mutex를 사용하여 다른 thread에서 이 변수를 사용할 수 없도록 함
        s++;
        pthread_mutex_unlock(&mutex);   // mutex로 잠겨있는 변수 해제
        /* critical section 종료 */
    }
    return NULL;
}

int main(void) {
    pthread_t t[2];
    int r;

    pthread_mutex_init(&mutex, NULL);   // mutex 초기화
    r = pthread_create(&t[0], NULL, c, NULL);   //  t[0] 식별자를 바탕으로 thread 생성, thread 함수는 c
    if (r) {                            // 생성 실패시
        perror("Thread create: ");
        exit(1);
    }

    r = pthread_create(&t[1], NULL, c, NULL);   //  t[1] 식별자를 바탕으로 thread 생성, thread 함수는 c
    if (r) {                            // 생성 실패시
        perror("Thread create: ");
        exit(2);
    }

    pthread_join(t[0], NULL);           // t[0] 종료 대기
    pthread_join(t[1], NULL);           // t[1] 종료 대기

    printf("%u\n", s);                  
    
    pthread_mutex_destroy(&mutex);      // 동적으로 할당된 mutex 제거

    return 0;
}