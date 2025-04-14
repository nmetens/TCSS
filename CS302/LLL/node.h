
class node {
    public:
        node();
        node(const node &src_node);
        node(int data); // Insert data
        ~node();

        void display();

        int getData();
        node *& getNext();
        void setNext(node * &next);

    private:
        int data;
        node * next;
};
