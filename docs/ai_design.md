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

---