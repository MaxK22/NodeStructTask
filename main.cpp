#include <iostream>
template <typename T>
class  Node
{
public:
    T src;
    Node<T>* next;
    Node(T src)
    {
        this->src = src;
    }
};

template <typename T>
class  List
{
public:
    Node<T>* head;
    Node<T>* tail;
    List()
    {
        head = NULL;
        tail = NULL;
    }
    Node<T> operator[](int i) {
        Node<T>* x = head;
        for(int j = 1; j < i && x->next != NULL; ++j)
        {
            x = x->next;
        }
        return *x;
    }
    int size()
    {
        int n = 0;
        Node<T>* x = head;
        for(; x != NULL; ++n)
        {
            x = x->next;
        }
        return n;
    }
    bool is_empty()
    {
        if(head == NULL)
            return true;
        else
            return false;
    }
    void push_front(T new_element)
    {
        Node<T>* x = new Node<T>(new_element);
        x->next = head;
        if(is_empty())
            tail = x;
        head = x;
    }
    void push_back(T new_element)
    {
        Node<T>* x = new Node<T>(new_element);
        x->next = NULL;
        tail->next = x;
        if(is_empty())
            head = x;
        tail = x;
    }
    void push(int i, T new_element)
    {
        if(i == 0)
            this->push_front(new_element);
        else{
            Node<T>* x = new Node<T>(new_element);
            Node<T>* y = *(this[i-1]);
            x->next = y->next;
            y->next = x;
            if(x->next == NULL)
                tail = x;
        }
    }
    void delete_front()
    {
        if(!is_empty()) {
            Node<T> *x = head;
            head = x->next;
            delete x;
            if (is_empty())
                tail = NULL;
        }
    }
    void delete_back()
    {
        if(head != tail) {
            Node<T>* x = head;
            while (x->next != tail)
                x = x->next;
            x->next = NULL;
            delete tail;
            tail = x;
        }
        else if(!is_empty())
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
    }
    void delete_(int i)
    {
        if(head != tail) {
            Node<T>* x = head;
            int j;
            for(j = 1; j < i - 1 && x->next != NULL; ++j)
            {
                x = x->next;
            }
            if(j + 2 == i) {
                Node<T> *c = x->next->next;
                delete x->next;
                x->next = c;
                if(c == NULL)
                    tail = x;
            }
        }
        else if(!is_empty() && i == 0)
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
    }
    void delete_(int i, T element) {
        Node<T>* x = head;
        while (x != NULL) {
            
        }
    }

};

int main() {
    Node<int>* head = NULL;
    Node<int>* tale = NULL;

    return 0;
}
