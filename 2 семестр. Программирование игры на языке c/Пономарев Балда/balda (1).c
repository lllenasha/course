// Раздельная компиляция
// Логика - проверка правил игры

#include "balda.h"

void main(){
    struct state st;
    struct word wrd;
    //int game=1;       // Флаг продолжения игры
    int step;           // Флаг выполнения хода
    int gamer = 0;      // Игрок, выполняющий ход

	void* dict = init_dict(fdict);	    // Подключаем словарь
	int nwords = *(int*)dict;		    // Количество слов
	char **dp = (char**)((int*)dict+1);	// Указатель на массив указателей				
	printf("Загружено слов: %i\n", nwords);

    init_game(&st);    // Создаем игру

    while (1) {
        print_state(&st);
        printf("Ход %i игрока\n", gamer+1);
        step = get_word(&st,&wrd);
        if (step == -1)             // Выход из игры
            break;
        else if (step == 0)         // Пропуск хода
            gamer = 1 - gamer;
        else {
            if (!check_word(&st, &wrd, dp, nwords)) { // Слово введено и оно верное
                #ifndef FINAL
                    print_path(&wrd);
                #endif
                add_word(&st, &wrd, gamer);
                gamer = 1 - gamer;
            }
        }
    }

	// Освобождаем память
	free(dict);
}