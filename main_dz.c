/**
@mainpage Вариант 6:
В текстовом файле содержатся целые числа.
Найти сумму цифр каждого числа и если она четная, то перевести его в двоичную систему счисления,
а если нечетная,то преобразовать число в обратном порядке следования цифр. Результат вывести на экран.
*/

/**
 * @file main.c
 * @author Вольняга Максим ИУ7-26Б
 * @brief
 * @version 0.1
 * @date 2022-05-13
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define N_ARR 1024

#define CODE_PASS 0
#define ERR_OPEN 1
#define ERR_NOT_NUM 2
#define ERR_RANGE_NUM 3
#define ERR_MORE100 3
#define ERR_EMPTY 3

/**
@function check_file
@brief Проверка фала
@param[in] file_name – Файловая переменная
@param[out] rc - Код ошибки
@return Код ошибки
*/

int check_file(char file_name[])
{
    int rc = CODE_PASS;
    FILE *input = fopen(file_name, "r");
    fseek(input, 0, SEEK_END);
    long pos = ftell(input);
    if (input == 0)
        rc = ERR_OPEN;

    else if (pos == 0)
        rc = ERR_EMPTY;

    return rc;
}

/**
@function read_num
@brief Считываем в массив чисела, расположенные в файле
@param[in] file_name – Файловая переменная
@param[in] arr - массив
@param[in] rc - Код ошибки
@param[out] i - Количество элементов вмассиве
@return Количество элементов в массиве
*/

int read_num(char file_name[], int *arr, int *rc)
{
    int i = 0;

    FILE *input = fopen(file_name, "r");
    fseek(input, 0, SEEK_SET);

    while (1)
    {
        int num;
        if (i > 100)
        {
            i = 0;
            *rc = ERR_MORE100;
            break;
        }
        else if (fscanf(input, "%d", &num) == 1)
            arr[i] = num;
        else
        {
            *rc = ERR_NOT_NUM;
            break;
        }
        i++;
        if (feof(input))
            break;
    }
    fclose(input);

    return i;
}

/**
 * \fn int test_read_num(int rc)
 * \brief Модульный тест для функции \link read_num
 * \param[in] rc - код ошибки
 * \return Количество проваленных тестов
 */
int test_read_num(int rc)
{
    int err_count = 0;

    // Пустой файл
    char file_name_1[] = "test_read_num_1.txt";
    int arr_1[N_ARR] = {0};
    err_count += read_num(file_name_1, arr_1, &rc) == 0 ? 0 : 1;

    // одно число
    char file_name_2[] = "test_read_num_2.txt";
    int arr_2[N_ARR] = {0};
    err_count += read_num(file_name_2, arr_2, &rc) == 1 ? 0 : 1;

    // 4 чисела
    char file_name_3[] = "test_read_num_3.txt";
    int arr_3[N_ARR] = {0};
    err_count += read_num(file_name_3, arr_3, &rc) == 4 ? 0 : 1;

    // больше 100 чисел
    char file_name_4[] = "test_read_num_4.txt";
    int arr_4[N_ARR] = {0};
    err_count += read_num(file_name_4, arr_4, &rc) == 0 ? 0 : 1;

    return err_count;
}

/**
@function sum_num
@brief Суммирует все цифры в числе
@param[in] num – Число
@param[out] sum_num - Сумма цифр числа
@return Сумма цифр числа
*/

int sum_num(int num)
{
    int sum_num = 0;
    if (num < 0)
        num = -num;
    while (num != 0)
    {
        sum_num += num % 10;
        num = num / 10;
    }
    return sum_num;
}

/**
 * \fn int test_sum_num()
 * \brief Модульный тест для функции \link sum_num
 *
 * \return Количество проваленных тестов
 */
int test_sum_num()
{
    int err_count = 0;

    // Неположительные числа
    err_count += sum_num(-100) == 1 ? 0 : 1;
    err_count += sum_num(-123) == 6 ? 0 : 1;

    // Нуль
    err_count += sum_num(0) == 0 ? 0 : 1;

    // Положительные числа
    err_count += sum_num(12) == 3 ? 0 : 1;
    err_count += sum_num(4) == 4 ? 0 : 1;
    err_count += sum_num(105) == 6 ? 0 : 1;

    return err_count;
}

/**
@function dec_to_bin
@brief Переводит число из 10-ой с/с в 2-ую с/с
@param[in,out]] str – строка, в которую будет записано двоичное представление числа а
@param[in] a - Число для перевода
@return Строка, в которой записано двоичное представление числа а
*/

char *dec_to_bin(char *str, int a)
{
    int flag_neg_num = 0;
    if (a < 0)
    {
        a = -a;
        flag_neg_num = 1;
    }

    int i = 32;
    while (a != 0)
    {
        if (a % 2 == 0)
        {
            *(str + i) = '0';
            a = a / 2;
        }
        else
        {
            *(str + i) = '1';
            a = a / 2;
        }
        i--;
    }
    i = i + 1;

    if (flag_neg_num == 1)
    {
        *str = '1';
    }
    *(str + 33) = '\0';
    return str;
}

/**
 * \fn int test_dec_to_bin()
 * \brief Модульный тест для функции \link dec_to_bin
 *
 * \return Количество проваленных тестов
 */
int test_dec_to_bin()
{
    int err_count = 0;
    char b[33] = "00000000000000000000000000000000";

    // Неположительные числа
    err_count += strcmp(dec_to_bin(b, -2), "100000000000000000000000000000010") == 0 ? 0 : 1;
    char b1[33] = "00000000000000000000000000000000";
    err_count += strcmp(dec_to_bin(b1, -400), "100000000000000000000000110010000") == 0 ? 0 : 1;

    // Нуль
    char b2[33] = "00000000000000000000000000000000";
    err_count += strcmp(dec_to_bin(b2, 0), "00000000000000000000000000000000") == 0 ? 0 : 1;

    // Положительные числа
    char b3[33] = "00000000000000000000000000000000";
    err_count += strcmp(dec_to_bin(b3, 2), "000000000000000000000000000000010") == 0 ? 0 : 1;
    char b4[33] = "00000000000000000000000000000000";
    err_count += strcmp(dec_to_bin(b4, 400), "000000000000000000000000110010000") == 0 ? 0 : 1;

    return err_count;
}

/**
@function upend_num
@brief Переворачивает число
@param[in] num – Число
@param[out] rev - Перевернутое число
@return Перевернутое число
*/

int upend_num(int num)
{
    int rev = 0, remainder;
    while (num != 0)
    {
        remainder = num % 10;
        rev = rev * 10 + remainder;
        num /= 10;
    }
    return rev;
}

/**
 * \fn int test_upend_num()
 * \brief Модульный тест для функции \link upend_num
 *
 * \return Количество проваленных тестов
 */

int test_upend_num()
{
    int err_count = 0;

    // Неположительные числа
    err_count += upend_num(-14) == -41 ? 0 : 1;
    err_count += upend_num(-1) == -1 ? 0 : 1;

    // Нуль
    err_count += upend_num(0) == 0 ? 0 : 1;

    // Положительные числа
    err_count += upend_num(1) == 1 ? 0 : 1;
    err_count += upend_num(3) == 3 ? 0 : 1;
    err_count += upend_num(14) == 41 ? 0 : 1;

    return err_count;
}

/**
@function main
@brief Точка входа в программу
@param[out] rc - Код ошибки
@return Код ошибки
*/

int main(void)
{
    int test_rs = 0;
    assert(test_sum_num() == 0);
    assert(test_dec_to_bin() == 0);
    assert(test_upend_num() == 0);
    assert(test_read_num(test_rs) == 0);

    int rc = CODE_PASS;
    int new_n = 0;
    char file_name[] = "/home/max/lab_opi/dz/func_tests/data/in.txt";
    int arr[N_ARR] = {0};

    rc = check_file(file_name);
    if (rc == ERR_OPEN)
    {
        printf("ERROR OPEN FILE\n");
        exit(rc);
    }

    else if (rc == ERR_EMPTY)
    {
        printf("ERROR OPEN IS EMPTY\n");
        exit(rc);
    }

    new_n = read_num(file_name, arr, &rc);

    if (rc == ERR_MORE100)
    {
        printf("FILE HAS MORE 100 NUMBERS\n");
        exit(rc);
    }
    else if (rc == ERR_NOT_NUM)
    {
        printf("FFILE HAS INVALID NUMBERS VALUES\n");
        exit(rc);
    }
    else
    {
        for (int i = 0; i < new_n; i++)
        {
            char b[33] = "00000000000000000000000000000000";
            char *p = b;
            if (sum_num(arr[i]) % 2 == 0)

                printf("bin: %s\n", dec_to_bin(p, arr[i]));
            else
                printf("upend: %d\n", upend_num(arr[i]));
        }
    }

    return rc;
}
