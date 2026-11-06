#include "balda.h"

/* Проверяет введенное слово. При правильном слове возвращает 0.
st - текущее состояние игры; wrd - проверяемое слово;
dp - массив указателей на слова из словаря; nwords - количество слов в словаре
Коды ошибок:
1 - маршрут не через соседние клетки
2 - проходит 2 раза через одну букву
3 - не проходит через добавленную букву
4 - слово уже использовалось
5 - слова нет в словаре
6 - пустое слово*/
int check_word (struct state *st, struct word *wrd, char **dp, int nwords){
    int i,j;

    // Слово не пустое
    if (!(wrd->n)) return 6;

    // 1 Маршрут идет через соседние клетки
    int *pr1 = wrd->row, *pc1 = wrd->col;
    int *pr2 = pr1++, *pc2 = pc1++;
    for (i=1; i<(wrd->n); i++) {
        if (    ((*pr1==*pr2) && (abs(*pc1-*pc2)==1)) || 
                ((*pc1==*pc2) && (abs(*pr1-*pr2)==1))      ) {
            *pr1++; *pc1++;
            *pr2++; *pc2++;
        } else {
            printf("Некорректный маршрут (%i%i-%i%i)\n", *pr2+1, *pc2+1, *pr1+1, *pc1+1);
            return 1;
        }
    }

    // 2 Не проходит дважды через одну и ту же букву
    pr1 = wrd->row, pc1 = wrd->col;
    for (i=1; i<(wrd->n); i++) {
        pr2 = pr1 + 1, pc2 = pc1 + 1;
        for (j=i; j<(wrd->n); j++)
            if (*pr1==*pr2 && *pc1==*pc2){
                printf("Одна буква используется два раза (%i%i)\n", *pr1+1, *pc1+1);
                return 2;
            } else {
                pr2++; pc2++;
            }
        pr1++; pc1++;
    }

    // 3 Проходит через добавленную букву
    pr1 = wrd->row, pc1 = wrd->col;
    j = 1;
    for (i=0; i<(wrd->n); i++, pr1++, pc1++)
        if ( *pr1 == wrd->rowc && *pc1 == wrd->colc )
            j = 0;
    if (j) {
        printf("Слово не использует добавленную букву (%i%i)\n", wrd->rowc+1, wrd->colc+1);
        return 3;
    }

    // 4 Не совпадает с ранее введенными словами
    if (!strcmp(wrd->w, st->word0)) {
        printf("Слово уже использовалось\n");
        return 4;
    }
    for (i=0; i<(st->w1); i++)
        if (!strcmp(wrd->w, st->word1[i])) {
            printf("Слово уже использовалось\n");
            return 4;
        }
    for (i=0; i<(st->w2); i++)
        if (!strcmp(wrd->w, st->word2[i])) {
            printf("Слово уже использовалось\n");
            return 4;
        }

    // 5 Слова нет в словаре
    if ( dict_word(dp, nwords, wrd->w) == -1 ) {
        printf("Слова \"%s\" нет в словаре\n",wrd->w);
        return 5;
    }
    return 0;
}

// Добавляет слово wrd игроку gamer
void add_word (struct state *st, struct word *wrd, int gamer){
    st->field[wrd->rowc][wrd->colc] = wrd->c;
    if (gamer) {
        strcpy (st->word2[st->w2], wrd->w);
        st->w2++;
        st->score2 += wrd->n;
    } else {
        strcpy (st->word1[st->w1], wrd->w);
        st->w1++;
        st->score1 += wrd->n;
    }
}

//
// 	ТЕСТИРУЕМ МОДУЛЬ
//

// Нужны функции из dict.c и iface.c
// Проверяем check_word
void test_check_word (struct state *st, char **dp, int nwords) {
	printf("\n\t\t\tТестируем функцию проверки");
	printf("\n\t\t\tправильности введенного слова\n\n");

	struct word wr1 = {3,1,1,'в',	// Верный маршрут
					{1,2,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
					{1,1,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0},
					"вал"};
	print_path(&wr1);	
	if(check_word(st,&wr1,dp,nwords)==0) printf("test passed\n");
	
	struct word wr2 = {5,1,1,'в',	// Переход на не соседнюю клетку
					{1,2,2,3,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					{1,1,2,3,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					"валли"};
	print_path(&wr2);
	if(check_word(st,&wr2,dp,nwords)==1) printf("test passed\n");
	else printf("TEST FAIL\n");
	
	struct word wr3 = {5,1,1,'в',	// Проходит 2 раза через 1 букву
					{1,2,2,1,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					{1,1,2,2,1, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					"валли"};
	print_path(&wr3);
	if(check_word(st,&wr3,dp,nwords)==2) printf("test passed\n");
		else printf("TEST FAIL\n");
	
	struct word wr4 = {5,1,1,'в',	// Не проходит через добавляемую букву
					{2,2,3,3,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					{2,1,1,2,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					"валли"};
	print_path(&wr4);
	if(check_word(st,&wr4,dp,nwords)==3) printf("test passed\n");
		else printf("TEST FAIL\n");	

	st->w1=1;
	char testword4[]="вал";
	strcpy(&(st->word1[0][0]),testword4);	
	struct word wr5 = {3,1,1,'в',	// Слово уже использовалось
					{1,2,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					{1,1,2,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					"вал"};
	print_path(&wr5);	
	if(check_word(st,&wr5,dp,nwords)==4) printf("test passed\n");
		else printf("TEST FAIL\n");	
	
	struct word wr6 = {5,1,1,'в',	// Слова нет в словаре
					{1,2,2,2,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					{1,1,2,3,3, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0, 0,0,0,0,0,},
					"валли"};
	print_path(&wr6);	
	if(check_word(st,&wr6,dp,nwords)==5) printf("test passed\n");
		else printf("TEST FAIL\n");	
}
/*
void main()
{
	int i;
	struct state st;
	struct word wr;

	// Загружаем словарь
	void* dict = init_dict(fdict);	// Подключаем словарь	
	int  nwords = *(int*)dict;		// Количество слов
	char **dp = (char**)(dict+sizeof(int));	// Указатель на массив указателей	
	printf ("Загружено %i слов\n", nwords);		

	// Создаем тестовую игру
	char testword3[]="тест!";
	char *p = &(st.field)[0][0];
	for (i=0; i<25; i++) *p++ ='.';
	p = &(st.field)[2][0];
	for (i=0; i<5; i++) *p++ = testword3[i];
	st.w1=0;
	st.w2=0;
	st.score1=0;
	st.score2=0;	
	print_state(&st);
	
	test_check_word(&st, dp, nwords);
	
	free(dict);
	getchar();
}
*/