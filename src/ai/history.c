
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOW 5
#define MAX_PAST 5
#define MAX_ID 100000 // ユーザーの最大値（10^5）

// typedef struct {
// 	int user_id;
// 	char name[100];
// 	char phone[32];
// 	char mail[100];
// 	char address[200];
// 	int now_count;
// 	int past_count;
// } User;

typedef struct {
	int user_id;
	int book_id;
	char lend_date[20];
	char return_date[20];
} History;

void history();


#define MAX_HISTORY 1000

int load_history(History histories[], const char* filename) {
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        printf("履歴ファイルが開けません: %s\n", filename);
        return 0;
    }
    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp) && count < MAX_HISTORY) {
        // user_id,book_id,lend_date,return_date
        char* token;
        token = strtok(line, ",");
        if (!token) continue;
        histories[count].user_id = atoi(token);
        token = strtok(NULL, ",");
        if (!token) continue;
        histories[count].book_id = atoi(token);
        token = strtok(NULL, ",");
        if (!token) continue;
        strncpy(histories[count].lend_date, token, sizeof(histories[count].lend_date));
        token = strtok(NULL, ",\n");
        if (!token) continue;
        strncpy(histories[count].return_date, token, sizeof(histories[count].return_date));
        count++;
    }
    fclose(fp);
    return count;
}



void display_user_history(int user_id, History* histories, int history_count) {
    printf("ユーザーID: %d の履歴一覧\n", user_id);
    printf("--- 貸出・返却履歴 ---\n");
    int has_history = 0;
    for (int i = 0; i < history_count; i++) {
        if (histories[i].user_id == user_id) {
            printf("書籍ID: %d, 貸出日: %s, 返却日: %s\n",
                histories[i].book_id,
                histories[i].lend_date,
                histories[i].return_date);
            has_history = 1;
        }
    }
    if (!has_history) {
        printf("履歴がありません。\n");
    }
}


void history(void) {
    int user_id;
    printf("ユーザーIDを入力してください: ");
    scanf("%d", &user_id);

    // 履歴データをCSVから読み込む
    History histories[MAX_HISTORY];
    int history_count = load_history(histories, "../../data/history.csv");
    printf("[DEBUG] 読み込んだ履歴件数: %d\n", history_count);
    printf("[DEBUG] 入力されたユーザーID: %d\n", user_id);
    display_user_history(user_id, histories, history_count);
}