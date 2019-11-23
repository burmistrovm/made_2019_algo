/*
 * Реализуйте структуру данных типа “множество строк” на основе динамической хеш-таблицы с открытой адресацией.
 * Хранимые строки непустые и состоят из строчных латинских букв.
 * Хеш-функция строки должна быть реализована с помощью вычисления значения многочлена методом Горнера.
 * Начальный размер таблицы должен быть равным 8-ми. Перехеширование выполняйте при добавлении элементов в случае,
 * когда коэффициент заполнения таблицы достигает 3/4.
 * Структура данных должна поддерживать операции добавления строки в множество, удаления строки из множества и проверки принадлежности данной строки множеству.
 * 1_1. Для разрешения коллизий используйте квадратичное пробирование. i-ая проба
 * g(k, i)=g(k, i-1) + i (mod m). m - степень двойки.
*/

#include <iostream>
#include <vector>

struct Hash_Table_Elem
{
    Hash_Table_Elem(std::string _key): key(_key), is_deleted(false) {};
    std::string key;
    bool is_deleted;
};


int get_hash(const std::string &key, const int& m)
{
    int hash = 0;
    for(int i = 0; key[i] != 0; ++i)
    {
        hash = (hash * 19 + key[i]) % m;
    }
    std::cout << hash;
    return hash;
}


class Hash_Table
{
public:
    Hash_Table(): size(0), container(std::vector<Hash_Table_Elem*>(8)){};
    bool add(Hash_Table_Elem* new_elem);
    bool remove(const std::string &key);
    bool has(const std::string &key);
private:
    int size = 0;
    std::vector<Hash_Table_Elem*> container;
    void rehash();
};


void Hash_Table::rehash()
{
    std::vector<Hash_Table_Elem*> old_cont = container;
    container = std::vector<Hash_Table_Elem*>(old_cont.size() * 2);
    size = 0;
    for (int i = 0; i < old_cont.size(); i++)
    {
        if ((old_cont[i] != NULL) and (!old_cont[i]->is_deleted))
        {
            add(old_cont[i]);
        }
    }
}


bool Hash_Table::add(Hash_Table_Elem* new_elem)
{
    if ((1.0 * size / container.size()) >= (3.0 / 4.0))
    {
        rehash();
    }
    int hash = get_hash(new_elem->key, container.size());
    int probe_num = 0;
    // если элемент присутствует, то вставить его нельзя
    if (has(new_elem->key))
    {
        return false;
    }
    // иначе ищем позицию для вставки
    while ((container[hash] != NULL) and (!container[hash]->is_deleted)
           and (container[hash]->key != new_elem->key))
    {
        hash = (hash + probe_num) % container.size();
        probe_num++;
    }
    if (container[hash] == NULL)
    {
        container[hash] = new_elem;
        size++;
        return true;
    }
    else if (container[hash]->is_deleted)
    {
        container[hash] = new_elem;
        size++;
        return true;
    }
    return false;
}

bool Hash_Table::remove(const std::string &key)
{
    int hash = get_hash(key, container.size());
    int probe_num = 0;

    while ((container[hash] != NULL) and (probe_num < container.size())
           and (container[hash]->key != key))
    {
        hash = (hash + probe_num) % container.size();
        probe_num++;
    }
    if (container[hash] == NULL)
    {
        return false;
    }
    else if (container[hash]->key == key and (!container[hash]->is_deleted))
    {
        container[hash]->is_deleted = true;
        --size;
        return true;
    }
    return false;
}

bool Hash_Table::has(const std::string &key)
{
    int hash = get_hash(key, container.size());
    int probe_num = 0;

    while ((container[hash] != NULL) and (container[hash]->key != key)
           and (probe_num < container.size()))
    {
        hash = (hash + probe_num) % container.size();
        probe_num++;
    }
    if (container[hash] == NULL)
    {
        return false;
    }
    else if ((container[hash]->key == key) and (!container[hash]->is_deleted))
    {
        return true;
    }
    return false;
}

int main()
{
    Hash_Table hash_table;
    std::string line;

    while (std::getline(std::cin, line) and !line.empty())
    {
        char command;
        std::string key;
        command = line[0];
        key = line.substr(2, line.size() - 2);

        std::string res;
        switch (command)
        {
            case '?':
                if (hash_table.has(key))
                {
                    res = "OK";
                }
                else
                {
                    res = "FAIL";
                }
                break;
            case '+':
                if (hash_table.add(new Hash_Table_Elem(key)))
                {
                    res = "OK";
                }
                else
                {
                    res = "FAIL";
                }
                break;
            case '-':
                if (hash_table.remove(key))
                {
                    res = "OK";
                }
                else
                {
                    res = "FAIL";
                }
                break;
        }
        std::cout << res << std::endl;
    }
    return 0;
}