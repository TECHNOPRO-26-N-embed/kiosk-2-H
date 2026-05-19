#include <stdio.h>

#define MAX_NOW 5
#define MAX_PAST 5
#define MAX_ID 100000 // ユーザーの最大値（10^5）

typedef struct {
    int id;
    char name[256];
    // char phonenumber[256];
    // char mail[256];
    // char address[256];
    // int now_books[MAX_NOW];
    // int past_books[MAX_PAST];
} User;

void history();

void view_history(User up[], int n, int target_id) {
    int flag = 0;
    for (int i = 0; i < n; i++) {
        if (up[i].id == target_id) {
            printf("ユーザーID: %d\n", up[i].id);
            printf("ユーザー名: %s\n", up[i].name);

            // 履歴を表示
            // printf("現在貸出中の本:\n");
            // for (int j = 0; j < MAX_NOW; j++) {
            //     printf("%d ", up->now_books[j]);
            // }
            // printf("\n");

            // printf("過去に貸出した本:\n");
            // for (int k = 0; k < MAX_PAST; k++) {
            //     printf("%d ", up->past_books[k]);
            // }
            // printf("\n");
            flag = 1;
            break;
        }
    }
    
    if (!flag) {
        int menu;
        printf("ユーザーが見つかりませんでした。\n");
        printf("0: メニューに戻る\n");
        printf("1: IDを再入力する\n");
        scanf("%d", &menu);
        if(menu == 0) {
            return;
        } else if(menu == 1) {
            history();
        } else {
            printf("無効な入力です。メニューに戻ります。\n");
            return;
        }
    }
}

void history(void) {
    int user_id;
    printf("ユーザーIDを入力してください: ");
    scanf("%d", &user_id);

    User users[] = {
        {1, "Asan"},
        {2, "Bsan"},
        {3, "Csan"}
    };

    // idで線形探索（構造体配列Userを探索）
    // 二部探索
    int n = 3;
    view_history(users, n, user_id);

    // return 0;
}