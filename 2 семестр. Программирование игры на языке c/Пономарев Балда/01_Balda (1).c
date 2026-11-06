// Структура данных и вывод игрового поля
// - структуры state и word
// - функция print_state()

#include <stdio.h>
#include <string.h>

struct state {
    char field[5][5];   // Игровое поле
    int  w1, w2;        // Количество слов 1 и 2 игрока
    char word1[20][25]; // Слова 1 игрока
    char word2[20][25]; // Слова 2 игрока
    char word0[6];      // Исходное слово
    int  score1, score2;// Баллы 1 и 2 игрока
};

struct word {
    int n;                  // Число букв
    int rowc, colc;         // Строка и столбец добавляемой буквы
    char c;                 // Добавляемая буква
    int row[25], col[25];   // Строки и столбцы букв слова
    char w[25];             // Слово
};

// Печатает игровое поле и введенные слова
void print_state (struct state *s) {
    int i,j;
    printf ("\n    1  2  3  4  5  | ");
    printf ("       Игрок 1 - %3i      | ", s->score1);
    printf ("       Игрок 2 - %3i      |\n", s->score2);

    for (i=0; i<5; i++) {
        // Печатаем поле
        printf("%2i ", 10*(i+1));
        for (j=0; j<5; j++)
            printf (" %c ", s->field[i][j]);
        
        // Печатаем слова игроков
        printf(" | ");
        if ( (s->w1) > i )
            printf("%25s | ", s->word1[i]);
        else
            printf("%25s | ", "");
        if ( (s->w2) > i )
            printf("%25s |", s->word2[i]);
        else
            printf("%25s | ", "");
        printf("\n");
    }
    // Завершаем печать слов игроков
    for ( ; (s->w1)>i || (s->w2)>i ; i++) {
        printf("%18s", "");
        if ( (s->w1) > i )
            printf(" | %25s | ", s->word1[i]);
        else
            printf("   %25s | ", "");
        if ( (s->w2) > i )
            printf("%25s |", s->word2[i]);
        printf("\n");
    }
}

void main(){
    struct state st;
    char testword[] = "балда";
    int i;
    char *p = &(st.field[0][0]);
    for (i = 0; i<25; i++) *p++ = '.';  // заполняем поле "пустыми" символами
    p = &(st.field[2][0]);
    for (i = 0; i<5; i++) *p++ = testword[i]; // копируем начальное слово
    st.w2 = 7;
    st.w1 = 0;
    st.score2 = 123;
    st.score1 = 0;
    strncpy(st.word2[0],"привет",7);	// тестовые слова
    strncpy(st.word2[1],"морковь",8);
    strncpy(st.word2[2],"хлеб",5);
    strncpy(st.word2[3],"программа",10);
    strncpy(st.word2[4],"тестинг",8);
    strncpy(st.word2[5],"мир",4);
    strncpy(st.word2[6],"программирование",17);
    print_state(&st);
}