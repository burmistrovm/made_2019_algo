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


void merge_with_inv_count(std::vector<int> &vec, int begin1,
                                       int begin2, int end2, int64_t &inv_num)
{
    int vec1_num = begin1, vec2_num = begin2;
    int res_vec_num = 0;
    int end1 = begin2 - 1;
    int vec1_size = begin1 - end1 + 1;
    int vec2_size = end2 - begin2 + 1;
    std::vector<int> res_vec = std::vector<int>(vec1_size + vec2_size);

    while (vec1_num <= end1 and vec2_num <= end2)
    {
        if (vec[vec1_num] <= vec[vec2_num])
        {
            res_vec[res_vec_num] = vec[vec1_num];
            res_vec_num++;
            vec1_num++;
        }
        else
        {
            res_vec[res_vec_num] = vec[vec2_num];
            inv_num += end1 - vec1_num + 1;
            res_vec_num++;
            vec2_num++;
        }
    }
    while (vec1_num <= end1) {
        res_vec[res_vec_num] = vec[vec1_num];
        res_vec_num++;
        vec1_num++;
    }
    while (vec2_num <= end2) {
        res_vec[res_vec_num] = vec[vec2_num];
        inv_num += end1 - vec1_num + 1;
        res_vec_num++;
        vec2_num++;
    }
    std::copy(res_vec.begin(), res_vec.end(), vec.begin() + begin1);
}

void merge_sort(std::vector<int> &vec, int begin, int end, int64_t &inv_num) {
    // std::vector<int> left;
    // std::vector<int> right;
    if (end - begin > 0)
    {
        int center = int((begin + end) / 2);
        merge_sort(vec, begin, center, inv_num);
        merge_sort(vec, center + 1, end, inv_num);
        merge_with_inv_count(vec,  begin, center + 1, end, inv_num);
    }
}

int main()
{
    std::string line;
    int value = 0;
    std::vector<int> vec = std::vector<int>();
    while (std::getline(std::cin, line) and !line.empty()) {
        value = std::stoi(line);
        vec.push_back(value);
    }

    int64_t inv_num = 0;
    merge_sort(vec, 0, vec.size() - 1, inv_num);

    std::cout << inv_num;
    return 0;
}