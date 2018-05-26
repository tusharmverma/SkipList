#include <iostream>
#include "genSkipL.h"
int main(int argc, const char * argv[]) {
    SkipList<int> temp;
    int a = 11;
    int b = 13;
    temp.skipListInsert(a);
    temp.skipListInsert(b);
    return 0;
    
}
