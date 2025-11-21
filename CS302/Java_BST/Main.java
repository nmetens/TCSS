import java.util.Scanner; // For user input

public class Main {
    public static void main(String[] args) {
        BST bst = new BST();
        for (int i = 0; i < 10; i++) {
            bst.insert(i);
        }
        int [] ints = {4, 3, 5, 2, 5, 2, 4, 2};
        for (int anInt : ints) {
            bst.insert(anInt);
        }

        System.out.print("Display Tree in order: ");
        bst.display();

        System.out.println();
        System.out.print("Total nodes: " + bst.countNodes());
        System.out.println();

        /*
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter a value: ");
        int input = scanner.nextInt();
        System.out.println("The value " + input + " appeared " + bst.countNode(input) + " times.");
        */

        int newValue = 20;
        bst.addIfNotExist(newValue);
        System.out.println();
        System.out.print("Display Tree in order: ");
        bst.display();
        System.out.println();

        System.out.print("Nodes removed: " + bst.removeAll());
        System.out.println();

        System.out.print("Display Tree in order: ");
        bst.display();
    }
}