//---------------------------------------------------------------------------
#pragma hdrstop

#include <windows.h>
#include <conio.h>
#include <iostream>
#include <math.h>
#include <string.h>

using namespace std;
//---------------------------------------------------------------------------
// Структура для хранения одного элемента списка
// num - число
// next - указатель на следующий элемент списка
struct Elem {
    int num;
    Elem *next;
};

const int m = 11; // Размер хеш-таблицы
Elem *table[m]; // Хеш-таблица для метода прямого связывания
const int n = 30; // Размер массива чисел
int a[n]; // Массив чисел

// Вычисляет хеш-функцию
int HashF(int num) {
    return num % m;
}

// Создает элемент списка в динамической памяти
Elem *NewElem(int num) {
    Elem *p = new Elem;
    p->num = num;
    p->next = NULL;
    return p;
}

// Создает хеш-таблицу
void CreateTable() {
    int i;
    for (i = 0; i < m; i++) // Обнуляем хеш-таблицу
        table[i] = NULL;
    for (i = 0; i < n; i++) {
        int hashF = HashF(a[i]); // Вычисляем хеш-функцию
        if (table[hashF] == NULL) // Если поле таблицы пустое
            table[hashF] = NewElem(a[i]); // Заполняем это поле ссылкой на первый элемент списка
        else {
            Elem *p = table[hashF]; // Указатель на текущий элемент списка
            int found = 0; // Будет равна 1, если число есть в списке
            if (p->num == a[i]) // Сравниваем числа
                found = 1;
            while (!found && p->next != NULL) // Проходим по всему списку
                if (p->next->num == a[i])
                    found = 1;
                else
                    p = p->next;
            if (!found) // Если число не найдено - вставляем его в конец списка
                p->next = NewElem(a[i]);
        }
    }
}

// Выводит хеш-таблицу на экран
void ShowTable() {
    printf("\nThe hash table constructed by the method of direct linking:\n\n");
    int i;
    for (i = 0; i < m; i++) {
        cout << i << ":";
        Elem *p = table[i]; // Указатель на текущий элемент списка
        while (p != NULL) {
            cout << " -> " << p->num;
            p = p->next;
        }
        cout << endl;
    }
}

// Ищет число в хеш-таблице
bool Search(int num) {
    int hashF = HashF(num); // Вычисляем хеш-функцию
    Elem *p = table[hashF]; // Указатель на текущий элемент списка
    while (p != NULL) {
        if (p->num == num)
            return true;
        p = p->next;
    }
    return false;
}

#pragma argsused

int main(int argc, char *argv[]) {
    rand();
    int i;
    for (i = 0; i < n; i++) // Заполняем массив чисел
        a[i] = rand() % 30;
    CreateTable();
    ShowTable();
    int num;
    printf("\nEnter a number to search: \n");
    cin >> num;
    if (Search(num))
        printf("\nThe number of found\n");
    else
        printf("\nThe number is not found\n");
    system("PAUSE");
    return 0;
}
//---------------------------------------------------------------------------
 