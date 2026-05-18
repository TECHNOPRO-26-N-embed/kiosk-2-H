#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_MEMBERS 10

typedef struct {
    int book_id;
    char title[100];
    int late_days;
} Book;

typedef struct {
    int member_id;
    char name[50];

    int rental_count;
    Book rented_books[MAX_MEMBERS];
} UserInfo;

UserInfo users[]={
    1001,"山田",2,{{0001,"C言語",0},{0002,"データ構造",3}},
    1002,"田中",1,{{0003,"アルゴリズム",2},{0006, "羅生門", 0},{0005, "人間失格", 0}}
};
int user_count = sizeof(users) / sizeof(users[0]);

int find_user_index(int member_id) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].member_id == member_id) {
            return i;
        }
    }
    return -1; // ユーザーが見つからない場合
}

void return_book() {
    
    int member_id;
    int menu;

    printf("=============返却=============\n");
    printf("会員IDを入力してください。: ");
    scanf("%d", &member_id);

    int index = find_user_index(member_id);

    if(index == -1) {
        printf("無効な会員IDです。\n");
        printf("1:もう一度入力する。\n");
        printf("0: メニューに戻る\n");
        scanf("%d", &menu);
        if(menu == 0) {
            return;
        }
    }

    UserInfo *user = &users[index];

    while(1){
        printf("----------貸出状況一覧----------");
        printf("会員ID: %d\n", user->member_id);
        printf("会員名: %s\n", user->name);
        if(user->rental_count == 0) {
            printf("貸出中の本はありません。\n");
            printf("0:1つ前に戻る\n");
            printf("9: メインメニューに戻る\n");
            scanf("%d", &menu);
            if (menu == 0) {
                return_book();
            } else if (menu == 9){
                return;
            }
            break;

        for(int i=0; i < user->rental_count; i++) {
            printf("本ID: %d\n", user->rented_books[i].book_id);
            printf("タイトル: %s\n", user->rented_books[i].title);
            printf("\n%d冊目\n",i+1);
            printf("遅延日数: %d\n", user->rented_books[i].late_days);
        }
    }
    printf("1:返却する。\n");
    printf("0:1つ前に戻る\n");
    printf("9:メインメニューに戻る\n");
    scanf("%d", &menu);
    if(menu == 1) { 
        int late_fee = 0;
        for(int i=0; i < user->rental_count; i++) {
            if(user->rented_books[i].late_days > 0) {
                late_fee += user->rented_books[i].late_days * 100; // 遅延日数に応じた料金計算
            }
        }
        if(late_fee > 0) {
            int payment;

            printf("遅延料金: %d円\n", late_fee);
            printf("支払い金額を入力してください: ");
            scanf("%d", &payment);
            if(payment >= late_fee) {
                printf("支払いが完了しました。返却処理を行います。\n");
                // 返却処理のコードをここに追加
            } else {
                printf("支払い金額が不足しています。\n");
                continue;
            }
        } else {
            printf("遅延料金はありません。\n");
        }
    } else if(menu == 0) {
        return_book();
    } else if(menu == 9) {
        return;
    }
}
}