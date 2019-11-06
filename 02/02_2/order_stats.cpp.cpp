/*
 * 4_2. Реализуйте стратегию выбора опорного элемента “медиана трёх”.
 * Функцию Partition реализуйте методом прохода двумя итераторами от конца массива к началу.
 */
#include <vector>
#include <iostream>

int find_pivot(std::vector<int> cont,
               int left_num, int right_num)
{
    return int((right_num + left_num) / 2);
}

void partition(std::vector<int> &cont,
              int left_num, int right_num,
              int &pivot_num)
{
    int left_side = left_num, right_side = right_num - 1;
    int curr_num = left_side;
    std::swap(cont[right_num], cont[pivot_num]);
    pivot_num = right_num;

    while (left_side != right_side) {
        if (cont[left_side] <= cont[pivot_num]) {
            left_side++;
            curr_num++;
        }
        else
        {
            std::swap(cont[curr_num], cont[right_side]);
            right_side--;
        }
    }
    if (cont[curr_num] < cont[pivot_num])
    {
        curr_num++;
    }
    std::swap(cont[curr_num], cont[pivot_num]);
    pivot_num = curr_num;
}

int get_order_stat(std::vector<int> vec, int ord_stat)
{
    int pivot_num;
    int left_num = 0, right_num = vec.size() - 1;
    bool flag_stop = false;
    while (!flag_stop)
    {
        pivot_num = find_pivot(vec, right_num, left_num);
        partition(vec, left_num, right_num, pivot_num);
        if (pivot_num < ord_stat)
        {
            left_num = pivot_num + 1;
        }
        else if (pivot_num > ord_stat)
        {
            right_num = pivot_num - 1;
        }
        else
        {
            flag_stop = true;
        }
        if (right_num == left_num)
        {
            flag_stop = true;
        }
    }
    return pivot_num;
}

int main()
{
    std::vector<int> v = {6, 5, 4, 3, 2, 1, 7};
    int pivot_num = 2;

    std::cout << get_order_stat(v, 6) << std::endl;
//    for (int i = 0; i < v.size(); ++i) {
//        std::cout << v[i] << std::endl;
//    }
    return 0;
}
