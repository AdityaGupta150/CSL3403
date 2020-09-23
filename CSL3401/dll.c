#include <stdio.h>
#include <stdlib.h>

typedef struct node node;
struct node{
    int data;
    node* prev, *next;
};

typedef struct{
    size_t _m_size, _cap;
    node *begin, *end;
} list;

void push(list*,int);   //these are not copy paste, and have been created at moment
void insertAfter(list*, size_t pos, int data);
void removeAt(list*, size_t pos);
void printList(list*);

int main()
{
    list l;
    l._m_size = 0;
    l.begin = l.end = NULL;

    int num;
        //1-based indexing user side
    printf("Please enter number of elements: ");
    scanf("%d", &l._cap);
    for (int i = 0; i < l._cap; i++){
        scanf("%d", &num);
        push(&l, num);
    }
    printList(&l);    

    int pos;
    printf("Please enter position and then value to insert: ");
    scanf("%d %d", &pos,&num);
    insertAfter(&l, pos-1, num);
    printList(&l);

    printf("Please enter position to erase: ");
    scanf("%d",&pos);
    removeAt(&l, pos-1);
    printList(&l);

    return 0;
}

void push(list* l, int data){
    return insertAfter(l, l->_m_size, data);
}

void insertAfter(list* l, size_t pos, int data){
    node *tmp = l->begin;
    if(pos > l->_m_size)    return;

    node *newNode = (node*)malloc(sizeof(node));
    newNode->data = data;
    if(l->begin == NULL){ //empty
        l->begin = newNode;
        newNode->prev = NULL;
        newNode->next = NULL;
        l->end = newNode;

        ++(l->_m_size);
        return;
    }

    int counter = 0;
    while (counter != pos){
        ++counter;
        tmp = tmp->next;
    }

    newNode->next = tmp;
    if(tmp == NULL){    //at end
        newNode->prev = l->end;
        l->end->next = newNode;
        l->end = newNode;
    }else{
        newNode->prev = tmp->prev;
        if(tmp->prev)   tmp->prev->next = newNode;
        tmp->prev = newNode;
    }
    
    ++(l->_m_size);
}

void removeAt(list* l, size_t pos){
    if( pos >= l->_m_size ) return;

    node* rem = l->begin;
    int counter = 0;
    while (counter != pos)
    {
        ++counter;
        rem = rem->next;
    }
    if(rem->prev)   rem->prev->next = rem->next;
    if(rem->next)   rem->next->prev = rem->prev;
    free(rem);

    --(l->_m_size);
}

void printList(list* l){
    node* tmp = l->begin;

    printf("\n");
    if(l->_m_size == 0){
        printf("List is empty\n");
        return;
    }
    while (tmp!=NULL)
    {
        printf("%d ", tmp->data);
        tmp = tmp->next;
    }
    printf("\n");

}
