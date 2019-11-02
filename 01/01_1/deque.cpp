//
// Created by mike on 20.10.19.
//

#include <iostream>
#include <vector>

template<typename T>
class Deque
{
public:
    Deque();
    void push_back(T value);
    void push_front(T value);
    T pop_back();
    T pop_front();
private:
    std::vector<T> container;
    int size;
    int tail;
    int head;

    void resize();
};

template<typename T>
Deque<T>::Deque()
{
    container = std::vector<T>(10);
    size = 0;
    tail = 0;
    head = 0;
}

template<typename T>
void Deque<T>::push_back(T value)
{
    if (container.size() == size)
    {
        resize();
    }
    tail++;
    if (tail  == container.size()){
        tail = 0;
    }
    container[tail] = value;
    size++;
}

template<typename T>
void Deque<T>::push_front(T value)
{
    if (container.size() == size)
    {
        resize();
    }
    container[head] = value;
    size++;
    head--;
    if (head == -1){
        head = container.size() - 1;
    }
}

template<typename T>
T Deque<T>::pop_back()
{
    if (size == 0)
    {
        return -1;
    }
    T res = container[tail];
    size--;
    tail--;
    if (tail  == -1){
        tail = container.size() - 1;
    }
    return res;
}

template<typename T>
T Deque<T>::pop_front()
{
    if (size == 0)
    {
        return -1;
    }
    if (head == container.size() - 1)
    {
        head = -1;
    }
    head++;
    T res = container[head];
    size--;
    return res;
}

template<typename T>
void Deque<T>::resize()
{
    std::size_t vec_size = container.size();
    std::vector<T> new_cont = std::vector<T>(vec_size * 2);

    std::size_t new_cont_pos = 0;
    std::size_t old_cont_pos;

    if (head != container.size() - 1)
    {
        old_cont_pos = head + 1;
    }
    else
    {
        old_cont_pos = 0;
    }

    std::size_t new_head = 0;
    int target = size;
    // если конец дека слева от начала
    // то сначала доходим от головы до конца буфера
    // а затем от начала буфера до хвоста
    // иначе просто доходим от головы до хвоста
    if (old_cont_pos > tail)
    {
        while (old_cont_pos <= size - 1)
        {
            new_cont[new_cont_pos] = container[old_cont_pos];
            new_cont_pos++;
            old_cont_pos++;
        }
    }
    else
    {
        while (old_cont_pos <= tail)
        {
            new_cont[new_cont_pos] = container[old_cont_pos];
            new_cont_pos++;
            old_cont_pos++;
        }
    }
    old_cont_pos--;

    if (old_cont_pos != tail) {
        old_cont_pos = 0;
        while (old_cont_pos <= tail)
        {
            new_cont[new_cont_pos] = container[old_cont_pos];
            new_cont_pos++;
            old_cont_pos ++;
        }
    }
    container = new_cont;
    head = container.size() - 1;
    tail = new_cont_pos - 1;
}

int main() {
    int commands_count = 0;
    Deque<int> deque = Deque<int>();

    std::cin >> commands_count;
    for (int i = 0; i < commands_count; ++i)
    {
        int command = 0;
        int value = 0;
        std::cin >> command >> value;
        if (command == 1)
        {
            deque.push_front(value);
        }
        else if (command == 2)
        {
            int new_val = deque.pop_front();
            if (new_val != value)
            {
                std::cout << "NO";
                return 0;
            }
        }
        else if (command == 3)
        {
            deque.push_back(value);
        }
        else if (command == 4)
        {
            int new_val = deque.pop_back();
            if (new_val != value) {
                std::cout << "NO";
                return 0;
            }
        }
    }
    std::cout << "YES";
    return 0;
}