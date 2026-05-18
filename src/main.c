#include<stdio.h>
// ヘッダーの入力

int main(void) {
    printf("メニュー\n");
    printf("1: 貸出\n");
    printf("2: 返却\n");
    printf("3: 検索\n");
    printf("4: 貸出履歴\n");
    
    printf("1-4の数字を入力してください: ");
    int n;
    scanf("%d",&n);

    // 条件に応じて各処理の関数を呼び出す。
    if (n == 1) {printf("分岐1");}
    else if (n == 2) {printf("分岐2");}
    else if (n == 3) {printf("分岐3");}
    else if (n == 4) {printf("分岐4");}
    else {
        printf("1-4の数字を入力してください; \n");
    }

    return 0;
}