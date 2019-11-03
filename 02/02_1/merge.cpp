/*
3_3. Количество инверсий.
Дана последовательность целых чисел из диапазона (-10^9 .. 10^9).
Длина последовательности не больше 10^6. Числа записаны по одному в строке. Количество чисел не указано.
Пусть количество элементов n, и числа записаны в массиве a = a[i]: i из [0..n-1].
Требуется напечатать количество таких пар индексов (i,j) из [0..n-1], что (i < j и a[i] > a[j]).
Указание: количество инверсий может быть больше 4*10^9 - используйте int64_t.
 */

#include <vector>
#include <iostream>

std::vector<int> merge_with_inv_count(const std::vector<int> vec1, const std::vector<int> vec2, int &inv_num)
{
    int vec1_num = 0, vec2_num = 0;
    int res_vec_num = 0;
    std::vector<int> res_vec = std::vector<int>(vec1.size() + vec2.size());

    while (vec1_num < vec1.size() and vec2_num < vec2.size())
    {
        if (vec1[vec1_num] <= vec2[vec2_num])
        {
            res_vec[res_vec_num] = vec1[vec1_num];
            res_vec_num++;
            vec1_num++;
        }
        else
        {
            res_vec[res_vec_num] = vec2[vec2_num];
            inv_num += vec1.size() - vec1_num;
            res_vec_num++;
            vec2_num++;
        }
    }
    while (vec1_num < vec1.size()) {
        res_vec[res_vec_num] = vec1[vec1_num];
        res_vec_num++;
        vec1_num++;
    }
    while (vec2_num < vec2.size()) {
        res_vec[res_vec_num] = vec2[vec2_num];
        inv_num += vec1.size() - vec1_num;
        res_vec_num++;
        vec2_num++;
    }
    return res_vec;
}


int main()
{
    std::vector input_vec;
    std::string line;
    int value = 0;
    while (std::getline(std::cin, line) and !line.empty()) {
        value = std::stoi(line);

    }
    std::cout << "bye";
    return 0;
}
