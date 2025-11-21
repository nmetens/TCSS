public class BST {
    private Node root;

    public BST() {
        root = null;
    }

    public void insert(int data) {
        root = insert(data, this.root);
    }
    private Node insert(int data, Node root) {
       if (root == null) {
           root = new Node(data);
           return root;
       }
       if (data < root.getValue()) root.setLeft(insert(data, root.getLeft()));
       else root.setRight(insert(data, root.getRight()));
       return root;
    }

    public void display() {
        display(root);
    }
    private void display(Node root) {
        if (root == null) return;
        display(root.getLeft());
        System.out.print(root.getValue() + " ");
        display(root.getRight());
    }

    // Count the total number of nodes in the tree:
    public int countNodes() {
        return countNodes(root);
    }
    private int countNodes(Node root) {
        if (root == null) return 0;
        return 1 + countNodes(root.getLeft()) + countNodes(root.getRight());
    }

    // Remove all nodes in the tree:
    public int removeAll() {
        int totalNodes = countNodes();
        root = null; // Garbage collection
        return totalNodes;
    }

    /* Count the number of times a value passed
    in from the user appears in the tree: */
    public int countNode(int data) {
        return countNode(data, this.root);
    }
    private int countNode(int data, Node root) {
        if (root == null) return 0;
        int count = 0;
        if (root.getValue() == data) {
            count++;
        }
        return count + countNode(data, root.getLeft()) + countNode(data, root.getRight());
    }

    // Add a value only if it doesn't already exist in the tree:
    public void addIfNotExist(int data) {
        root = addIfNotExist(data, this.root);
    }
    private Node addIfNotExist(int data, Node root) {
        if (root == null) {
            root = new Node(data);
            return root;
        }
        if (data == root.getValue()) {
            return root; // Node already exists
        }
        if (data < root.getValue()) root.setLeft(addIfNotExist(data, root.getLeft()));
        else root.setRight(addIfNotExist(data, root.getRight()));
        return root;
    }
}