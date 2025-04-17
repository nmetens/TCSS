
class node {
    public:
        node();
        node(int data);
        ~node();

        void display();
        int getData();

        node * &getNext();
        node * &getPrev();

        void setNext(node * &next);
        void setPrev(node * &previous);

    private:
        int data;
        node * next;
        node * previous;
};
