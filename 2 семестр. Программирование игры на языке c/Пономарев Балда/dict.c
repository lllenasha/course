#include "balda.h"

// Инициализирует словарь слов из файла fname
// Слова с дефисами опускаются
// Выходной массив содержит:
// - sizeof(int) - количество слов - words
// - words*sizeof(void*) - указатели на начала слов
// - слова без пропусков
void* init_dict(char* fname) {
	char str[100];
	FILE *fp;
	fp = fopen(fname, "r");
	if (!fp) {
		fprintf(stderr, "Ошибка при открытии файла \"%s\"", fname);
		return 0;
	}

	// Оцениваем размер словаря
	int nwords=0, size=0;
	while(fscanf(fp, "%s", str)!=EOF) {
		nwords++;
		size += strlen(str)+1;
	}
	fclose(fp);

	// Выделяем память
	size_t dict_size = sizeof(int) + nwords*sizeof(char**) + size;
	void* pdict = malloc(dict_size);
	if (pdict)
		printf("Загружаем словарь.\nКоличество слов: %i.\nОбъем словаря: %i байт\nДля хранения требуется %i байт\n", nwords, size, dict_size);
	else {
		fprintf(stderr, "Недостаточно памяти");
		return 0;
	}

	// Загружаем слова
	fp = fopen(fname, "r");
	*(int*)pdict = nwords;
	char **dp = (char**)((char*)pdict+sizeof(int));	// Указатель на массив указателей
	char *dw  = (char*)(dp+nwords);		// Указатель на слова
	int n = 0;
	while(fscanf(fp, "%s", str)!=EOF) {
		*dp = dw;
		strcpy(dw, str);
		//if ((n++ > 12000)&&(n<12050)) printf("Скопировано слово %i: %s-%s-%s\n",n-1,str,dw,*dp);
		dp++;
		dw += strlen(str)+1;
	}
	fclose(fp);
	return pdict;
};

// Возвращает номер слова str в массиве указателей на начало слов ap,
// с количеством слов words. Если слова нет возвращает -1
int dict_word(char **dp, int nwords, char* str) {
	int l=0, r=nwords, m;
	while (l<r-1) {
		m = (r+l)/2;
		if(strcmp(str, dp[m])<0)
			r=m;
		else
			l=m;
	}
	if (!strcmp(str, dp[l])) return l;
	if (!strcmp(str, dp[r])) return r;
	return -1;
};