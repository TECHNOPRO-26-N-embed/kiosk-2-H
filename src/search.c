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
    int menu;

    
    printf("検索したい本のIDを入力してください: ");
    scanf("%d", &book_id);

   


    books library[] = {
        {1, "C Programming", "Author A"},
        {2, "Data Structures", "Author B"},
        {3, "Algorithms", "Author C"},
        {4, "Operating Systems", "Author D"},
        {5, "Database Systems", "Author E"},
        {6, "Computer Networks", "Author F"},
        {7, "Software Engineering", "Author G"},
        {8, "Artificial Intelligence", "Author H"},
        {9, "Machine Learning", "Author I"},
        {10, "Deep Learning", "Author J"},
        {11, "Book 11", "Author K"},
        {12, "Book 12", "Author L"},
        {13, "Book 13", "Author M"},
        {14, "Book 14", "Author N"},
        {15, "Book 15", "Author O"},
        {16, "Book 16", "Author P"},
        {17, "Book 17", "Author Q"},
        {18, "Book 18", "Author R"},
        {19, "Book 19", "Author S"},
        {20, "Book 20", "Author T"},
        {21, "Book 21", "Author U"},
        {22, "Book 22", "Author V"},
        {23, "Book 23", "Author W"},
        {24, "Book 24", "Author X"},
        {25, "Book 25", "Author Y"},
        {26, "Book 26", "Author Z"},
        {27, "Book 27", "Author AA"},
        {28, "Book 28", "Author AB"},
        {29, "Book 29", "Author AC"},
        {30, "Book 30", "Author AD"}
    };

    int index = search_book(book_id, library, 30);
        if (index != -1) {
            printf("本が見つかりました: %s by %s\n", library[index].title, library[index].author);
        } else if( index == -1) {
            printf("本が見つかりませんでした。\n");
            printf("1:もう一度入力する。\n");
            printf("0: メニューに戻る\n");
            scanf("%d", &menu);
            if(menu == 0) {
            return;
            }else if(menu == 1) {
                search();
            }
        }
    // return 0;
}