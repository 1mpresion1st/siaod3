#include <iostream>
#include <string>
#include <sstream>
#include <vector>
using namespace std;


int main()
{
    setlocale(0, "");
    string sentence;
    cout << "Введите предложение: ";
    getline(cin, sentence); //Считывание введённого предложения

    // Используем stringstream для разделения предложения на слова
    istringstream iss(sentence); //Создание istringstream с именем iss, который используется для разделения предложения на отдельные слова
    string word; //string word будет использоваться для временного хранения слов
    vector<string> words; //vector<string> words - для хранения всех слов из предложения.

    while (iss >> word) //разделяет предложение на отдельные слова
    {
        words.push_back(word); //Каждое слово считывается из iss и добавляется в вектор words
    }

    if (!words.empty())
    {
        // Первое слово в предложении
        string firstWord = words[0]; //Сохранение первого слова из вектора в переменной firstWord.

        int count = 0; //счётчик количества встречь слова

        // Считаем, сколько раз первое слово встречается в предложении
        for (const string& w : words)
        {
            if (w == firstWord)
            {
                count++;
            }
        }

        cout << "Первое слово \"" << firstWord << "\" встречается " << count << " раз." << endl;
    }
    else
    {
        cout << "Пустое предложение." << endl;
    }
    return 0;
}
