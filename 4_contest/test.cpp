#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0)); // Инициализация генератора случайных чисел

    int q = 300000; // Максимальное количество запросов
    std::cout << q << std::endl;

    std::vector<int> inserted_numbers; // Для хранения вставленных чисел
    int last_answer = 0; // Для хранения последнего ответа на запрос lower_bound

    for (int i = 0; i < q; ++i) {
        // Генерируем случайное число для запроса
        int operation_type = std::rand() % 2; // 0 для insert, 1 для lower_bound
        int x = std::rand() % 1000000000 + 1; // Случайное число от 1 до 10^9

        if (operation_type == 0) { // Запрос на вставку
            if (inserted_numbers.empty() || (i > 0 && (i % 1000 == 0))) {
                // Если это первый запрос или каждые 1000 запросов, вставляем x
                std::cout << "+ " << x << std::endl;
                inserted_numbers.push_back(x);
            } else {
                // В противном случае, вставляем (x + last_answer) % 10^9
                std::cout << "+ " << (x + last_answer) % 1000000000 << std::endl;
            }
        } else { // Запрос на lower_bound
            std::cout << "? " << x << std::endl;
            // Здесь можно добавить логику для обновления last_answer, если это необходимо
            // Например, если вы хотите, чтобы last_answer был равен x, вы можете сделать:
            last_answer = x; // Это просто пример, вы можете изменить логику по своему усмотрению
        }
    }

    return 0;
}
