## 実装すべき関数一覧と役割

### 1. 書籍ID管理関連
- `load_books()`
	書籍情報CSVを読み込み、書籍リストを生成
- `save_books()`
	書籍情報をCSVに保存
- `display_book_status()`
	書籍の概要や貸出状態を表示

### 2. 利用者ID管理関連
- `load_users()`
	利用者情報CSVを読み込み、利用者リストを生成
- `save_users()`
	利用者情報をCSVに保存
- `add_user()`
	新規利用者を追加
- `delete_user()`
	利用者を削除
- `display_user_info()`
	利用者情報を表示

### 3. 貸出処理
- `checkout_book(user_id, book_id)`
	利用者と書籍IDで貸出処理、支払い処理も実施

### 4. 返却処理
- `return_book(user_id, book_id)`
	返却受付、延滞時の支払い処理
- `handle_damage(book_id)`
	破損時の人間対応（アラート等）

### 5. 貸出履歴保存・閲覧
- `save_history()`
	貸出・返却履歴をCSVに記録
- `load_history()`
	履歴CSVを読み込み
- `display_user_history(user_id)`
	利用者ごとの履歴表示

### 6. 延滞者管理
- `extract_overdue_users()`
	延滞者の抽出
- `calculate_overdue_fee(user_id, book_id)`
	延滞料金の計算

### 7. 蔵書検索機能
- `search_books(keyword)`
	検索キーワード（タイトル・著者名・ID等）で蔵書を検索し、
	該当書籍のID・タイトル・著者名・現在の貸出状態（貸出可／貸出中など）を一覧表示。
	これにより、今図書館に本があるか（貸出可）・貸出中かが分かる。
 	一致した書籍の情報（ID・タイトル・著者名・貸出状態など）を一覧表示

---

## 構造体定義例

```c
// 書籍情報
typedef struct {
	int book_id;
	char title[100];
	char author[100];
	int status; // 0:貸出可, 1:貸出不可, 2:貸出中, 3:延滞
} Book;

// 利用者情報
typedef struct {
	int user_id;
	char name[100];
	char phone[32];
	char mail[100];
	char address[200];
	char payment[32];
	int now_books[10]; // 現在借りている書籍ID
	int past_books[100]; // 過去借りた書籍ID
	int now_count;
	int past_count;
} User;

// 履歴情報
typedef struct {
	int user_id;
	int book_id;
	int fee;
	int count;
	char lend_date[20];
	char return_date[20];
	int overdue_fee;
} History;

// 操作ログ
typedef struct {
	char datetime[20];
	int user_id;
	char operation[32];
	char detail[128];
} OperationLog;
```

<!-- ## 実装すべき関数一覧（引数型・構造体付き）

```c
// --- 書籍ID管理 ---
void load_books(Book books[], int *count);
void save_books(const Book books[], int count);
void display_book_status(const Book *book);

// --- 利用者ID管理 ---
void load_users(User users[], int *count);
void save_users(const User users[], int count);
void add_user(User users[], int *count, const User *new_user);
void delete_user(User users[], int *count, int user_id);
void display_user_info(const User *user);

// --- 貸出処理 ---
int checkout_book(User *user, Book *book, int days, int *fee);

// --- 返却処理 ---
int return_book(User *user, Book *book, const char *return_date, int *overdue_fee);
void handle_damage(Book *book);

// --- 貸出履歴保存・閲覧 ---
void save_history(const History histories[], int count);
void load_history(History histories[], int *count);
void display_user_history(const History histories[], int count, int user_id);

// --- 延滞者管理 ---
void extract_overdue_users(const History histories[], int count, int overdue_user_ids[], int *overdue_count);
int calculate_overdue_fee(const History *history, const char *current_date);

// --- 操作ログ管理 ---
void save_operation_log(const OperationLog logs[], int count);
void load_operation_log(OperationLog logs[], int *count);
``` -->