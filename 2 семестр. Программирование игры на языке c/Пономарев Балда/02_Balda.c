// Интерфейс игры
// - функции init_game(), get_word(), add_word(), main(), print_path()

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct state {
    char field[5][5];   // Игровое поле
    int w1, w2;         // Количество слов 1 и 2 игрока
    char word1[20][25]; // Слова 1 игрока
    char word2[20][25]; // Слова 2 игрока
    char word0[6];      // Исходное слово
    int score1, score2; // Баллы 1 и 2 игрока
};

struct word {
    int n;                  // Число букв
    int rowc, colc;         // Строка и столбец добавляемой буквы
    char c;                 // Добавляемая буква
    int row[25], col[25];   // Строки и столбцы букв слова
    char w[25];             // Слово
};

void print_state (struct state *s);
void print_path(struct word *wrd);
void init_game (struct state *st);
int get_word (struct state *st, struct word *wrd, int gamer);
int check_word (struct state *st, struct word *wrd);
void add_word (struct state *st, struct word *wrd, int gamer);

void main(){
    struct state st;
    struct word wrd;
    int step;           // Флаг выполнения хода
    int gamer = 0;      // Игрок, выполняющий ход

    init_game(&st);     // Создаем игру

    while (1) {
        print_state(&st);   // Выводим игровое поле
        step = get_word(&st,&wrd,gamer+1);	// Вводим данные от пользователя (заполняем wrd или пропускаем ход)
        if (step == 0) {
            gamer = 1 - gamer; 	// Смена игрока
        } else if (step == -1){
            exit(0);			// Выход из игры
        } else {
			// Игрок не пропустил ход, а ввел слово
            step = check_word(&st, &wrd); // Проверяем слово на корректность. Пока стоит "заглушка"
			if (step == 0) {
				// Слово верное
				#ifndef FINAL
					print_path(&wrd);		// Печатаем информацию по введенному слову
				#endif
				add_word(&st, &wrd, gamer);	// Добавлвяем слово игроку
				gamer = 1 - gamer;			// Меняем игрока (0->1, 1->0)
			}
            else {
                // Печать сообщения об ошибке (код ошибки - step)
            }
		}
    }
}

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
    for (int i=0; i<25; i++)	// Очищаем поле
        *p++ = '.';

    char str[10]={};
    do {
        printf("Введите начальное слово: ");
        fflush(stdin);
        scanf("%s", str);
    } while (strlen(str)!=5);		  // Вводим слово из 5 букв
    strncpy ( st->field[2], str, 5);  // Копируем слово на поле
    strcpy (st->word0, str);	// Копируем слово в state.word0
    st->w1 = 0;
    st->w2 = 0;
    st->score1 = 0;
    st->score2 = 0;
}

// Вводит слово wrd с клавиатуры (без проверки)
// 0 - пропуск хода; -1: выход из игры; 1 - слово введено
int get_word (struct state *st, struct word *wrd, int gamer){
    int cell, row, col;
    int flag = 1, i;
    char c;
    
    // Вводим добавляемую букву
    printf ("Игрок %i.\nДобавляемый символ (0 - пропуск хода, 9 - выйти из игры): ",gamer);
    fflush(stdin); c = getchar();
    if (c=='0')
        return 0;
    if (c=='9')
        return -1;
    wrd->c = c;	// Запоминаем введенный символ
    while (flag){
        printf ("Ячейка: ");
        fflush(stdin); scanf("%i", &cell);
        row = cell/10 - 1;	//Вводим координаты добавляемой буквы
        col = cell%10 - 1;
        if (row>=0 && row<=4 && col>=0 && col<=4)
            if (st->field[row][col]=='.')
                flag = 0;
            else
                printf("В ячейке уже есть буква.\n");
        else
            printf("Некорректный номер ячейки.\n");
    }
    wrd->rowc = row; // Запоминаем координаты добавленной буквы
    wrd->colc = col; // (но на поле ее пока не проставляем)

    // Вводим слово
    i = 0; flag = 1;
    while (flag) {
        printf("Ячейка слова (0 - закончить ввод слова): ");
        fflush(stdin); scanf("%i", &cell);
        if (cell==0) flag=0;
        else {	// Записываем координаты букв слова в row[i],col[i], а буквы слова - в w[i]
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

// Проверяет слово по словарю
int check_word (struct state *st, struct word *wrd){
    return 0;
}

// Добавляет слово wrd игроку gamer
void add_word (struct state *st, struct word *wrd, int gamer){
    st->field[wrd->rowc][wrd->colc] = wrd->c; // Проставляем введенный символ на поле
    if (gamer) {	// Добавляем слово указанному игроку
        strcpy (st->word2[st->w2], wrd->w);
        st->w2++;
        st->score2 += wrd->n;
    } else {
        strcpy (st->word1[st->w1], wrd->w);
        st->w1++;
        st->score1 += wrd->n;
    }
}