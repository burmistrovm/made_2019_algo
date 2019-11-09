/*
 * 4_2. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */
#include <vector>
#include <iostream>
#include <sstream>

int find_pivot(std::vector<int> cont,
               int left_num, int right_num)
{
    int middle = int((left_num + right_num) / 2);
    if (left_num > right_num)
    {
        if (right_num > middle) {
            return right_num;
        }
        else
        {
            return middle;
        }
    }
    else
    {
        if (left_num > middle) {
            return left_num;
        }
        else
        {
            return middle;
        }
    }
}

void partition(std::vector<int> &cont,
              int left_num, int right_num,
              int &pivot_num)
{
    std::swap(cont[right_num], cont[pivot_num]);
    pivot_num = right_num;

    int i = right_num, j = right_num;
    while (j >= left_num)
    {
        if (cont[j] > cont[pivot_num]) {
            i--;
            std::swap(cont[i], cont[j]);
            j--;
        }
        else {
            j--;
        }
    }
    std::swap(cont[i], cont[pivot_num]);
    pivot_num = i;
}

int get_order_stat(std::vector<int> vec, int ord_stat)
{
    int left_num = 0, right_num = vec.size() - 1;
    int pivot_num = find_pivot(vec, right_num, left_num);
    partition(vec, left_num, right_num, pivot_num);
    while (pivot_num != ord_stat)
    {
        if (pivot_num < ord_stat)
        {
            left_num = pivot_num + 1;
        }
        else if (pivot_num > ord_stat)
        {
            right_num = pivot_num - 1;
        }
        pivot_num = find_pivot(vec, right_num, left_num);
        partition(vec, left_num, right_num, pivot_num);
    }
    return vec[pivot_num];
}

int main()
{
    int dim, ord_stat;
    std::cin >> dim >> ord_stat;
    std::cin.ignore();

    std::vector<int> vec = std::vector<int>(dim);
    for (int i = 0; i < dim; ++i)
    {
        std::cin >> vec[i];
    }
    std::cout << get_order_stat(vec, ord_stat);
    return 0;
}
