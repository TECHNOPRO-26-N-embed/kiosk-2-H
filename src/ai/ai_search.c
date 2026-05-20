#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ai_common.h"

// #define TITLE_LEN 100
// #define AUTHOR_LEN 100
// #define MAX_BOOKS 200
// #define CSV_PATH "data/books1.csv"

// typedef struct {
// 	int book_id;
// 	char title[TITLE_LEN];
// 	char author[AUTHOR_LEN];
// 	int status; // 0:貸出可, 1:貸出不可, 2:貸出中, 3:延滞
// } Book;

// typedef struct {
// 	Book *books;
// 	int size;
// } BookList;

BookList load_books(void) {
	static Book library[MAX_BOOKS];
	char line[512];
	FILE *fp = fopen(CSV_PATH, "r");
	int count = 0;
	BookList list;

	if (fp == NULL) {
		printf("CSVファイルを開けませんでした: %s\n", CSV_PATH);
		list.books = NULL;
		list.size = 0;
		return list;
	}

	// 1行目（ヘッダー）を必ず読み飛ばす
	fgets(line, sizeof(line), fp);
	while (fgets(line, sizeof(line), fp) != NULL) {
		char *token;
		Book book;
		if (count >= MAX_BOOKS) {
			break;
		}
		token = strtok(line, ",\r\n");
		if (token == NULL) continue;
		book.book_id = atoi(token);
		token = strtok(NULL, ",\r\n");
		if (token == NULL) continue;
		strncpy(book.title, token, TITLE_LEN - 1);
		book.title[TITLE_LEN - 1] = '\0';
		token = strtok(NULL, ",\r\n");
		if (token == NULL) continue;
		strncpy(book.author, token, AUTHOR_LEN - 1);
		book.author[AUTHOR_LEN - 1] = '\0';
		token = strtok(NULL, ",\r\n");
		if (token == NULL) continue;
		book.status = atoi(token);
		if (book.status < 0 || book.status > 3) book.status = 0;
		library[count] = book;
		count++;
	}

	fclose(fp);

	list.books = library;
	list.size = count;
	return list;
}


// 前後の空白・改行を除去する
void trim(char *str) {
	if (!str) return;
	// 先頭の空白をスキップ
	char *start = str;
	while (*start && (*start == ' ' || *start == '\t' || *start == '\r' || *start == '\n')) start++;
	// 末尾の空白をカット
	char *end = start + strlen(start);
	while (end > start && (end[-1] == ' ' || end[-1] == '\t' || end[-1] == '\r' || end[-1] == '\n')) end--;
	*end = '\0';
	if (start != str) memmove(str, start, end - start + 1);
}

static const char *status_text(int status) {
	switch (status) {
		case 0:
			return "貸出可";
		case 1:
			return "貸出不可";
		case 2:
			return "貸出中";
		case 3:
			return "延滞";
		default:
			return "不明";
	}
}

void search_books(const BookList *list, const char *keyword) {
	int found = 0;
	if (list == NULL || list->books == NULL || list->size <= 0) {
		printf("蔵書データがありません。\n");
		return;
	}
	// 空文字やスペースだけの入力は何も出力しない
	if (keyword == NULL) {
		printf("該当する書籍が見つかりませんでした。\n");
		return;
	}
	char trimmed_keyword[100];
	strncpy(trimmed_keyword, keyword, sizeof(trimmed_keyword)-1);
	trimmed_keyword[sizeof(trimmed_keyword)-1] = '\0';
	trim(trimmed_keyword);
	if (strlen(trimmed_keyword) == 0) {
		printf("該当する書籍が見つかりませんでした。\n");
		return;
	}
	printf("\n--- 蔵書検索結果 ---\n");
	printf("%-4s | %-24s | %-18s | %-8s\n", "ID", "タイトル", "著者名", "貸出状態");
	printf("------------------------------------------------------------------\n");
	for (int i = 0; i < list->size; i++) {
		char id_text[16];
		char title_trim[TITLE_LEN];
		char author_trim[AUTHOR_LEN];
		snprintf(id_text, sizeof(id_text), "%d", list->books[i].book_id);
		strncpy(title_trim, list->books[i].title, TITLE_LEN-1); title_trim[TITLE_LEN-1]='\0';
		strncpy(author_trim, list->books[i].author, AUTHOR_LEN-1); author_trim[AUTHOR_LEN-1]='\0';
		trim(id_text);
		trim(title_trim);
		trim(author_trim);
		// ID・タイトル・著者名すべて完全一致
		int id_match = (strcmp(trimmed_keyword, id_text) == 0);
		int title_match = (strcmp(trimmed_keyword, title_trim) == 0);
		int author_match = (strcmp(trimmed_keyword, author_trim) == 0);
		if (id_match || title_match || author_match) {
			printf("%-4d | %-24s | %-18s | %-8s\n",
				   list->books[i].book_id,
				   list->books[i].title,
				   list->books[i].author,
				   status_text(list->books[i].status));
			found = 1;
		}
	}
	if (!found) {
		printf("該当する書籍が見つかりませんでした。\n");
	}
}

void search(void) {
	BookList list = load_books();
	char keyword[100];
	int menu = -1;

	while (1) {
		printf("検索キーワードを入力してください（タイトル・著者名・ID）: ");
		if (fgets(keyword, sizeof(keyword), stdin) == NULL) {
			printf("入力エラーです。メニューに戻ります。\n");
			return;
		}
		// 改行除去
		keyword[strcspn(keyword, "\r\n")] = '\0';

		search_books(&list, keyword);

		printf("\n1: もう一度検索する\n");
		printf("0: メニューに戻る\n");
		printf("選択してください: ");
		char menu_input[16];
		if (fgets(menu_input, sizeof(menu_input), stdin) == NULL) {
			printf("入力エラーです。メニューに戻ります。\n");
			return;
		}
		menu = atoi(menu_input);

		if (menu == 0) {
			return;
		}
		if (menu != 1) {
			printf("無効な選択です。メニューに戻ります。\n");
			return;
		}
	}
}
