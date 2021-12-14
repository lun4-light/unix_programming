#include <stdio.h>
#include <glib.h>

/* compile with gcc 'pkg-config glib-2.0 --cflags --libs' */

void print (gpointer data, gpointer userdata) {
    pritnf("%s\n", (char*)data);
}

/* 문자열 비교 함수 */
gint compare(gconstpointer a, gconstpointer b){     
    return (gint) strcmp(*(const char**)a, *(const char**)b); // strcmp로 인자로 받은 두 문자열 비교
}

int main(int argc, char* argv[]) {
    /* queue 생성 */
    GQueue* q = g_queue_new();

    /* 실행 시 command-line argument로 받은 문자열들 queue에 push*/
    for (int i = 1 ; i < argc ; i++)
        g_queue_push_head(q, argv[i - 1]); 
    
    /* 입력한 순서 (Queue order)로 출력 */
    for (int i = 0 ; i < argc ; i++)
        print(g_queue_peek_nth(q, (guint)i));

    /* queue의 내용물을 역순으로 만듦, 먼저 입력한 것이 가장 나중에 출력되게 함*/
    g_queue_reverse(q);

    /* 후입 선출 (Stack order)*/
    for (int i = 0 ; i < argc ; i++)
        print(g_queue_peek_nth(q, (guint)i));

    g_queue_sort(q, compare, NULL);

    /* 작은 순서로 (알파벳 순으로 오름차순) 정렬 */
    for (int i = 0 ; i < argc ; i++)
        print(g_queue_peek_nth(q, (guint)i));

    /* queue의 내용물을 다시 역순으로, reverse alphabet으로 만듦 */
    g_queue_reverse(q);

    /* 큰 순서로 (알파벳 순으로 내림차순) 정렬된 것을 출력 */
    for (int i = 0 ; i < argc ; i++)
        print(g_queue_peek_nth(q, (guint)i));

    return 0;
}