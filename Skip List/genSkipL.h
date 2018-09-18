#ifndef genSkipL_h
#define genSkipL_h
#include <cmath>
const int maxLevel = 4;
template<class T>
class SkipListNode{
    
public:
    SkipListNode(){}
    T key;
    SkipListNode **next;
    
};
template<class T>
class SkipList{
    
public:
    SkipList();
    bool isEmpty() const;
    void choosePowers();
    int chooseLevel();
    T* skipListSearch(const T&);
    void skipListInsert(const T&);
private:
    typedef SkipListNode<T> *nodePtr;
    nodePtr root[maxLevel];
    int powers[maxLevel];
    
};

template<class T>
SkipList<T>::SkipList(){
    for(int i = 0; i < maxLevel; i++)
        root[i] = 0;
}

template<class T>
bool SkipList<T>::isEmpty () const{
    return root[0] == 0;
}

template <class T>
void SkipList<T>::choosePowers(){
    powers[maxLevel-1] = (2 << (maxLevel-1)) - 1; // 2^maxLevel - 1
    for (int i = maxLevel - 2, j = 0; i >= 0; i--, j++)
        powers[i] = powers[i+1] - (2 << j); // 2^(j+1)
}
template<class T>
int SkipList<T>::chooseLevel(){
    int i;
    int r = rand() % (powers[maxLevel - 1]+1);
    for (i = 1; i < maxLevel; i++)
        if (r < powers[i])
            return i - 1; //return a level < the highest level
    return i-1;
}

template<class T>
T* SkipList<T>::skipListSearch(const T& key){
    if (isEmpty()) return 0;
    nodePtr prev, curr;
    int lvl;                                                // find the highest non-null
    for (lvl = maxLevel - 1; lvl >= 0 && !root[lvl]; lvl--);// level
    prev = curr = root [lvl];
    while(true){
        if (key == curr->key)           // success if equal
            return &curr->key;
        else if (key < curr->key){  // If smalled, go down
            if(lvl == 0)            // if possibles
                return 0;
            else if (curr == root[lvl])         // by one level
                curr = root[--lvl];             // starting from the
            else curr = *(prev->next + --lvl);  // predecessor which
        }                                       // can be the root
        else {                                  // if greater,
            prev = curr;                        // go to the next
            if (*(curr->next + lvl) != 0)       // non-null node
                curr = *(curr->next + lvl);     // on the same level
            else {
                for (lvl--; lvl >= 0 && *(curr->next + lvl) == 0; lvl--);
                if(lvl >= 0)
                    curr = *(curr->next + lvl);
                else return 0;
            }
            
        }
    }
    
}

template <class T>
void SkipList<T>::skipListInsert (const T& key){
    nodePtr curr[maxLevel], prev [maxLevel], newNode;
    int lvl, i;
    curr[maxLevel-1] = root[maxLevel - 1];
    prev [maxLevel - 1] = 0;
    for (lvl = maxLevel - 1; lvl >= 0; lvl--){
        while(curr[lvl] && curr[lvl]->key < key){
            prev[lvl] = curr[lvl];
            curr[lvl] = *(curr[lvl]->next + lvl);
        }
        if (curr[lvl] && curr[lvl]->key == key)
            return;
        if(lvl > 0){
            if(prev[lvl] == 0){
                curr[lvl-1] = root[lvl-1];
                prev[lvl-1] = 0;
            }
            else{
                curr[lvl - 1] = *(prev[lvl] -> next + lvl - 1);
                prev[lvl - 1] = prev [lvl];
            }
            
        }
        
    }
    lvl = chooseLevel();
    newNode = new SkipListNode<T>;
    newNode -> next = new nodePtr[sizeof(nodePtr) * (lvl+1)];
    newNode -> key = key;
    for (i = 0; i <= lvl; i++){
        *(newNode->next + 1) = curr[i];
        if (prev[i] == 0)
            root[i] = newNode;
        else *(prev[i]->next + 1) = newNode;
    }
}


#endif /* genSkipL_h */

