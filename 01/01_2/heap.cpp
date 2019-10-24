//
// Created by mike on 20.10.19.
//

#include <iostream>
#include <vector>

class Heap
{
public:
    Heap();
    void insert(int value);
    int get_size();
    int get_top();
    int extract_top();
private:
    std::vector<int> container;
    int heap_size = 0;
    void sift_up(int num);
    void sift_down(int num);
    void resize();
};

Heap::Heap()
{
    container = std::vector<int>(1);
}

int Heap::get_size()
{
    return heap_size;
}

int Heap::get_top()
{
    if (heap_size != 0) {
        return container[0];
    }
    else
    {
        return -1;
    }
}

int Heap::extract_top()
{
    int res = container[0];
    container[0] = container[heap_size - 1];
    heap_size--;
    sift_down(0);
    return res;
}

void Heap::insert(int value)
{
    if (heap_size == container.size())
    {
        resize();
    }
    container[heap_size] = value;
    sift_up(heap_size);
    heap_size++;
}

void Heap::sift_up(int num)
{
    // пока родитель меньше текущего элемента
    // поднимаем его наверх
    while((num != 0) && (container[(num - 1) / 2] > container[num]))
    {
        int temp = container[num];
        container[num] = container[(num - 1) / 2];
        container[(num - 1) / 2] = temp;
        num = (num - 1) / 2;
    }
}

void Heap::sift_down(int num)
{
    //пока текущий элемент меньше потомков
    //меняем его с минимумом
    bool stop_flag = false;
    while(2 * num + 1 < heap_size and !stop_flag)
    {
        int left_ch = 2 * num + 1;
        int right_ch = 2 * num + 2;
        int min_ch = left_ch;
        if (right_ch < heap_size & container[left_ch] > container[right_ch])
        {
            min_ch = right_ch;
        }
        if (container[min_ch] < container[num])
        {
            int tmp = container[num];
            container[num] = container[min_ch];
            container[min_ch] = tmp;
            num = min_ch;
        }
        else
        {
            stop_flag = true;
        }
    }
}

void Heap::resize()
{
    std::vector<int> new_cont = std::vector<int>(2 * container.size());
    for (int i = 0; i < container.size(); i++)
    {
        new_cont[i] = container[i];
    }
    container = new_cont;
}

int main() {
    int trains_count = 0;
    int max_ends = 0;
    Heap heap = Heap();
    std::cin >> trains_count;
    for (int i = 0; i < trains_count; ++i)
    {
        int input_time, output_time;
        std::cin >> input_time >> output_time;

        while (heap.get_size() !=0 & input_time > heap.get_top())
        {
            heap.extract_top();
        }

        heap.insert(output_time);
        if (heap.get_size() > max_ends)
        {
            max_ends = heap.get_size();
        }
    }


    std::cout << max_ends;

    return 0;
}