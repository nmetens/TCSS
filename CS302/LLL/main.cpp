
#include "LLL.h"

int main() {

    List my_list;

    int data[6] = {10, 5, 2, 7, 11, 4};

    for (int i=0; i<6; ++i) my_list.insert(data[i]);

    my_list.display();

    return 0;
}
