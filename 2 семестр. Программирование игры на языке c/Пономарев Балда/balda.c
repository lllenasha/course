// Подсказки от компьютера
#include "balda.h"

void main(){
    struct state st;
    struct word wrd;
    //int game=1;       // Флаг продолжения игры
    int step;           // Флаг выполнения хода
    int gamer = 0;      // Игрок, выполняющий ход

	void* dict = init_dict(fdict);	    // Подключаем словарь
	int nwords = *(int*)dict;		    // Количество слов
	char **dp = (char**)((char*)dict+sizeof(int));	// Указатель на массив указателей				
	printf("Загружено слов: %i\n", nwords);
	void* hash = init_hash(dp, nwords);
	struct word *cw = malloc(sizeof(struct word)*10000); // Массив для хранения слов

    init_game(&st);    // Создаем игру

    while (1) {
        print_state(&st);
        printf("Ход %i игрока\n", gamer+1);
        step = get_word(&st,&wrd);
        if (step == -1)             // Выход из игры
            break;
        else if (step == 0)         // Пропуск хода
            gamer = 1 - gamer;
        else if (step == -2) { 		// Подсказка
			int nw = get_all_words_in_state(&st,cw,hash,dp);
			for (int i=0; i<nw; i++)
				printf("%s\n", cw[i].w);
		}		
		else if (!check_word(&st, &wrd, dp, nwords)) { // Слово введено и оно верное
            #ifndef FINAL
                print_path(&wrd);
            #endif
            add_word(&st, &wrd, gamer);
            gamer = 1 - gamer;
        }
    }
    
	// Освобождаем память
	free(dict);
}