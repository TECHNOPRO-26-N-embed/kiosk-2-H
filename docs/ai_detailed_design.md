# 図書館セルフ貸出システム 詳細アルゴリズム設計

## 1. 書籍ID管理
### 書籍情報の読み込み（load_books）
```c
Book* load_books() {
    // 書籍CSVファイルを読み込み、書籍リストを生成
    return NULL;
}
```

### 書籍情報の保存（save_books）
```c
int save_books(Book* books) {
    // 書籍リストをCSV形式で保存
    return 0;
}
```

### 書籍状態表示（display_book_status）
```c
void display_book_status(Book* books) {
    // 書籍リストをループし、ID・概要・貸出状態を出力
}
```

---

## 2. 利用者ID管理
### 利用者情報の読み込み（load_users）
```c
User* load_users() {
    // 利用者CSVファイルを読み込み、利用者リストを生成
    return NULL;
}
```

### 利用者追加（add_user）
```c
int add_user(User new_user) {
    // 新規利用者情報を構造体リストに追加し、CSVに保存
    return 0;
}
```

### 利用者情報表示（display_user_info）
```c
void display_user_info(User* users) {
    // 利用者リストをループし、ID・氏名・連絡先等を出力
}
```

---

## 3. 貸出処理（checkout_book）
```c
int checkout_book(int user_id, int book_id) {
    // 書籍リストから該当書籍を検索し、貸出処理を実施
    return 0;
}
```

---

## 4. 返却処理（return_book）
```c
int return_book(int user_id, int book_id) {
    // 書籍リストから該当書籍を検索し、返却処理を実施
    return 0;
}
```

---

## 5. 貸出履歴保存・閲覧
### 履歴読み込み（load_history）
```c
void load_history(csv) {
    // 履歴CSVを読み込み、履歴リストを生成
    return NULL;
}
```

### 利用者ごとの履歴表示（display_user_history）
```c
void display_user_history(int user_id, User* users) {
    // 指定利用者IDの履歴を抽出し、一覧表示
}
```

---

## 6. 蔵書検索機能
### 書籍検索（search_books）
```c
Book* search_books(char* keyword, Book* books) {
    // 検索キーワードに一致する書籍を検索し、該当書籍リストを返す
    return NULL;
}
```

---

## 7. 関数呼び出し関係（フローチャートイメージ）

### 7.1 関数名（呼び出す関数名）
- load_books（なし）
- save_books（なし）
- display_book_status（なし）
- load_users（なし）
- add_user（save_users）
- display_user_info（なし）
- checkout_book（load_books, load_users, load_history, save_books）
- return_book（load_books, load_history, save_books）
- load_history（なし）
- display_user_history（load_history）
- search_books（load_books）

### 7.2 主要処理フロー
- 貸出処理: checkout_book -> load_books -> load_users -> load_history -> save_books
- 返却処理: return_book -> load_books -> load_history -> save_books
- 履歴表示: display_user_history -> load_history
- 蔵書検索: search_books -> load_books

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
	int now_count;
	int past_count;
} User;

// 履歴情報
typedef struct {
	int user_id;
	int book_id;
	char lend_date[20];
	char return_date[20];
} History;

// 操作ログ
// typedef struct {
// 	char datetime[20];
// 	int user_id;
// 	char operation[32];
// 	char detail[128];
// } OperationLog;
貸出処理をキャンセルした場合は、追加せず、貸出操作を確定した人のみの処理を追加する（操作番号を追加する　例1　1番が押されました。など）
```