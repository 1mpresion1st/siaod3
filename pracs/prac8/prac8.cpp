#include <iostream>
#include <vector>
using namespace std;

/*Функция для решения задачи с помощью динамического программирования
Она принимает векторы `weights` и `values`, вместимость `capacity`, а также вектор `selected_items` для отслеживания выбранных вещей */
int knapsack(vector<int>& weights, vector<int>& values, int capacity, vector<int>& selected_items)
{
    int n = weights.size();
    // Определение переменной `n` как размер вектора `weights`, то есть количество вещей.

    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));
    // Создание двумерного вектора `dp`, где строки представляют вещи, столбцы представляют вместимость
    // Все значения инициализируются нулями

    for (int i = 1; i <= n; i++) // Цикл по вещам (i) от первой до последней
    {
        for (int w = 0; w <= capacity; w++) // Вложенный цикл по вместимости рюкзака (w) от 0 до указанной вместимости
        {
            if (weights[i - 1] > w)  // Проверка, если вес текущей вещи больше, чем вместимость рюкзака
            {
                dp[i][w] = dp[i - 1][w];  // Текущее значение в матрице `dp` равно предыдущему значению в той же строке
            }
            else
            {
                dp[i][w] = max(dp[i - 1][w], dp[i - 1][w - weights[i - 1]] + values[i - 1]);
                // В противном случае, выбирается максимум из двух вариантов:
                // 1. Не включать текущую вещь (предыдущее значение в той же строке)
                // 2. Включить текущую вещь и добавить ее стоимость к стоимости, которая помещается в оставшейся вместимости
            }
        }
    }

    // Отслеживаем выбранные вещи
    int i = n;
    int w = capacity;
    while (i > 0 && w > 0) // Цикл для отслеживания выбранных вещей, начиная снизу в правом верхнем углу матрицы
    {
        if (dp[i][w] != dp[i - 1][w])  // Если значение изменилось (текущая вещь включена в рюкзак), то добавляем номер текущей вещи в вектор выбранных вещей
        {
            selected_items.push_back(i);
            w -= weights[i - 1];  // Уменьшаем вместимость рюкзака на вес текущей вещи
        }
        i--;
    }
    return dp[n][capacity];
}

int main()
{
    setlocale(0, "");

    // Задаем векторы с весами и стоимостями вещей.
    vector<int> weights = { 2, 3, 1 };
    vector<int> values = { 60000, 5000, 20000 };

    int capacity = 5; // Вместимость рюкзака в кг

    // Создаем вектор с названиями вещей
    vector<string> item_names = { "Ноутбук", "Спальный мешок", "Фляга с водой" };

    cout << "У вас имеется рюкзак вместимостью " << capacity << " кг и следующий набор вещей:" << endl;
    for (int i = 0; i < weights.size(); i++)
    {
        cout << i + 1 << " - " << item_names[i] << ", Вес - " << weights[i] << " кг, Цена - " << values[i] << " руб." << endl;
    }

    vector<int> selected_items;
    int max_value = knapsack(weights, values, capacity, selected_items);

    cout << "Максимальная стоимость: " << max_value << " руб." << endl << endl;
    cout << "Выбранные вещи:" << endl;
    for (int i = selected_items.size() - 1; i >= 0; i--)
    {
        int item_idx = selected_items[i] - 1;
        cout << item_names[item_idx] << " - Вес: " << weights[item_idx] << " кг, Стоимость: " << values[item_idx] << " руб." << endl;
    }
    return 0;
}
