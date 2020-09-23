/*
Sample Input - 
4
5 23 2 6
2 7
5

    does this->
Initially add 4 elements -> 5,23,2,6
Then, after 2, add 7
Then, remove 5
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node{
    int data;
    node* next;
};

typedef struct{
    size_t _m_size, _cap;   //just to store sizes, gives O(1) size, though NOT USED HERE
    node* last;
} csll;

void insert(csll*, int data);
void insertAfter(csll*, int d, int newData);

void removeData(csll*, int data);
void printCSLL(csll*);

int main(){
    csll l;
    l._m_size = 0;
    l.last = NULL;

    int num;
    printf("Please enter number of elements: ");
    scanf("%d", &l._cap);
    for( int i = 0; i < l._cap; i++ ){
        scanf("%d", &num);
        insert(&l, num);
    }
    printCSLL(&l);

    int prev_data;
    printf("Please enter value to insert after, then the data to insert: ");
    scanf("%d %d", &prev_data, &num);
    insertAfter(&l, prev_data, num);
    printCSLL(&l);

    printf("Please enter data to erase: ");
    scanf("%d", &prev_data);
    removeData(&l, prev_data);
    printCSLL(&l);

    return 0;
}

void insert(csll* l, int data){
    node* newNode = (node*) malloc(sizeof(node));
    newNode->data = data;
    // no need to set `next` = NULL, since in circular that's not the case for >=1 elements

    if( l->last == NULL ){    //empty
        l->last = newNode;
        newNode->next = l->last;
    }

    newNode->next = l->last->next;
    l->last->next = newNode;
    l->last = newNode;
    ++(l->_m_size);
}

void insertAfter(csll* l, int prev, int data){
    if( l->last == NULL ) return; //`prev` can't be found

    node* tmp = l->last->next;
    while( tmp != l->last && tmp->data != prev ){
        tmp = tmp->next;
    }
    if(tmp == l->last){
        if(tmp->data == prev)
            return insert(l, data);

        return; //ie. couldn't find prev
    }

    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    newNode->next = tmp->next;
    tmp->next = newNode;

    ++(l->_m_size);
}

void removeData(csll* l, int data){
    if( l->last == NULL ) return; //empty

    node* tmp = l->last->next, *prev = l->last;
    while( tmp != l->last && tmp->data != data ){
        prev = tmp;
        tmp = tmp->next;
    }
    
    if(tmp == l->last){
        if(tmp->data != data)   return; //ie. couldn't find data
        else if(prev == tmp) l->last = NULL;
        else l->last = prev;    //since tmp will be deleted
    }
    prev->next = tmp->next;

    free(tmp);
    --(l->_m_size);
}

void printCSLL(csll* l){
    if( l->last == NULL ){
        printf("List is empty\n");
        return;
    }

    node* tmp = l->last->next;
    for( ; (tmp != l->last); tmp=tmp->next)
        printf("%d ", tmp->data);

    printf("%d\n", l->last->data);  //printing the last element, it will be skipped by for loop
}
