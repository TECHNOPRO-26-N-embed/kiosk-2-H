#include<stdio.h>
// ヘッダーの入力
#include "rental.c"
#include "return.c"
#include "search.c"
#include "history.c"

int main(void) {
    while(1) {
        printf("メニュー\n");
        printf("1: 貸出\n");
        printf("2: 返却\n");
        printf("3: 検索\n");
        printf("4: 貸出履歴\n");
        
        printf("1-4の数字を入力してください: ");
        int n;
        scanf("%d",&n);

        // 条件に応じて各処理の関数を呼び出す。
        if (n == 1) {rental();}
        else if (n == 2) {return_book();}
        else if (n == 3) {search();}
        else if (n == 4) {history();}
        else {
            printf("1-4の数字を入力してください; \n");
        }
    }

    return 0;
}