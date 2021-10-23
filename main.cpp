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
    Node<T>* operator[](int i) {
        if(head == NULL)
            return NULL;
        Node<T>* x = head;
        int j = 1;
        for(; j < i && x->next != NULL; ++j)
        {
            x = x->next;
        }
        if(j < i)
            return NULL;
        return x;
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
            Node<T>* el = new Node<T>(new_element);
            Node<T>* x = head;
            int j = 1;
            for(; j < i - 1 && x->next != NULL; ++j)
            {
                x = x->next;
            }
            if(x->next == NULL) {
                x->next = el;
                el->next = NULL;
                tail = el;
            }
            else
            {
                el->next = x->next->next;
                x->next = el;
                if(el->next == NULL)
                    tail = el;//
            }
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
        cout << "Element wasn't found ";
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
            if((now1->src < now2->src && i <=n)|| j > m)
            {
                h->next = now1;
                h = now1;
                if(i < n) now1 = now1->next;
                i++;
            }
            else
            {
                h->next = now2;
                h = now2;
                if(j < m) now2 = now2->next;
                j++;
            }
        }
        ans.second = h;
        if(head->src > ans.first->src)
            head = ans.first;
        ans.second->next = NULL;
        return ans;
    }
};

int main() {
    cout << "Enter 'help' to see all commands" << endl;
    List<int> list = List<int>();
    string command;
    cin >> command;
    while(command != "end")
    {
        if(command == "help")
            cout << "i element: 'i_el'" << endl <<
            "size: 'size'" << endl <<
            "is empty: 'is_empty'" << endl <<
            "push front: 'p_f' [int](new element)" << endl <<
            "push back: 'p_b' [int](new element)" << endl <<
            "push i: 'p_i' [int](i) [int](new element)" << endl <<
            "delete front: 'd_f'" << endl <<
            "delete back: 'd_b'" << endl <<
            "delete i: 'd_i' [int](i)" << endl <<
            "delete element: 'd_el' [int](old element)" << endl <<
            "find i by element: 'find' [int](old element)" << endl <<
            "merge sort: 'm_sort'" << endl <<
            "print: 'print'" << endl <<
            "close programm: 'end'";
        else if(command == "i_el")
        {
            int i;
            cin >> i;
            Node<int>* a = list[i];
            if(a != NULL)
            cout << list[i]->src;
            else
                cout << "Element wasn't found";
        }
        else if(command == "size")
        {
            cout << list.check_size();
        }
        else if(command == "is_empty")
        {
            cout << list.is_empty();
        }
        else if(command == "p_f")
        {
            int el;
            cin >> el;
            list.push_front(el);
            cout << "element was pushed";
        }
        else if(command == "p_b")
        {
            int el;
            cin >> el;
            list.push_back(el);
            cout << "element was pushed";
        }
        else if(command == "p_i")
        {
            int el, i;
            cin >> i >> el;
            list.push(i, el);
            cout << "element was pushed";
        }
        else if(command == "d_f")
        {
            list.delete_front();
            cout << "element was deleted";
        }
        else if(command == "d_b")
        {
            list.delete_back();
            cout << "element was deleted";
        }
        else if(command == "d_i")
        {
            int i;
            cin >> i;
            list.delete_by_id(i);
            cout << "element was deleted";
        }
        else if(command == "d_el")
        {
            int el;
            cin >> el;
            list.delete_by_element(el);
            cout << "element was deleted";
        }
        else if(command == "find")
        {
            int el;
            cin >> el;
            cout << list.find_by_element(el);
        }
        else if(command == "m_sort")
        {
            int size = list.check_size();
            list.merge_sort(list.head, list.tail, size);
            cout << list;
        }
        else if(command == "print")
        {
            cout << list;
        }
        cout << endl;
        cin >> command;
    }

    return 0;
}
