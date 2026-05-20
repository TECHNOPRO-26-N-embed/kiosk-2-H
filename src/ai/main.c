#include<stdio.h>
#include<time.h>
#include <string.h>
// ヘッダーの入力
#define MAX_BOOKS 1024
#define MAX_USERS 1024
#define MAX_HISTORY 2048

#define BOOKS_CSV "data/books.csv"
#define USERS_CSV "data/users.csv"
#define HISTORY_CSV "data/history.csv"
#define OPLOG_CSV "data/operation_log.csv"
typedef struct {
	int book_id;
	char title[100];
	char author[100];
	int status; /* 0:available, 1:unavailable, 2:rented, 3:overdue */
} Book;

typedef struct {
	int user_id;
	char name[100];
	char phone[32];
	char mail[100];
	char address[200];
	int now_count;
	int past_count;
} User;

typedef struct {
	int user_id;
	int book_id;
	char lend_date[20];
	char return_date[20];
} History;

static const char *status_to_text(int status) {
	switch (status) {
		case 0:
			return "available";
		case 1:
			return "unavailable";
		case 2:
			return "rented";
		case 3:
			return "overdue";
		default:
			return "unknown";
	}
}

static void now_string(char *out, size_t out_size) {
	time_t t;
	struct tm *tm_info;

	t = time(NULL);
	tm_info = localtime(&t);
	if (tm_info == NULL) {
		if (out_size > 0) {
			out[0] = '\0';
		}
		return;
	}
	strftime(out, out_size, "%Y/%m/%d %H:%M", tm_info);
}

static int load_books(Book *books, int max_books) {
	FILE *fp;
	int count;

	fp = fopen(BOOKS_CSV, "r");
	if (fp == NULL) {
		return 0;
	}

	count = 0;
	while (count < max_books) {
		Book b;
		int n;
		n = fscanf(fp, "%d,%99[^,],%99[^,],%d\n", &b.book_id, b.title, b.author, &b.status);
		if (n != 4) {
			break;
		}
		books[count++] = b;
	}

	fclose(fp);
	return count;
}

static int save_books(const Book *books, int book_count) {
	FILE *fp;
	int i;

	fp = fopen(BOOKS_CSV, "w");
	if (fp == NULL) {
		return -1;
	}

	for (i = 0; i < book_count; i++) {
		fprintf(fp, "%d,%s,%s,%d\n",
				books[i].book_id,
				books[i].title,
				books[i].author,
				books[i].status);
	}

	fclose(fp);
	return 0;
}

static int load_users(User *users, int max_users) {
	FILE *fp;
	int count;

	fp = fopen(USERS_CSV, "r");
	if (fp == NULL) {
		return 0;
	}

	count = 0;
	while (count < max_users) {
		User u;
		int n;
		n = fscanf(fp,
				   "%d,%99[^,],%31[^,],%99[^,],%199[^,],%d,%d\n",
				   &u.user_id,
				   u.name,
				   u.phone,
				   u.mail,
				   u.address,
				   &u.now_count,
				   &u.past_count);
		if (n != 7) {
			break;
		}
		users[count++] = u;
	}

	fclose(fp);
	return count;
}

static int load_history(History *histories, int max_histories) {
	FILE *fp;
	int count;

	fp = fopen(HISTORY_CSV, "r");
	if (fp == NULL) {
		return 0;
	}

	count = 0;
	while (count < max_histories) {
		History h;
		int n;
		n = fscanf(fp, "%d,%d,%19[^,],%19[^\n]\n", &h.user_id, &h.book_id, h.lend_date, h.return_date);
		if (n != 4) {
			break;
		}
		histories[count++] = h;
	}

	fclose(fp);
	return count;
}

static int append_history(int user_id, int book_id) {
	FILE *fp;
	char lend_date[20];

	fp = fopen(HISTORY_CSV, "a");
	if (fp == NULL) {
		return -1;
	}

	now_string(lend_date, sizeof(lend_date));
	fprintf(fp, "%d,%d,%s,%s\n", user_id, book_id, lend_date, "-");
	fclose(fp);
	return 0;
}

static int append_operation_log(int user_id, const char *operation, const char *detail) {
	FILE *fp;
	char now[20];

	fp = fopen(OPLOG_CSV, "a");
	if (fp == NULL) {
		return -1;
	}

	now_string(now, sizeof(now));
	fprintf(fp, "%s,%d,%s,%s\n", now, user_id, operation, detail);
	fclose(fp);
	return 0;
}

static int find_user_index(const User *users, int user_count, int user_id) {
	int i;
	for (i = 0; i < user_count; i++) {
		if (users[i].user_id == user_id) {
			return i;
		}
	}
	return -1;
}

static int find_book_index(const Book *books, int book_count, int book_id) {
	int i;
	for (i = 0; i < book_count; i++) {
		if (books[i].book_id == book_id) {
			return i;
		}
	}
	return -1;
}

/*
 * checkout_book flow follows the detailed design:
 * load_books -> load_users -> load_history -> save_books
 */
int checkout_book(int user_id, int book_id) {
	Book books[MAX_BOOKS];
	User users[MAX_USERS];
	History histories[MAX_HISTORY];
	int book_count;
	int user_count;
	int history_count;
	int user_index;
	int book_index;
	int operation_number;
	char detail[128];

	book_count = load_books(books, MAX_BOOKS);
	user_count = load_users(users, MAX_USERS);
	history_count = load_history(histories, MAX_HISTORY);
	(void)history_count;

	user_index = find_user_index(users, user_count, user_id);
	if (user_index < 0) {
		printf("user not found: %d\n", user_id);
		return -1;
	}

	book_index = find_book_index(books, book_count, book_id);
	if (book_index < 0) {
		printf("book not found: %d\n", book_id);
		return -2;
	}

	printf("checkout target\n");
	printf(" user_id: %d\n", user_id);
	printf(" book_id: %d\n", books[book_index].book_id);
	printf(" title: %s\n", books[book_index].title);
	printf(" author: %s\n", books[book_index].author);
	printf(" current_status: %s\n", status_to_text(books[book_index].status));

	if (books[book_index].status != 0) {
		printf("cannot checkout: book status is %s\n", status_to_text(books[book_index].status));
		return -3;
	}

	printf("select operation number (1=確定, 0=キャンセル): ");
	if (scanf("%d", &operation_number) != 1) {
		printf("invalid operation input\n");
		return -4;
	}

	printf("%d button was pressed.\n", operation_number);

	if (operation_number != 1) {
		printf("checkout canceled. no data was added.\n");
		append_operation_log(user_id, "checkout_cancel", "operation canceled before confirmation");
		return 1;
	}

	books[book_index].status = 2;
	if (save_books(books, book_count) != 0) {
		printf("failed to save books\n");
		return -5;
	}

	if (append_history(user_id, book_id) != 0) {
		printf("warning: failed to append history\n");
	}

	snprintf(detail, sizeof(detail), "book_id:%d checked out", book_id);
	if (append_operation_log(user_id, "checkout", detail) != 0) {
		printf("warning: failed to append operation log\n");
	}

	printf("checkout completed successfully.\n");
	return 0;
}

int main(void) {
   int user_id = 1001; // Example user_id
   int book_id = 1001; // Example book_id
   checkout_book(user_id, book_id);
   return 0;
}