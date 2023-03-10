
/**
@mainpage Вариант 1:
*/

/**
 * @file main.c
 * @author Вольняга Максим ИУ7-26Б
 * @brief
 * @version 0.1
 * @date 2022-05-20
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>

#define STR_LEN 256
#define WORD_LEN 16

#define LINE_READ_ERROR 100
#define WORD_LEN_ERROR 101
#define FILE_NAME_ERROR 103
#define LONG_LINE_ERROR 104
#define LONG_FILE_ERROR 105

typedef char str_t[STR_LEN + 1];
typedef char word_t[WORD_LEN + 1];

/**
@function my_split
@brief разделение строки на слова
@param[in] arr – массив
@param[in] n – размер
@param[in] str – строка
@param[in] seps – разделитель
@return Код ошибки
*/

int my_split(word_t *arr, size_t *n, str_t str, char *seps)
{
    size_t *new_len = n;

    char *pch = strtok(str, seps);
    while (pch != NULL)
    {
        strncpy(arr[*new_len], pch, WORD_LEN);
        if (arr[*new_len][WORD_LEN - 1] != '\0')
            return EXIT_FAILURE;
        (*new_len)++;
        pch = strtok(NULL, seps);
    }

    return EXIT_SUCCESS;
}


/**
@function swap_words
@brief перестановка слов
@param[in] arr – массив
@param[in] i – размер слова
@param[in] j – размер слова второго
*/

void swap_words(word_t *arr, size_t i, size_t j)
{
    word_t temp;

    strncpy(temp, arr[i], WORD_LEN);
    strncpy(arr[i], arr[j], WORD_LEN);
    strncpy(arr[j], temp, WORD_LEN);
}

/**
@function sort_words_in_arr
@brief сортировка в массиве слов
@param[in] arr – массив
@param[in] i – размер слова
@param[in] j – размер слова второго
*/

void sort_words_in_arr(word_t *arr, size_t len)
{
    for (size_t i = 0; i < len - 1; i++)
        for (size_t j = 0; j < len - 1 - i; j++)
            if (strncmp(arr[j], arr[j + 1], WORD_LEN) > 0)
                swap_words(arr, j, j + 1);
}

/**
@function main
@brief точка входа в программу
@param[out] rc - Код ошибки
@return Код ошибки
*/

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("example.exe <source file> <destination file>\n");

        return -1;
    }

    str_t s = {'\0'};

    FILE *src = fopen(argv[1], "r");
    FILE *dest = fopen(argv[2], "w");

    if (src == NULL)
    {
        printf("File doesn't exist\n");
        fclose(dest);
        return FILE_NAME_ERROR;
    }

    if (dest == NULL)
    {
        printf("File doesn't exist\n");
        fclose(src);
        return FILE_NAME_ERROR;
    }

    while (fgets(s, STR_LEN + 1, src) != NULL)
    {
        word_t words[STR_LEN / 2 + 1];
        size_t len = 0;

        if (s[STR_LEN - 1] != '\0')
        {
            printf("Wrong line entered!\n");
            return LINE_READ_ERROR;
        }

        if (my_split(words, &len, s, " \n"))
        {
            printf("Wrong words in line!\n");
            return WORD_LEN_ERROR;
        }

        sort_words_in_arr(words, len);

        for (size_t i = 0; i < len; i++)
        {
            fputs(words[i], dest);
            putc(' ', dest);
        }
        putc('\n', dest);
    }

    fclose(dest);
    fclose(src);

    return EXIT_SUCCESS;
}