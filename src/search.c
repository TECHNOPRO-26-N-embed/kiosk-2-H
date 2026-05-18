#include <stdio.h>

typedef struct{
    int book_id;
    char title[100];
    char author[100];
}books;

int search_book(int book_id, books library[], int size) {
    for (int i = 0; i < size; i++) {
        if (library[i].book_id == book_id) {
            return i; // 本が見つかった場合、そのインデックスを返す
        }
    }
    return -1; // 本が見つからなかった場合、-1を返す
}


void search(void) {
    int book_id;
    printf("検索したい本のIDを入力してください: ");
    scanf("%d", &book_id);

    books library[] = {
        {1, "C Programming", "Author A"},
        {2, "Data Structures", "Author B"},
        {3, "Algorithms", "Author C"}
    };

    int index = search_book(book_id, library, 3);
    if (index != -1) {
        printf("本が見つかりました: %s by %s\n", library[index].title, library[index].author);
    } else {
        printf("本が見つかりませんでした。\n");
    }

    // return 0;
}