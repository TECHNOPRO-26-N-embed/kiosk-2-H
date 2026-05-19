#include <stdio.h>
#include <stdlib.h>
enum Button {
    ホーム,
    戻る,
    貸出,
    確定,
    完了
};
enum RentalStatus {
    貸出可能,
    貸出不可,
    貸出中,
    延滞中
};
typedef struct {
    int book_id;
    char title[100];
    char author[100];
    enum RentalStatus status;
} Bookinfo;
void rental(void){
    int i  ;
    Bookinfo b_info[4] = {{0, "title0", "author0", 貸出可能},{1, "title1", "author1", 貸出不可},{2, "title2", "author2", 貸出中},{3, "title3", "author3", 延滞中}};
    // b_info[i].book_id = i;
    printf("書籍IDを入力してください: ");
    //ID(整数)の入力を受け取る
    scanf("%d",&i);
    if(i < 0 || i >= 4) {
        printf("無効な書籍IDが入力されました。\n");
        return;
    }

    printf("書籍ID: %d\n", b_info[i].book_id);
    printf("タイトル: %s\n", b_info[i].title);
    printf("著者: %s\n", b_info[i].author);

    printf("貸出状況: %s\n", b_info[i].status == 貸出可能 ? "貸出可能" : b_info[i].status == 貸出不可 ? "貸出不可" : b_info[i].status == 貸出中 ? "貸出中" : "延滞中");

    printf("ボタンを選択してください (0: ホーム, 1: 戻る, 2: 貸出): ");
    enum Button button;
    scanf("%d", &button);
    if(button == ホーム) {
        printf("ホームに戻ります。\n");
    } else if(button == 戻る) {
        printf("前の画面に戻ります。\n");
    } else if(button == 貸出) {
        if(b_info[i].status == 貸出可能) {
            printf("確認画面\n");
            printf("書籍ID: %d\n", b_info[i].book_id);
            printf("タイトル: %s\n", b_info[i].title);
            printf("著者: %s\n", b_info[i].author);
            printf("ボタンを選択してください (0: ホーム, 1: 戻る, 3: 確定): ");
            scanf("%d", &button);
            if(button == ホーム) {
                printf("ホームに戻ります。\n");
            } else if(button == 戻る) {
                printf("前の画面に戻ります。\n");
            } else if(button == 確定) {
                b_info[i].status = 貸出中;
                printf("貸出が完了しました。\n");
                printf("4: 完了\n");
                scanf("%d", &button);
                if(button == 完了) {
                    printf("ホームに戻ります。\n");
                } else {
                    printf("無効なボタンが選択されました。\n");
                }
            } else {
                printf("無効なボタンが選択されました。\n");
            }

        } else {
            printf("この書籍は貸し出せません。\n");
        }
    } else {
        printf("無効なボタンが選択されました。\n");
    }
 }