#include <stdio.h>
#include "ai_common.h"

static void clear_input_buffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {
        /* discard */
    }
}

int main(void) {
    while (1) {
        int n;

        printf("メニュー\n");
        printf("1: 貸出\n");
        printf("2: 返却\n");
        printf("3: 検索\n");
        printf("4: 貸出履歴\n");
        printf("1-4の数字を入力してください: ");

        if (scanf("%d", &n) != 1) {
            printf("1-4の数字を入力してください。\n");
            clear_input_buffer();
            continue;
        }
        clear_input_buffer();

        if (n == 1) {
            do_checkout_book();
        } else if (n == 2) {
            return_screen();
        } else if (n == 3) {
            search();
        } else if (n == 4) {
            history();
        } else {
            printf("1-4の数字を入力してください。\n");
        }
    }

    return 0;
}