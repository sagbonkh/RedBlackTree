#include "RedBlackTree.h"

int main(){

    RedBlackTree rbt;
    rbt.insert(5);
    rbt.insert(7);
    rbt.insert(3);
    rbt.insert(6);
    rbt.insert(11);
    rbt.insert(4);

    cout<<"num of vals "<<rbt.size()<<endl;

    rbt.print();

    RedBlackTree rbt2;
    rbt2 = rbt;
    cout<<"num of vals in rbt2 "<<rbt2.size()<<endl;
    rbt2.print();

    return 0;
}