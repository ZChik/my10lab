#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h> 
#define MAXLEN 1000 // максимальная длина строки
#define NLINES 1000  // максимальное число строк 
void out_interface(char**, int);
void main(void)
{
	FILE *fp;//входной файл
	int nlines = 0;//число строк в файле
	char **lines_ptr = NULL;  // указатель на динамический массив
	int npointers;    // число указателей в динамическом массиве
	int i;
	fp = fopen("test.txt", "rt"); // открыть файл для чтения
	if (fp == NULL)
		return;    // ошибка при открытии файла
	lines_ptr = (char**)calloc(NLINES, sizeof(char*)); //заказать динамический массив указателей
	for (i = 0; i < NLINES; i++)
	{
		lines_ptr[i] = (char*)calloc(MAXLEN, sizeof(char));
	}
	npointers = NLINES;
	while (!feof(fp))
	{
		char line[MAXLEN];
		char *ptr = fgets(line, MAXLEN, fp); // чтение строки 
		int len;
		if (ptr == NULL)
			break; // файл исчерпан 
		if (nlines == npointers)
		{
			// динамический массив исчерпан  
			npointers += NLINES;// увеличить число указателей в массиве 
								// перезаказать память для массива указателей     
			lines_ptr = (char**)realloc(npointers, sizeof(char*));
			for (i = NLINES; i < npointers; i++)
			{
				lines_ptr[i] = (char*)calloc(MAXLEN, sizeof(char));
			}
			// обнулить новую часть массива указателей
			memset(&lines_ptr[nlines], 0, MAXLEN * sizeof(char*));
		}     
		strcpy(lines_ptr[nlines], line); // сохраняем строку в динамическом массиве
		nlines++;
	}
	fclose(fp);
	out_interface(lines_ptr, npointers);
	if (lines_ptr != NULL)
	{
		for (i = 0; i < npointers; i++)
		{
			free(lines_ptr[i]);
		}
		free(lines_ptr);
	}
	getchar();
	system("pause");
}
void out_interface(char **lines, int n)
{
	int i;
	char *ptr;
	char line[100];
	for (i = 0; i < n; i++)
	{
		ptr = lines[i];
		if (strstr(lines[i], ")") && !strstr(lines[i], ");") && !strstr(lines[i], ";") && !strstr(lines[i], "for")
			&& !strstr(lines[i], "while") && !strstr(lines[i], "if") && !strstr(lines[i], "switch"))
		{
			int g = 0;
			int counter = 0;
			while (*ptr)
			{
				if (*ptr == '(')
				{
					counter++;
					line[g++] = *ptr++;
				}
				else if (*ptr == ')')
				{
					counter--;
					line[g++] = *ptr++;
					if (counter == 0) {
						line[g] = '\0';
						break;
					}
				}
				else line[g++] = *ptr++;
			}
			line[g] = '\0';
			printf("%s\n", line);
		}
	}
}