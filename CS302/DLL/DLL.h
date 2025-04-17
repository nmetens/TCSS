
#include "node.h"

class DList {
    public:
        DList();
        DList(const DList &src_list);
        ~DList();

        void display();
        void display_backwards();
        int insert(int data);

    private:
        node * head;
        node * tail;

        void display(node * head);
        void display_backwards(node * tail);
};
