#include <windows.h> //библиотека для работы с системой
#include <stdlib.h>  //содержит определения и прототипы функций общего пользования
#include <locale.h>  //отвечает за работу с локальной культурой
#include <string.h>  //для работы со строками
#include <ctype.h>   //отвечает за преобразование и проверку символов
#include <stdio.h>   //для работы со средствами ввода-вывода
#include <wchar.h>   //для работы с символами
#include <time.h>    //для работы с датами и временем

#define MAX_NUM_WORDS 68000
#define MAX_NUM_LETTERS 11
#define SIZE 20

#define DBOLD    "\033[2m"
#define GREEN    "\033[0;32m"
#define RESET    "\033[0m"
#define RED      "\033[1;31m"

char DICTIONARY_WORDS[MAX_NUM_WORDS][MAX_NUM_LETTERS];
char ENTERED_WORDS[MAX_NUM_WORDS][MAX_NUM_LETTERS];
char WORD_GENERATION[MAX_NUM_WORDS][MAX_NUM_LETTERS];

void Greeting(){
    printf("\n");
    printf("  ╔══╗ ╔══╗╔═══╗╔═══╗╔══╗   ╔══╗╔══╗╔╗╔╗╔╗╔══╗ ╔══╗╔══╗╔══╗ ╔══╗╔════╗╔╗      ╔══╗\n");
    printf("  ║╔╗║ ║╔╗║║╔══╝║╔═╗║║╔╗║   ║╔╗║║╔╗║║║║║║║║╔╗║ ║╔╗║║╔╗║║╔╗║ ║╔╗║╚═╗╔═╝║║      ║╔╗║\n");
    printf("  ║║║║ ║║║║║╚══╗║╚═╝║║║║║   ║║║║║║║║║╚╝╚╝║║╚╝║ ║║║║║║║║║╚╝╚╗║╚╝║  ║║  ║╚══╗   ║╚╝╚╗\n");
    printf("  ║║║║ ║║║║║╔═╗║║╔══╝║║║║   ║║║║║║║║║╔╗╔╗║║╔╗║ ║║║║║║║║║╔═╗║║╔╗║  ║║  ║╔═╗║   ║╔═╗║\n");
    printf(" ╔╝╚╝╚╗║╚╝║║╚═╝║║║   ║╚╝║   ║║║║║╚╝║║║║║║║║║║║╔╝║║║║╚╝║║╚═╝║║║║║  ║║  ║╚═╝║   ║╚═╝║\n");
    printf(" ╚════╝╚══╝╚═══╝╚╝   ╚══╝   ╚╝╚╝╚══╝╚╝╚╝╚╝╚╝╚╝╚═╝╚╝╚══╝╚═══╝╚╝╚╝  ╚╝  ╚═══╝   ╚═══╝\n");
    printf("                       ╔╗╔╗╔══╗╔═══╗╔══╗╔═══╗╔╗╔╗╔╗╔╗╔╗╔╗╔══╗\n");
    printf("                       ║║║║║╔╗║║╔══╝║╔╗║║╔═╗║║║║║║║║║║║║║║╔═╝\n");
    printf("                       ║╚╝║║╚╝║║╚══╗║║║║║╚═╝║║║║║║║║║║║║╚╝║\n");
    printf("                       ║╔╗║║╔╗║║╔═╗║║║║║║╔══╝║║║║║║║║╔║║╔╗║\n");
    printf("                       ║║║║║║║║║╚═╝║║╚╝║║║   ║╚╝╚╝║║╚╝║║║║╚═╗\n");
    printf("                       ╚╝╚╝╚╝╚╝╚═══╝╚══╝╚╝   ╚════╗╚══╝╚╝╚══╝\n");
    printf("\n");
    printf("%s                                                               <c> Кучеренко Елена, 2023\n%s", DBOLD, RESET);
    printf("НОВАЯ ИГРА \n");
    printf(" %s1.%s Наборщик один на один\n", DBOLD, RESET);
    printf(" %s2.%s Правила игры\n", DBOLD, RESET);
    printf(" %s3.%s Рейтинг\n", DBOLD, RESET);
    printf(" %s4.%s Выход\n", DBOLD, RESET);
}

void Rules(){
    printf("                                                                                       \n");
    printf("                                  ╔══════════════════╗                                 \n");
    printf(" ╔════════════════════════════════╣   ПРАВИЛА ИГРЫ   ╠════════════════════════════════╗\n");
    printf(" ║                                ╚══════════════════╝                                ║\n");
    printf(" ║ В игре принимают участие два игрока.                                               ║\n");
    printf(" ║ В начале игры произвольно подбирается слово.                                       ║\n");
    printf(" ║ Задача игроков , пользуясь буквами этого слова, составить новые слова.             ║\n");
    printf(" ║ 1) Писать можно только имена существительные в именительном падеже, ед.ч.          ║\n");
    printf(" ║ 2) Каждое слово должно быть составлено только из тех букв, которые есть в слове.   ║\n");
    printf(" ║ 3) Нельзя использовать слова, которые уже были воздействованы ранее.               ║\n");
    printf(" ║ Игра заканчивается в тот момент, когда игроки больше не cмогут сделать ход.        ║\n");
    printf(" ║                                        ...                                         ║\n");
    printf(" ╚════════════════════════════════════════════════════════════════════════════════════╝\n");
    printf(" ╔════════════════╦═════════════════════════════════════════════════════════════════╗\n");
    printf(" ║      ПРИМЕР    ║ Наборщик: наборк, щи, борщ, кино, бар, банщик, барон, барин.    ║\n");
    printf(" ╚════════════════╩═════════════════════════════════════════════════════════════════╝\n");
    printf(" Нажмите 1, чтобы начать игру двух пользователей.. \n");
    printf(" Нажмите 2, чтобы ознакомиться с правилами игры..  \n");
    printf(" Нажмите 3, чтобы открыть турнирную таблицу..      \n");
    printf(" Нажмите 4, чтобы выйти из игры..                  \n");
    printf("\n");
}
void Farewell(){
    printf("\n");
    printf("                     ╔═════════════════════════════════════════════╗\n");
    printf("                     ║      СПАСИБО ЗА ИГРУ! ДО НОВЫХ ВСТРЕЧ!      ║\n");
    printf("                     ╚═════════════════════════════════════════════╝\n");
}

struct Date{
    int gameCounter1;
    char name1[100];
    int gameCounter2;
    char name2[100];
    int score;
    char name[999];
};

int Compare(const void* a, const void* b) { //это объявление указателя на константный тип данных "void", который может указывать на любой объект.
    struct Date* p1 = (struct Date*)a;      //это приведение типов указателя "a" к типу "struct Date*", чтобы получить доступ к полям структуры "Date".
    struct Date* p2 = (struct Date*)b;
    return p2->score - p1->score;           //вычисление разницы между значениями поля "score" структур "p2" и "p1", чтобы сравнить их в функции сортировки. 
}

int Parse(){
    FILE *file;
    struct Date players[50];
    char line[100];
    char scoreString[50];
    int i, j, n = 0;
    char kolvo[50];
    file = fopen("proverka.txt", "a+");
    if (!file) {
        printf("%sНе удалось открыть файл!%s", RED, RESET);
        return 1;
    }
    while (fgets(line, sizeof line, file) != NULL){  //константное выражение со значением 0
        struct Date *player = &players[n++];         //Эта строка объявляет указатель на структуру Data с именем player и инициализирует его адресом элемента массива "players", который имеет индекс "n". Затем значение "n" увеличивается на 1 с помощью оператора инкремента "++".
        i = 0;
        j = 0;
        while (line[i] != ':'){
            player->name[i] = line[i];              //Эта строка копирует символ с индексом i из строки line в символ с индексом i в массиве name у объекта player. Таким образом, она копирует имя игрока из входной строки в объект игрока.
            i++;
        }
        player->name[i] = '\0';
        i++;
        while (line[i] != '\0'){
            scoreString[j] = line[i];
            i++;
            j++;
        }
        scoreString[j] = '\0';
        player->score = atoi(scoreString);
    }
    fclose(file);
    qsort(players, n, sizeof(struct Date), Compare);

    for(i = 0; i < n; i++){
        printf("                                    %s    \t %d\n", players[i].name, players[i].score);
        printf("%s                               ═════════════════════════%s\n", DBOLD, RESET);
    }
}

int FirstWritingToAFile(struct Date users){
    char line[100], arr2[100], arr1[100],  buffer[100], line2[100];
    int array2, a = 0, b = 0, c = 0, d = 0, m = 0;
    FILE *f = fopen("proverka.txt", "a+");
    while (fgets(line, sizeof line, f) != NULL){
        if (strstr(line, users.name1)){ //ЕСЛИ НАХОДИТ ИМЯ ИГРОКА, ТО...
            a++;
            int j = 0;
            int i = 0;
            while (line[i] != ':'){
                arr1[i] = line[i];
                i++;
            }
            arr1[i] = '\0';
            i++;
            while (line[i] != '\0'){
                arr2[j] = line[i];
                i++;
                j++;
            }
            arr2[j] = '\0';
            array2 = atoi(arr2);
            if (users.gameCounter1 > array2){
                b++;
            }
        }
    }
    if (a == 0){
        fprintf(f, "%s:%i\n", users.name1, users.gameCounter1);
    }
    fclose(f);
    if (b != 0){
        FILE *l = fopen("proverka.txt", "r");
        FILE *file = fopen("itog.txt", "w+");
            while (fgets(buffer, sizeof buffer, l) != NULL){
                if (strstr(buffer, users.name1)){
                    fprintf(file, "%s:%i\n", users.name1, users.gameCounter1);
                }
                else {
                    fprintf(file, "%s", buffer);
                }
            }
        fclose(file);
        fclose(l);
        m++;
    }
    if (m != 0){
        FILE *li = fopen("proverka.txt", "w+");
        FILE *fi = fopen("itog.txt", "r");
            while (fgets(line2, sizeof line2, fi) != NULL){
                fprintf(li, "%s", line2);
            }
        fclose(fi);
        fclose(li);
    }
}

int SecondWritingToAFile(struct Date users){
    char line[100], arr2[100], arr1[100],  buffer[100], line2[100];
    int array2, a = 0, b = 0, c = 0, d = 0, m = 0;
    FILE *f2 = fopen("proverka.txt", "a+");
    while (fgets(line, sizeof line, f2) != NULL){
        if (strstr(line, users.name2)){ //ЕСЛИ НАХОДИТ ИМЯ ИГРОКА, ТО...
            a++;
            int j = 0;
            int i = 0;
            while (line[i] != ':'){
                arr1[i] = line[i];
                i++;
            }
            arr1[i] = '\0';
            i++;
            while (line[i] != '\0'){
                arr2[j] = line[i];
                i++;
                j++;
            }
            arr2[j] = '\0';
            array2 = atoi(arr2);
            if (users.gameCounter2 > array2){
                b++;
            }
        }
    }
    if (a == 0){
        fprintf(f2, "%s:%i\n", users.name2, users.gameCounter2);
    }
    fclose(f2);
    if (b != 0){
        FILE *l2 = fopen("proverka.txt", "r");
        FILE *file2 = fopen("itog.txt", "w+");
            while (fgets(buffer, sizeof buffer, l2) != NULL){
                if (strstr(buffer, users.name2)){
                    fprintf(file2, "%s:%i\n", users.name2, users.gameCounter2);
                }
                else {
                    fprintf(file2, "%s", buffer);
                }
            }
        fclose(file2);
        fclose(l2);
        m++;
    }
    if (m != 0){
        FILE *li2 = fopen("proverka.txt", "w+");
        FILE *fi2 = fopen("itog.txt", "r");
            while (fgets(line2, sizeof line2, fi2) != NULL){
                fprintf(li2, "%s", line2);
            }
        fclose(fi2);
        fclose(li2);
    }
}

int Check(char *s2){ //проверка по словарю
    int q = 0, w = 0;
    char t[MAX_NUM_LETTERS];
    strcpy(t, s2);
    
    while (t[q] != '\0'){
        t[q] = tolower(t[q]);
        q++;
    }
    
    while (w < MAX_NUM_WORDS){
        if (!strcmp(t, DICTIONARY_WORDS[w])){
            return 1;
        }
        w++;
    }
    return 0;
}

int FirstCheck(char *s1, char *s2){ //проверка по слову
// s1 - игровое слово s2-введенное слово
    int k = 0, n;
    char t[MAX_NUM_LETTERS];
    strcpy(t, s1); //запоминаем заданное слово
    for (int i = 0; i < strlen(s2) && k != -1; i++){ //цикл по всему слову s2
        k = -1; //допустим слово не удовлетворяет требованиям
        for (int j = 0; j < strlen(s1) && k == -1; j++) //цикл по заданному слову (s1)
            if ((s1[j]) == (s2[i])){
                k = j;
            }
        if (k != -1){ //если символ из строки s2 есть в строке s1 то
            n = strlen(s1) - 1; //запоминаем длину строки s1
            for (int j = k; j < n; j++)
            s1[j] = s1[j+1];
            s1[n] = '\0';
        }
    }
    strcpy(s1, t); //восстанавливаем заданное слово
    if (k != -1 && Check(s2)){ //если слово удовлетворяет поиску, то далее проверяем существует ли слово вообще
        return 1;
    }
    else {
        return 0;
    }
}

int SecondCheck(char allWords[MAX_NUM_WORDS][MAX_NUM_LETTERS], int *number, char word[MAX_NUM_LETTERS]){ //проверяет на повтор
    int i = 0, k = -1;
    for (i; i < *number && k == -1; i++)
        if (stricmp(allWords[i], word) == 0){
            k = i; //если очередной элемент массива равен переданному слову, то запоминаем его индекс
        }
    //если это слово не повтор то
    if (k == -1){
        strcpy(allWords[*number], word);
        (*number)++;
    }
    if (k != -1){ //если это слово повтор, то возвращем 1
        return 1;
    }
    else {
        return 0;
    }
}

int ThePlayersMove(char *playWord, char ENTERED_WORDS[MAX_NUM_WORDS][MAX_NUM_LETTERS], int *counter, int *score, char word[MAX_NUM_LETTERS]){
    int resultFirstCheck, resultSecondCheck, end = 0, resultFirstCheckh, resultSecondCheckh, n = 0, b = 0;
    if (!strcmp(word, "stop")){
        return 2;
    }
    if (!strcmp(word, "hint")){
        if (*score < 15){
            printf("%sУ вас недостаточно очков! %s", RED, RESET);
            return 0;
        }
        else {
            while (n == 0){
                srand(time(NULL));
                memcpy(word, DICTIONARY_WORDS[rand() % MAX_NUM_WORDS - b], 11);
                resultFirstCheck = FirstCheck(playWord, word);
                if (resultFirstCheck == 1){
                    resultSecondCheck = SecondCheck(ENTERED_WORDS, counter, word);
                    if (resultSecondCheck == 0){
                        n++;
                    }
                }
                b++;
            }
            printf("%s", DBOLD);
            printf("ПОДСКАЗКА   :       %s\n", word);
            printf("%s", RESET);
            return 1;
        }
    }
    do{ //Цикл do...while ? это цикл с постусловием, где истинность выражения, проверяющего Условие проверяется после выполнения Блока Операций, заключенного в фигурные скобки.
        resultFirstCheck = FirstCheck(playWord, word);
        if (resultFirstCheck == 1){
            resultSecondCheck = SecondCheck(ENTERED_WORDS, counter, word);
            if (resultSecondCheck == 1){
                printf("%sТакое слово уже использовалось! %s", RED, RESET);
                end ++;
                resultSecondCheck --;
            }
        }
    }
    while (resultFirstCheck == 1 && resultSecondCheck == 1);
    if (end != 0){
        resultFirstCheck = 0;
        return resultFirstCheck;
    }
    else if (resultFirstCheck != 0){
        *score = *score + strlen(word);
        return resultFirstCheck;
    }
}

int FillDictionary(int *number){
    FILE *f = fopen("dictionary.txt", "r");
	if (!f){
        return 0;
    }
    else {
        *number = 0;
        while (*number < MAX_NUM_WORDS && fscanf(f, "%s", DICTIONARY_WORDS[(*number)++]) > 0);
        (*number)--;
        fclose(f);
        if (*number == 0){
            return 0;
        }
        else {
            return 1;
        }
    }
}

int Score(int player1, int player2, struct Date users){
    users.gameCounter1  = player1;
    users.gameCounter2  = player2;
    FirstWritingToAFile(users);
    SecondWritingToAFile(users);
    if (player1 > player2){
        printf("\n");
        printf("                           ПОБЕДУ ОДЕРЖАЛ ПЕРВЫЙ ИГРОК! СЧЕТ:\n");
        printf("                     ╔══════════════════════╦═════════════════════╗\n");
        if (player1 < 10){
            printf("                     ║          %i           ║", player1);
        }
        else printf("                     ║          %i          ║", player1);
        if (player2 < 10){
            printf("          %i          ║\n", player2);
        }
        else printf("          %i         ║\n", player2);
        printf("                     ╚══════════════════════╩═════════════════════╝\n");
        printf("\n");
        Farewell();
    }
    else if (player1 < player2){
        printf("\n");
        printf("                           ПОБЕДУ ОДЕРЖАЛ ВТОРОЙ ИГРОК! СЧЕТ:\n");
        printf("                     ╔══════════════════════╦═════════════════════╗\n");
        if (player1 < 10){
            printf("                     ║          %i           ║", player1);
        }
        else printf("                     ║          %i          ║", player1);
        if (player2 < 10){
            printf("          %i          ║\n", player2);
        }
        else printf("          %i         ║\n", player2);
        printf("                     ╚══════════════════════╩═════════════════════╝\n");
        printf("\n");
        Farewell();
    }
    else if (player1 = player2){
        printf("\n");
        printf("\n                                      НИЧЬЯ! СЧЕТ:\n");
        printf("                     ╔══════════════════════╦═════════════════════╗\n");
        if (player1 < 10){
            printf("                     ║          %i           ║", player1);
        }
        else printf("                     ║          %i          ║", player1);
        if (player2 < 10){
            printf("          %i          ║\n", player2);
        }
        else printf("          %i         ║\n", player2);
        printf("                     ╚══════════════════════╩═════════════════════╝\n");
        printf("\n");
        Farewell();
        }
}

void Rating(){
    printf("\n");
    printf("                               ╔═══════════════════════╗\n");
    printf("                               ║   ТУРНИРНАЯ ТАБЛИЦА   ║\n");
    printf("                               ╚═══════════════════════╝\n");
    printf("\n");
    Parse();
    printf("\n");
    printf("\n");
}

int main(){
    system("cls");
    char playWord[SIZE];
    char word[MAX_NUM_LETTERS];
    int result, score1 = 0, score2 = 0, counter = 0, countWords = 0, stopWhile = 0, n = 0;
    struct Date users;
    Greeting();
    int choice;
    printf("ВАШ ВЫБОР: ");
    scanf("%i", &choice);
    while (choice != 4){
        while (choice != 1 && choice != 2 && choice != 3 && choice != 4){
            printf("%sНекорректный ввод! Попробуйте еще раз!\n%s", RED,    RESET);
            printf("ВАШ ВЫБОР: ");
            scanf("%i", &choice); 
        }
        if (choice == 1){
            while (stopWhile != 1){
                FILE *file = fopen("dictionary.txt", "r");
                char *fileContents[MAX_NUM_WORDS+1];
                char buffer[MAX_NUM_WORDS + 1];
                for (size_t i = 0; fgets(buffer, sizeof buffer, file); i++){
                    if (strlen(buffer) == 11){
                        n++;
                        fileContents[n] = strdup(buffer);
                    }
                }
                fclose(file);
                // srand(time(NULL)); // инициализация генератора псевдослучайных чисел
                int randomIndex = 0 + rand()%(n); // генерация случайного индекса
                if (randomIndex == 0){
                    randomIndex++;
                }
                memcpy(playWord, fileContents[randomIndex], 11);
                result = FillDictionary(&countWords);
                if (result == 0){
                    printf("%s Не удалось загрузить словарь! Попробуйте зайти в игру еще раз!\n%s ", RED,    RESET);
                    return 0;
                }
                printf("\n%sИМЯ ИГРОКА 1:       ", DBOLD);
                scanf("%s", &users.name1);
                printf("ИМЯ ИГРОКА 2:       ");
                scanf("%s", &users.name2);
                printf("%s", RESET);
                printf("\n");
                printf("                            ИГРА НАЧАЛАСЬ! ЗАГАДАННОЕ СЛОВО:\n");
                printf("                                ╔═════════════════════╗\n");
                printf("                                      %s", playWord);
                printf("                                ╚═════════════════════╝\n");
                printf("\n");
                stopWhile++;
            }
            printf("ХОД ИГРОКА 1:       ");
            scanf("%s", &word);
            result = ThePlayersMove(playWord, ENTERED_WORDS, &counter,  &score1, word);
            if (result == 0){
                printf("%sНекорректный ввод! Осталась одна попытка!\n%s", RED,    RESET);
                printf("ХОД ИГРОКА 1:       ");
                scanf("%s", &word);
                result = ThePlayersMove(playWord, ENTERED_WORDS, &counter,  &score1, word);
                if (result == 0){
                    Score(score1, score2, users);
                    break;
                }
            }
            else if (result == 2){
                Score(score1, score2, users);
                break;
            }
            printf("%s+%d\n%s", GREEN, strlen(word), RESET);
            
            printf("ХОД ИГРОКА 2:       ");
            scanf("%s", &word);
            result = ThePlayersMove(playWord, ENTERED_WORDS, &counter, &score2, word);
            if (result == 0){
                printf("%sНекорректный ввод! Осталась одна попытка!\n%s", RED,    RESET);
                printf("ХОД ИГРОКА 2:       ");
                scanf("%s", &word);
                result = ThePlayersMove(playWord, ENTERED_WORDS, &counter,  &score2, word);
                if (result == 0){
                    Score(score1, score2, users);
                    break;
                }
            }
            else if (result == 2){
                Score(score1, score2, users);
                break;
            }
            printf("%s+%d\n%s", GREEN, strlen(word), RESET);
        }
        else if (choice == 2){
            Rules();
            printf ("ВАШ ВЫБОР: ");
            scanf("%i", &choice);
        }
        else if (choice == 3){
            Rating();
            printf ("ВАШ ВЫБОР: ");
            scanf("%i", &choice);
        }
    }
    if (choice == 4){
        Farewell();
    }
}