#ifndef LINKEDLIST_H
#define LINKEDLIST_H
template <class N>
class NodeOfList {
public:
    N data;
    NodeOfList<N> *next;

    NodeOfList() {
        data = N();
        next = nullptr;
    }

    NodeOfList(N el) {
        data = el;
        next = nullptr;
    }

    NodeOfList<N> &operator=(const NodeOfList<N> &rht) {
        data = rht.data;
        next = rht.next;
        return *this;
    }

    N operator*() {
        return data;
    }

};

template <class I>
class ListIterator {
public:
    ListIterator() {
        node = nullptr;
        isEndIter = true;
    }

    ListIterator(NodeOfList<I> *ref) {
        node = ref;
        isEndIter = false;
    }

    ListIterator(const ListIterator<I> &other) {
        node = other.node;
        isEndIter = other.isEndIter;
    }

    void operator++(int a) {
        if (node->next == nullptr) {
            isEndIter = true;
        } else {
            node = node->next;
        }
    }

    void operator++() {
        if (node->next == nullptr) {
            isEndIter = true;
        } else {
            node = node->next;
        }
    }

    ListIterator<I> &operator+(int num) {
        auto iter = *this;
        while (num > 0) {
            iter++;
            num--;
        }
        return iter;
    }

    I &operator*() {
        if (isEndIter) {
            std::cout << "Error! You cannot indirect the end() iterator.\n";
            exit(-1);
        }
        return node->data;
    }

    bool operator==(const ListIterator<I> &other) {
        return isEndIter == other.isEndIter and node == other.node or isEndIter == other.isEndIter and
               isEndIter == true;
    }

    bool operator!=(const ListIterator<I> &other) {
        return !(*this == other);
    }

    NodeOfList<I> *nodeRef() {
        return node;
    }

private:
    NodeOfList<I> *node;
    bool isEndIter;
};

template <class T>
class LinkedList {
public:
    NodeOfList<T> *head;
    NodeOfList<T> *tail;

    int size() {
        return length;
    }

    LinkedList() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    LinkedList(int count) {
        head = new NodeOfList<T>;
        auto tmp = head;
        for (int i = 0; i < count - 1; i++) {
            tmp->next = new NodeOfList<T>;
            tmp = tmp->next;
        }
        tail = tmp;
        length = count;
    }

    LinkedList(const std::initializer_list<T> &t) {
        head = new NodeOfList<T>;
        auto tmp = head;
        for (int i = 0; i < t.size() - 1; i++) {
            tmp->next = new NodeOfList<T>;
            tmp = tmp->next;
        }
        tail = tmp;
        tmp = head;
        for (auto i = t.begin(); i != t.end(); i++) {
            tmp->data = *i;
            tmp = tmp->next;
        }
        length = t.size();
    }

    void pushBack(const T &data) {
        if (length == 0) {
            head = new NodeOfList(data);
            tail = head;
        } else {
            tail->next = new NodeOfList(data);
            tail = tail->next;
        }
        length++;
    }

    void pushFront(const T &data) {
        if (length == 0) {
            head = new NodeOfList(data);
            tail = head;
        } else {
            NodeOfList<T> *tmp = new NodeOfList(data);
            tmp->next = head;
            head = tmp;
        }
        length++;
    }

    T popFront() {
        if (length == 0) {
            std::cout << "Error! List is empty.\n";
            exit(-1);
        } else if (length == 1) {
            length--;
            T res = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
            return res;
        } else {
            length--;
            T res = head->data;
            auto ref = head;
            head = head->next;
            delete ref;
            return res;
        }
    }

    T popBack() {
        if (length == 0) {
            std::cout << "Error! List is empty.\n";
            exit(-1);
        } else if (length == 1) {
            length--;
            T res = tail->data;
            delete tail;
            head = nullptr;
            tail = nullptr;
            return res;
        } else {
            length--;
            NodeOfList<T> *ref = head;
            while (ref->next != tail) {
                ref = ref->next;
            }
            tail = ref;
            T res = ref->next->data;
            delete ref->next;
            ref->next = nullptr;
            return res;
        }
    }

    LinkedList<T> &operator=(const std::initializer_list<T> &initLst) {
        auto tmp = head;
        if (this->size() > initLst.size()) {
            for (auto el = initLst.begin(); el != initLst.end(); el++) {
                tmp->data = *el;
                tail = tmp;
                if (tmp != nullptr) {
                    tmp = tmp->next;
                }
            }
            if (this->size() > initLst.size()) {
                auto nxt = tmp->next;
                while (tmp != nullptr) {
                    delete tmp;
                    tmp = nxt;
                    if (tmp != nullptr) {
                        nxt = tmp->next;
                    }
                }
            }
            tail->next = nullptr;
        } else {
            tmp = tail;
            for (int i = 0; i < initLst.size() - this->size(); i++) {
                tmp->next = new NodeOfList<T>;
                tmp = tmp->next;
            }
            tail = tmp;
            tmp = head;
            for (auto elem = initLst.begin(); elem != initLst.end(); elem++) {
                tmp->data = *elem;
                tmp = tmp->next;
            }
        }
        length = initLst.size();
        return *this;
    }

    ListIterator<T> begin() {
        return ListIterator<T>(head);
    }

    ListIterator<T> end() {
        return ListIterator<T>();
    }

    void insert(ListIterator<T> &iter, T data) {
        if (iter == begin() or iter == end()) {
            std::cout << "Error! Cannot insert into begin() or end(), use pushFront() and pushBack().\n";
            exit(-1);
        }
        auto tmp = iter.nodeRef()->next;
        iter.nodeRef()->next = new NodeOfList<T>(data);
        iter.nodeRef()->next->next = tmp;
    }

    void printList() {
        std::cout << '[';
        for (auto i = begin(); i != end(); i++) {
            std::cout << *i << ((i.nodeRef()->next == end().nodeRef()) ? "" : ", ");
        }
        std::cout << "]\n";
    }

    ~LinkedList() {
        if (length != 0) {
            auto tmp = head;
            auto nxt = head->next;
            while (tmp != nullptr) {
                delete tmp;
                tmp = nxt;
                if (tmp != nullptr) {
                    nxt = tmp->next;
                }
            }
        }
    }

    bool isEmpty() {
        return length == 0;
    }

private:
    int length;
};

template <>
class LinkedList<char> {
public:
    NodeOfList<char> *head;
    NodeOfList<char> *tail;

    int size() {
        return length;
    }

    LinkedList() {
        head = nullptr;
        tail = nullptr;
        length = 0;
    }

    LinkedList(int count) {
        head = new NodeOfList<char>;
        auto tmp = head;
        for (int i = 0; i < count - 1; i++) {
            tmp->next = new NodeOfList<char>;
            tmp = tmp->next;
        }
        tail = tmp;
        length = count;
    }

    LinkedList(const std::initializer_list<char> &t) {
        head = new NodeOfList<char>;
        auto tmp = head;
        for (int i = 0; i < t.size() - 1; i++) {
            tmp->next = new NodeOfList<char>;
            tmp = tmp->next;
        }
        tail = tmp;
        tmp = head;
        for (auto i = t.begin(); i != t.end(); i++) {
            tmp->data = *i;
            tmp = tmp->next;
        }
        length = t.size();
    }

    LinkedList(const std::string &str) {
        int size = str.size();
        int ind = 0;
        head = new NodeOfList<char>;
        auto tmp = head;
        head->data = str[ind++];
        for (int i = 0; i < size - 1; i++) {
            tmp->next = new NodeOfList<char>;
            tmp->next->data = str[ind++];
            tmp = tmp->next;
        }
        tail = tmp;
        length = size;
    }

    LinkedList<char> &operator=(const std::string &str) {
        if (length >= str.size()) {
            auto tmp = head;
            for (int i: str) {
                tmp->data = i;
                tail = tmp;
                tmp = tmp->next;
            }
            auto nxt = tmp;
            while (tmp != nullptr) {
                nxt = tmp->next;
                delete tmp;
                tmp = tmp->next;
            }
        } else {
            auto tmp = tail;
            for (int i = 0; i < str.size() - length; i++) {
                tmp = new NodeOfList<char>;
                tail->next = tmp;
                tail = tmp;
            }
            tmp = head;
            for (auto i: str) {
                tmp->data = i;
                tmp = tmp->next;
            }
        }
        length = str.size();
        return *this;
    }

    void pushBack(const char &data) {
        if (length == 0) {
            head = new NodeOfList(data);
            tail = head;
        } else {
            tail->next = new NodeOfList(data);
            tail = tail->next;
        }
        length++;
    }

    void pushFront(const char &data) {
        if (length == 0) {
            head = new NodeOfList(data);
            tail = head;
        } else {
            NodeOfList<char> *tmp = new NodeOfList(data);
            tmp->next = head;
            head = tmp;
        }
        length++;
    }

    char popFront() {
        if (length == 0) {
            std::cout << "Error! List is empty.\n";
            exit(-1);
        } else if (length == 1) {
            length--;
            char res = head->data;
            delete head;
            head = nullptr;
            tail = nullptr;
            return res;
        } else {
            length--;
            char res = head->data;
            auto ref = head;
            head = head->next;
            delete ref;
            return res;
        }
    }

    char popBack() {
        if (length == 0) {
            std::cout << "Error! List is empty.\n";
            exit(-1);
        } else if (length == 1) {
            length--;
            char res = tail->data;
            delete tail;
            head = nullptr;
            tail = nullptr;
            return res;
        } else {
            length--;
            NodeOfList<char> *ref = head;
            while (ref->next != tail) {
                ref = ref->next;
            }
            tail = ref;
            char res = ref->next->data;
            delete ref->next;
            ref->next = nullptr;
            return res;
        }
    }

    LinkedList<char> &operator=(const std::initializer_list<char> &initLst) {
        auto tmp = head;
        if (this->size() > initLst.size()) {
            for (auto el = initLst.begin(); el != initLst.end(); el++) {
                tmp->data = *el;
                tail = tmp;
                if (tmp != nullptr) {
                    tmp = tmp->next;
                }
            }
            if (this->size() > initLst.size()) {
                auto nxt = tmp->next;
                while (tmp != nullptr) {
                    delete tmp;
                    tmp = nxt;
                    if (tmp != nullptr) {
                        nxt = tmp->next;
                    }
                }
            }
            tail->next = nullptr;
        } else {
            tmp = tail;
            for (int i = 0; i < initLst.size() - this->size(); i++) {
                tmp->next = new NodeOfList<char>;
                tmp = tmp->next;
            }
            tail = tmp;
            tmp = head;
            for (auto elem = initLst.begin(); elem != initLst.end(); elem++) {
                tmp->data = *elem;
                tmp = tmp->next;
            }
        }
        length = initLst.size();
        return *this;
    }

    ListIterator<char> begin() {
        return ListIterator<char>(head);
    }

    ListIterator<char> end() {
        return ListIterator<char>();
    }

    void insert(ListIterator<char> &iter, char data) {
        if (iter == begin() or iter == end()) {
            std::cout << "Error! Cannot insert into begin() or end(), use pushFront() and pushBack().\n";
            exit(-1);
        }
        auto tmp = iter.nodeRef()->next;
        iter.nodeRef()->next = new NodeOfList<char>(data);
        iter.nodeRef()->next->next = tmp;
    }

    void printList() {
        std::cout << '[';
        for (auto i = begin(); i != end(); i++) {
            std::cout << *i << ((i.nodeRef()->next == end().nodeRef()) ? "" : ", ");
        }
        std::cout << "]\n";
    }

    ~LinkedList() {
        if (length != 0) {
            auto tmp = head;
            auto nxt = head->next;
            while (tmp != nullptr) {
                delete tmp;
                tmp = nxt;
                if (tmp != nullptr) {
                    nxt = tmp->next;
                }
            }
        }
    }

    bool isEmpty() {
        return length == 0;
    }

private:
    int length;
};

#endif//LINKEDLIST_H
