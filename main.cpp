#include <vector>
#include <iostream>
#include <assert.h>
using namespace std;
template <typename T>
struct Node{
    T value;
    Node<T>* next;

    Node(const T &new_value, Node<T>* new_next) {
        next = new_next;
        value = new_value;
    }

    Node(const T &new_value) {
        next = nullptr;
        value = new_value;
    }
};

template <typename T>
class LinkedList {
private:
    Node<T> *first, *last;
    size_t size_of_list = 0;

    void move(Node<T>* &node) const {
        node = node->next;
    }

public:
    LinkedList() {
        first = nullptr;
        last = nullptr;
        size_of_list = 0;
    }

    ~LinkedList() {
        clear();
    }

    LinkedList(const LinkedList& that) : LinkedList() {
        this->copy(that);
    }

    friend void swap(LinkedList&a, LinkedList&b) {
        std::swap(a.first, b.first);
        std::swap(a.last, b.last);
        std::swap(a.size_of_list, b.size_of_list);
    }

    LinkedList&operator=(LinkedList that) {
        swap(*this, that);
        return *this;
    }

    void copy(const LinkedList<T>& old) {
        Node<T> *node = old.first, *current = nullptr;
        while(node != nullptr) {
            this->push_back(node->value);
            move(node);
        }
    }

    // insert new node with 'value' after 'node'
    // it is convenient to consider, that 'first' is 'next' to nullptr
    void insert(const T& value, Node<T>* node) {
        size_of_list++;
        Node<T>* new_node;
        if(node != nullptr)
            new_node = new Node<T>(value, node->next);
        else {
            new_node = new Node<T>(value, first);
            first = new_node;
        }
        if(new_node->next == nullptr)
            last = node;
    }

    void insert(const T&& value, Node<T>* node) {
        insert(value, node);
    }

    // insert new node with 'value' to the end of the LinkedList
    void push_back(const T& value) {
        size_of_list++;
        Node<T>* new_node = new Node<T>(value);
        if(size_of_list == 1) {
            last = new_node;
            first = new_node;
            return;
        }
        last->next = new_node;
        last = new_node;
    }

    void push_back(const T&& value) {
        push_back(value);
    }

    void push_front(const T& value) {
        size_of_list++;
        Node<T>* new_node = new Node<T>(value, first);
        first = new_node;
        if(size_of_list == 1)
            last = new_node;
    }

    void push_front(const T&& value) {
        push_front(value);
    }
    Node<T>* begin() {
        return first;
    }

    Node<T>* end() {
        return last;
    }

    Node<T>* find(const T& value) const {
        Node<T>* node = first;
        while(node != nullptr) {
            if(node->value == value)
                return node;
            move(node);
        }
        return node;
    }

    Node<T>* find(const T&& value) const {
        return find(value);
    }

    bool contains(const T& value) const{
        return find(value) != nullptr;
    }

    bool contains(const T&& value) const {
        return find(value) != nullptr;
    }

    Node<T>* find_by_index(int index) const {
        assert(index < size_of_list);
        Node<T>* node = first;
        for(int i = 0; i < index; i++)
            move(node);
        return node;
    }

    Node<T>* find_previous(const Node<T>* next_node) const {
        Node<T>* node = first;
        while(node != nullptr) {
            if(node->next == next_node)
                return node;
            move(node);
        }
        // node equals nullptr in that case
        return nullptr;
    }

    //to work
    Node<T>* find_previous(const T& value) const {
        if(first == nullptr || first->value == value)
            return nullptr;
        Node<T>* node = first;
        while(node->next != nullptr) {
            if(node->next->value == value)
                return node;
            move(node);
        }
        // last equals node in that case
        return last;
    }

    Node<T>* find_previous(const T&& value) const {
        //calls lvalue function
        return find_previous(value);
    }

    //not fast/ to work with lvalue
    bool erase(const T& value) {
        return erase_next(find_previous(value));
    }
    // to work with rvalue
    bool erase(const T&& value) {
        // calls lvalue function
        return erase_next(find_previous(value));
    }

    // not fast
    bool erase(Node<T>* node_to_delete) {
        return erase_next(find_previous(node_to_delete));
    }

    // fast, returns 'true' if successful
    // it is convenient, to consider, that next to 'nullprt' is 'first'
    bool erase_next(Node<T>* node) {
        if(node == last || size_of_list == 0)
            return false;
        size_of_list--;
        if(node == nullptr) {
            node = first;
            move(node);
            delete first;
            first = node;
            return true;
        }
        Node<T>* node_to_delete = node->next;
        node->next = node_to_delete->next;
        delete node_to_delete;
        if(node->next == nullptr)
            last = node;
        return true;
    }

    size_t size() const {
        return size_of_list;
    }

    vector <T> convert_to_vector() const{
        vector <T> vectored_list(size_of_list);
        Node<T>* node = first;
        for(int i = 0; i < size_of_list; i++) {
            vectored_list[i] = node->value;
            move(node);
        }
        return vectored_list;
    }

    void clear() {
        while(first != nullptr) {
            Node<T>* reference = first->next;
            delete first;
            first = reference;
        }
        last = nullptr;
        size_of_list = 0;
    }

    bool empty() const {
        return size_of_list == 0;
    }


    // функция разворота
    void reverse() {
        Node<T> *previous = nullptr, *node = first;
        while(node != nullptr) {
            Node<T>* reference = node->next;
            node->next = previous;
            previous = node;
            node = reference;
        }
        Node<T>* tmp = first;
        first = last;
        last = tmp;
    }

};

void represent_vector(const vector <int> &vec) {
    for(int i = 0; i < vec.size(); i++)
        cout << vec[i] << " ";
    cout << endl;
}

int main() {
    LinkedList <LinkedList <int> > lol;
    LinkedList<int> mylist;
    for(int i = 0; i < 5; i++)
        mylist.push_front(i);
    lol.push_front(mylist);
    lol.begin()->value.reverse();
    cout << lol.begin()->value.find_by_index(3)->value;
    return 0;
}