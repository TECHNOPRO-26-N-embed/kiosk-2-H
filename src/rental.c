#include <stdio.h>
#include <stdlib.h>
enum Button {
    ホーム,
    戻る,
    貸出,
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
    Bookinfo b_info;
    printf("整数 文字列 文字列 整数(0-3)のように入力してください: ");
    scanf("%d %s %s %d",&b_info.book_id, b_info.title, b_info.author, &b_info.status);    
    printf("書籍ID: %d\n", b_info.book_id);
    printf("タイトル: %s\n", b_info.title);
    printf("著者: %s\n", b_info.author);

    printf("貸出状況: %s\n", b_info.status == 貸出可能 ? "貸出可能" : b_info.status == 貸出不可 ? "貸出不可" : b_info.status == 貸出中 ? "貸出中" : "延滞中");
}