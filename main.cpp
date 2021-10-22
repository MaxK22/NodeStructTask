#include <iostream>
using namespace std;
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
    List(T a[], int size_a)
    {
        if(size_a > 0) {
            Node<T> *x = new Node<T>(a[0]);
            Node<T> *y;
            head = x;
            for (int i = 1; i < size_a; ++i)
            {
                y = new Node<T>(a[i]);
                x->next = y;
                x = y;
            }
            tail = x;
        }
        else
        {
            head = NULL;
            tail = NULL;
        }
    }
    Node<T> operator[](int i) {
        Node<T>* x = head;
        for(int j = 1; j < i && x->next != NULL; ++j)
        {
            x = x->next;
        }
        return *x;
    }
    int check_size()
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
    void delete_by_id(int i)
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
    void delete_by_element(T element) {
        if(head != NULL) {
            Node<T>* x = head;
            while (x->next != NULL) {
                if (x->next->src == element) {
                    Node<T> *y = x->next->next;
                    delete x->next;
                    x->next = y;
                    if(y == NULL)
                        tail = x;
                    x = NULL;
                }
                x = x->next;
            }
        }
        else if(head != NULL && head->src == element)
        {
            delete head;
            head = NULL;
            tail = NULL;
        }
    }
    int find_by_element(T element) {
            Node<T>* x = head;
            int i = 0;
            while (x != NULL) {
                if (x->src == element) {
                    return i;
                }
                x = x->next;
                i++;
            }
            return -1;
    }
    template<typename Type> friend ostream& operator<<(ostream& out, const List<Type>& list)
    {
        if(list.head != NULL) {
            Node<T>* x = list.head;
            while (x->next != NULL) {
                out << x->src << "->";
                x = x->next;
            }
            out << x->src;
        }
        else
            out << "empty";
        return out;
    }
    std::pair<Node<T>*, Node<T>*> merge_sort(Node<T>* left, Node<T>* right, int size)
    {
        if(size == 1)
            return make_pair(left, left);
        int n = size/2;
        int m = size - n;


        Node<T>* mid = left;
        for(int j = 1; j < n; ++j)
        {
            mid = mid->next;
        }
        Node<T>* next_mid = mid->next;
        /*
        Node<T>* end = mid;
        for(int j = 1; j <= m; ++j)
        {
            end = end->next;
        }*/


        std::pair<Node<T>*, Node<T>*> middle_and_first = merge_sort(left, mid,  n);
        std::pair<Node<T>*, Node<T>*> middle_and_first2 = merge_sort(next_mid/* ???? */, right,  m);
        Node<T>* now2 = middle_and_first2.first;
        Node<T>* now1 = middle_and_first.first;
        middle_and_first.second->next = now2;//merge
        Node<T>* h;
        int i = 1, j = 1;
        if(now1->src < now2->src)
        {
            h = now1;
            now1 = now1->next;
            i++;
        }
        else
        {
            h = now2;
            now2 = now2->next;
            j++;
        }
        pair<Node<T>*, Node<T>*> ans = make_pair(h, h);
        while(i <= n || j <= m)
        {
                if(i <= n && now1->src < now2->src || j > m)
                {
                    h->next = now1;
                    h = now1;
                    now1 = now1->next;
                    i++;
                }
                else
                {
                    h->next = now2;
                    h = now2;
                    now2 = now2->next;
                    j++;
                }
        }
        ans.second = h;
        if(head->src > ans.first->src)
            head = ans.first;
        return ans;
    }
};

int main() {
    int a[10] = {10, 6, 3, 5, 8, 7, 9, 1, 2, 4};
    cout << "ok \n";
    List<int> list = List<int>(a, 10);
    //cout << list << endl;
    list.merge_sort(list.head, list.tail, 10).first;
    cout << list;

    return 0;
}
