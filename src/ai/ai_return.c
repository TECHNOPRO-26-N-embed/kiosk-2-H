#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai_common.h"

// #define MAX_USERS 100

// // 構造体定義（設計書準拠）
// typedef struct {
//     int book_id;
//     char title[100];
//     char author[100];
//     int status; // 0:貸出可, 1:貸出不可, 2:貸出中, 3:延滞
//     char due_date[20]; // 返却期限
// } Book;

// typedef struct {
//     int user_id;
//     char name[100];
//     int now_count;
//     Book now_books[10]; // 貸出中の本（最大10冊仮定）
// } User;

User_return users[MAX_USERS];
int user_count = 0;

static FILE* open_users_csv(void) {
    const char* candidates[] = {
        "data/test_users.csv",
        "../data/test_users.csv",
        "test_users.csv"
    };
    int i;

    for (i = 0; i < (int)(sizeof(candidates) / sizeof(candidates[0])); i++) {
        FILE* fp = fopen(candidates[i], "r");
        if (fp != NULL) {
            printf("Attempting to open file: %s\n", candidates[i]);
            return fp;
        }
    }

    perror("Failed to open CSV file");
    return NULL;
}

int load_users_from_csv(void) {
    FILE* file = open_users_csv();
    char line[1024];

    if (file == NULL) {
        printf("Ensure the file exists in the correct directory.\n");
        return -1;
    }

    user_count = 0;

    if (fgets(line, sizeof(line), file) == NULL) {
        fclose(file);
        return -1;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        User_return* user;
        int fields;

        if (user_count >= MAX_USERS) {
            break;
        }

        line[strcspn(line, "\r\n")] = '\0';
        if (line[0] == '\0') {
            continue;
        }

        user = &users[user_count];
        memset(user, 0, sizeof(User_return));

        fields = sscanf(
            line,
            "%d,%99[^,],%d,%d,%99[^,],%99[^,],%d,%19[^,],%d,%99[^,],%99[^,],%d,%19[^,]",
            &user->user_id,
            user->name,
            &user->now_count,
            &user->now_books[0].book_id,
            user->now_books[0].title,
            user->now_books[0].author,
            &user->now_books[0].status,
            user->now_books[0].due_date,
            &user->now_books[1].book_id,
            user->now_books[1].title,
            user->now_books[1].author,
            &user->now_books[1].status,
            user->now_books[1].due_date
        );

        if (fields < 3) {
            continue;
        }

        if (user->now_count < 0) {
            user->now_count = 0;
        }
        if (user->now_count > 10) {
            user->now_count = 10;
        }

        if (user->now_count >= 2 && fields < 13) {
            user->now_count = 1;
        }
        if (user->now_count >= 1 && fields < 8) {
            user->now_count = 0;
        }

        user_count++;
    }

    fclose(file);
    return 0;
}

// 返却画面本体
void return_screen() {
    int user_id, menu, i;

    if (load_users_from_csv() != 0) {
        printf("利用者データの読み込みに失敗しました。\n");
        return;
    }

    while (1) {
        printf("--------- 返却画面 ---------\n");
        printf("利用者IDを入力してください: ");
        if (scanf("%d", &user_id) != 1) {
            printf("数値で入力してください。\n");
            while(getchar() != '\n'); // 入力バッファクリア
            continue;
        }

        // 利用者検索
        User_return* user = NULL;
        for (i = 0; i < user_count; i++) {
            if (users[i].user_id == user_id) {
                user = &users[i];
                break;
            }
        }
        if (!user) {
            printf("利用者が見つかりません。\n");
            printf("[1] もう一度入力　[2] メインメニューへ\n");
            if (scanf("%d", &menu) != 1) {
                while(getchar() != '\n');
                continue;
            }
            if (menu == 1) continue;
            else return;
        }

        printf("利用者ID: %d　利用者名: %s\n", user->user_id, user->name);

        if (user->now_count == 0) {
            printf("現在貸出中の本はありません。\n");
            printf("[1] 1つ前に戻る　[2] メインメニューへ\n");
            if (scanf("%d", &menu) != 1) {
                while(getchar() != '\n');
                continue;
            }
            if (menu == 1) continue;
            else return;
        }

        while (1) {
            int total_overdue_days = 0;
            int total_fee = 0;

            printf("===============【貸出中の本一覧】===============\n");
            for (i = 0; i < user->now_count; i++) {
                int overdue_days = 0;
                if (user->now_books[i].status == 3) {
                    overdue_days = 2; // 仮に2日延滞
                }
                total_overdue_days += overdue_days;
                total_fee += overdue_days * 100;
                printf("[%d] %s（著者: %s, 延滞日数: %d日, 期限: %s）\n",
                    user->now_books[i].book_id,
                    user->now_books[i].title,
                    user->now_books[i].author,
                    overdue_days,
                    user->now_books[i].due_date);
            }

            printf("延滞日数合計: %d日\n", total_overdue_days);
            printf("\n");
            printf("1: 返却する\n");
            printf("0: 1つ前に戻る\n");
            printf("9: メインメニューへ\n");
            printf("番号を入力してください: ");

            if (scanf("%d", &menu) != 1) {
                printf("数値で入力してください。\n");
                while(getchar() != '\n');
                continue;
            }

            if (menu == 0 || menu == 9) {
                return; // main.c のメニューへ戻る
            }

            if (menu != 1) {
                printf("無効な選択です。\n");
                continue;
            }

            if (total_fee > 0) {
                printf("延滞料金が発生しています。合計: %d円\n", total_fee);
                printf("[金額入金画面へ]\n");
                while (1) {
                    int payment = 0;
                    printf("入金額を入力してください: ");
                    if (scanf("%d", &payment) != 1) {
                        printf("数値で入力してください。\n");
                        while(getchar() != '\n');
                        continue;
                    }

                    if (payment < total_fee) {
                        printf("入金額が不足しています。不足: %d円\n", total_fee - payment);
                        printf("もう一度入金してください。\n");
                        continue;
                    }

                    printf("入金を確認しました。\n");
                    if (payment > total_fee) {
                        printf("おつり: %d円\n", payment - total_fee);
                    }
                    break;
                }
            }

            printf("返却処理が完了しました。\n");
            printf("===============【返却完了】===============\n");
            user->now_count = 0; // 一括返却
            return; // main.c のメニューへ戻る
        }
    }
}
