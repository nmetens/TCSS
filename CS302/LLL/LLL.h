
#include "node.h"

class List {
    public:
        List();
        List(const List &src_list);
        ~List();

        void display();
        int insert(int data);

    private:
        node * head;

        void display(node * head);
        int insert(int data, node * &head);
};

