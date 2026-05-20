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
- `display_user_info()`
	利用者情報を表示

### 3. 貸出処理
- `checkout_book(user_id, book_id)`
	利用者と書籍IDで貸出処理、支払い処理も実施
- `rental_history()`
	貸出履歴をCSVに記録

### 4. 返却処理
- `return_book(user_id, book_id)`
	返却受付、延滞時の支払い処理
- `calculate_overdue_fee(user_id, book_id)` 
	延滞料金の計算
- `return_history()`
	返却履歴をCSVに記録

### 5. 貸出履歴保存・閲覧
- `load_history()`
	履歴CSVを読み込み
- `display_user_history(user_id)`
	利用者ごとの履歴表示

### 6. 蔵書検索機能
- `search_books(keyword)`
	検索キーワード（タイトル・著者名・ID等）で蔵書を検索し、
	該当書籍のID・タイトル・著者名・現在の貸出状態（貸出可／貸出中など）を一覧表示。
	これにより、今図書館に本があるか（貸出可）・貸出中かが分かる。
 	一致した書籍の情報（ID・タイトル・著者名・貸出状態など）を一覧表示