#include <iostream>
#include <string>
#include <cmath>
using namespace std;

const int prime = 101; // Простое число для хеширования

// Функция для вычисления хеша строки
int calculateHash(const string& str, int length) //вычисляет хеш строки str заданной длины length
{
    int hash = 0;
    for (int i = 0; i < length; i++)
    {
        hash += (str[i] * pow(prime, i)); //итерирует по символам строки, вычисляет хеш каждого символа и добавляет их в переменную hash
    }
    return hash;
}

// Функция для обновления хеша при сдвиге
int recalculateHash(int oldHash, char oldChar, char newChar, int length) //обновляет хеш при сдвиге на один символ
{
    int newHash = oldHash - (oldChar * pow(prime, 0));
    newHash = newHash / prime;
    newHash += (newChar * pow(prime, length - 1)); //вычитает старый символ oldChar из текущего хеша oldHash, затем делит
    //результат на prime и добавляет новый символ newChar, умноженный на prime^(length-1), чтобы учесть новый символ
    return newHash;
}

// Функция для поиска подстроки в тексте с использованием алгоритма Рабина-Карпа
void searchRabinKarp(const string& text, const string& pattern) //начинает сравнивать подстроки по очереди
{
    int textLength = text.length();
    int patternLength = pattern.length();
    int patternHash = calculateHash(pattern, patternLength);

    for (int i = 0; i <= textLength - patternLength; i++)
    {
        int textHash = calculateHash(text.substr(i, patternLength), patternLength);
        if (textHash == patternHash) //Если хеши совпадают, выполняется дополнительная проверка на полное совпадение подстроки
        {
            bool match = true;
            for (int j = 0; j < patternLength; j++)
            {
                if (text[i + j] != pattern[j])
                {
                    match = false;
                    break;
                }
            }
            if (match) //Если подстрока найдена, выводится сообщение о позиции начала подстроки и сама подстрока
            {
                cout << "Подстрока найдена с позиции " << i << ". ";
                cout << "Часть, входящая в строку: " << text.substr(i, patternLength) << endl;
                return;
            }
        }
    }

    cout << "Подстрока не найдена в тексте." << endl;
}

int main()
{
    setlocale(0, "");
    string text = "Мы всей группой пошли гулять по городу.";
    string pattern = "мв";

    searchRabinKarp(text, pattern);
    return 0;
}