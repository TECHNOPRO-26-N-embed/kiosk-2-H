#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// data/history.csvの格納上限数
#define MAX_HISTORY 10000

typedef struct {
	int user_id;
	int book_id;
	char lend_date[20];
	char return_date[20];
} History;

void history();

int load_history(History histories[], const char* filename) {
    // ファイル読み込みと例外処理
    FILE* fp = fopen(filename, "r");
    if (!fp) {
        fprintf(stderr, "[ERROR] 履歴ファイルが開けません: %s\n", filename);
        return -1;
    }

    int count = 0;
    char line[256];
    while (fgets(line, sizeof(line), fp) != NULL && count < MAX_HISTORY) {
        // fgetsで読み込んだ行の末尾に改行が残っていれば除去
        size_t len = strlen(line);
        if (len > 0 && line[len-1] == '\n') {
            line[len-1] = '\0';
        }
        char* token;
        // 1列目: user_id
        token = strtok(line, ",");
        if (!token) {
            fprintf(stderr, "[WARN] CSV形式不正: user_id列がありません\n");
            continue;
        }
        histories[count].user_id = atoi(token);
        // 2列目: book_id
        token = strtok(NULL, ",");
        if (!token) {
            fprintf(stderr, "[WARN] CSV形式不正: book_id列がありません\n");
            continue;
        }
        histories[count].book_id = atoi(token);
        // 3列目: lend_date
        token = strtok(NULL, ",");
        if (!token) {
            fprintf(stderr, "[WARN] CSV形式不正: lend_date列がありません\n");
            continue;
        }
        strncpy(histories[count].lend_date, token, sizeof(histories[count].lend_date)-1);
        histories[count].lend_date[sizeof(histories[count].lend_date)-1] = '\0';
        // 4列目: return_date
        token = strtok(NULL, ",\n");
        if (!token) {
            fprintf(stderr, "[WARN] CSV形式不正: return_date列がありません\n");
            continue;
        }
        strncpy(histories[count].return_date, token, sizeof(histories[count].return_date)-1);
        histories[count].return_date[sizeof(histories[count].return_date)-1] = '\0';
        count++;
    }
    fclose(fp);
    if (count == 0) {
        fprintf(stderr, "[WARN] 履歴ファイルに有効なデータがありません: %s\n", filename);
    }
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
            has_history += 1;
        }
    }
    if (has_history == 0) {
        printf("履歴がありません。\n");
    }
    printf("--- 貸出・返却履歴 終了 ---\n");
}


void history(void) {
    int user_id;
    printf("ユーザーIDを入力してください: ");
    if (scanf("%d", &user_id) != 1) {
        fprintf(stderr, "[ERROR] ユーザーIDの入力が不正です。数値を入力してください。\n");
        // 入力バッファをクリア
        int c;
        while ((c = getchar()) != '\n' && c != EOF) {}
        return;
    }

    // 履歴データをCSVから読み込む
    History histories[MAX_HISTORY];

    // CSVの読み込み件数
    int history_count = load_history(histories, "./data/history.csv");
    if (history_count < 0) {
        fprintf(stderr, "[ERROR] 履歴データの読み込みに失敗しました。\n");
        return;
    }
    // printf("[DEBUG] 読み込んだ履歴件数: %d\n", history_count);

    // 該当ユーザーの履歴の表示
    display_user_history(user_id, histories, history_count);
}