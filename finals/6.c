#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

/* compile with gcc 'pkg-config glib-2.0 --cflags --libs' */

/* print func */
void print(gpointer data, gpointer userdata) {
    printf("%s\n", (char*)data);
}

/* 문자열 비교 함수 */
gint compare(gconstpointer a, gconstpointer b, gpointer userdata){     
    return (gint) strcmp(a, b); // strcmp로 인자로 받은 두 문자열 비교
}

int main(int argc, char* argv[]) {
    /* queue 생성 */
    GQueue* q = g_queue_new();

    /* 실행 시 command-line argument로 받은 문자열들 queue에 push*/
    for (int i = 1 ; i < argc ; i++)
        g_queue_push_tail(q, argv[i]); 
    
    /* 입력한 순서 (Queue order)로 출력 */
    g_queue_foreach(q, print, NULL);
    printf("\n");

    /* queue의 내용물을 역순으로 만듦, 먼저 입력한 것이 가장 나중에 출력되게 함*/
    g_queue_reverse(q);

    /* 후입 선출 (Stack order)*/
    g_queue_foreach(q, print, NULL);
    printf("\n");

    g_queue_sort(q, compare, (gpointer) NULL);

    /* 작은 순서로 (알파벳 순으로 오름차순) 정렬 */
    g_queue_foreach(q, print, NULL);
    printf("\n");

    /* queue의 내용물을 다시 역순으로, reverse alphabet으로 만듦 */
    g_queue_reverse(q);

    /* 큰 순서로 (알파벳 순으로 내림차순) 정렬된 것을 출력 */
    g_queue_foreach(q, print, NULL);
    printf("\n");

    return 0;
}