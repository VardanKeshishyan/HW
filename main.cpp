#include "bst.h"
#include "avltree.h"
#include "bstree.h"

int main()
{
    measure_BSTs("src/random.txt");
    std::cout << std::endl;
    measure_BSTs("src/sorted.txt");
    return 0;}
