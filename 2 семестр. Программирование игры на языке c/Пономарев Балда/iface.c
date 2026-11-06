#include "balda.h"

// Печатает игровое поле и введенные слова
void print_state (struct state *s) {
    int i,j;

    #ifdef FINAL
        system("cls");
    #endif
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
    printf("\n");
}

// Печатает информацию о совершенном ходе
void print_path(struct word *wrd)
{
	int i;	
	int *pr = wrd->row;
    int *pc = wrd->col;
	printf("\nДобавлена буква \'%c\' в ячейку %i%i.\nПуть: ", wrd->c, wrd->rowc+1, wrd->colc+1);
	for(i=1; i<(wrd->n); i++)
		printf("%i%i-", (*pr++)+1, (*pc++)+1 );
	printf("%i%i\n", (*pr)+1, (*pc)+1 );
	printf("Добавлено слово \"%s\",  ", wrd->w);
	printf("количество букв: %i\n", wrd->n);
}

// Заполняет структуру st,
// начальное слово запрашивается с клавиатуры
void init_game (struct state *st){
    char *p = st->field[0];
    for (int i=0; i<25; i++)
        *p++ = '.';

    char str[10]={};
    do {
        printf("Введите начальное слово: ");
        fflush(stdin);
        scanf("%s", str);
    } while (strlen(str)!=5);
    strncpy ( st->field[2], str, 5);
    strcpy (st->word0, str);
    st->w1 = 0;
    st->w2 = 0;
    st->score1 = 0;
    st->score2 = 0;
}

// Вводит слово wrd с клавиатуры (без проверки)
// 0 - пропуск хода; 1 - слово введено
int get_word (struct state *st, struct word *wrd){
    int cell, row, col;
    int flag = 1, i;
    char c;
    
    // Вводим добавляемую букву
    printf ("Добавляемый символ (0 - пропуск хода, 9 - выйти из игры): ");
    fflush(stdin); c = getchar();
    if (c=='0') return 0;
    if (c=='9') return -1;
    wrd->c = c;
    while (flag){
        printf ("Ячейка: ");
        fflush(stdin); scanf("%i", &cell);
        row = cell/10 - 1;
        col = cell%10 - 1;
        if (row>=0 && row<=4 && col>=0 && col<=4)
            if (st->field[row][col]=='.')
                flag = 0;
            else
                printf("В ячейке уже есть буква.\n");
        else
            printf("Некорректный номер ячейки.\n");
    }
    wrd->rowc = row;
    wrd->colc = col;

    // Вводим слово
    i = 0; flag = 1;
    while (flag) {
        printf("Ячейка слова (0 - закончить ввод слова): ");
        fflush(stdin); scanf("%i", &cell);
        if (cell==0) flag=0;
        else {
            row = cell/10 - 1;
            col = cell%10 - 1;
            if (row>=0 && row<=4 && col>=0 && col<=4) {
                if (row == wrd->rowc && col == wrd->colc)
                    wrd->w[i] = c;
                else
                    wrd->w[i] = st->field[row][col];
                wrd->row[i] = row;
                wrd->col[i] = col;
                i++;
            }
            else
                printf("Некорректный номер ячейки.\n");
        }
    }
    wrd->w[i] = '\0';
    wrd->n = i;
    return 1;
}