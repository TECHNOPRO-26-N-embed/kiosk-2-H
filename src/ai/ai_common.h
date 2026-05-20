#ifndef AI_COMMON_H
#define AI_COMMON_H

#define MAX_BOOKS 1024
#define MAX_USERS 1024
#define MAX_HISTORY 2048

#define BOOKS_CSV "data/books.csv"
#define USERS_CSV "data/users.csv"
#define HISTORY_CSV "data/history.csv"
#define OPLOG_CSV "data/operation_log.csv"

#define TITLE_LEN 100
#define AUTHOR_LEN 100
// #define MAX_BOOKS 200
#define CSV_PATH "data/books1.csv"

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

// 設計書準拠の構造体
typedef struct {
    int book_id;
    char title[100];
    char author[100];
    int status; // 0:貸出可, 1:貸出不可, 2:貸出中, 3:延滞
    char due_date[20]; // 返却期限
} Book_return;

typedef struct {
    int user_id;
    char name[100];
    int now_count;
    Book_return now_books[10]; // 貸出中の本（最大10冊仮定）
} User_return;

typedef struct {
    Book *books;
    int size;
} BookList;

void do_checkout_book();
void return_screen();
void search();
void history();

#endif // AI_COMMON_H