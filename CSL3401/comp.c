/*
Write a program to add, subtract, multiply two polynomials using singly linked list. The node of your linked list should hold two data vales one is coefficient and another one is exponent. First create two linked lists representing two polynomials and for each addition, subtraction and multiplication create separate polynomials.
*/

#include <stdio.h>
#include <stdlib.h>

struct Sll{
    int coeff, exp;
    struct Sll* next;
};
typedef struct Sll Sll;

typedef struct {
    int degree;
    int n_terms;
    Sll* head;
} Poly; //the polynomial struct

Poly* getAddedPoly(Poly*, Poly*);
Poly* getSubPoly(Poly*, Poly*);
Poly* getCrossPoly(Poly*, Poly*);
Poly* getDividePoly(Poly*, Poly*);

void inputPoly(Poly*);    //takes the polynomial
void printPoly(Poly*);
void pushBack(Poly*, int, int);

void main()
{
    Poly a,b;
    a.head = b.head = NULL; //just to ensure, its NULL, and not a reachable garbage location
    printf("Please type the number of terms in first and the second polynomial you will type: ");
    scanf("%d %d", &a.n_terms, &b.n_terms);
    printf("Now proceed to enter the polynomials (in [(coeff,exp),(coeff,exp),...] form)\n");

    inputPoly(&a);
    inputPoly(&b);

    Poly *add = getAddedPoly(&a, &b);
    Poly *sub = getSubPoly(&a, &b);
    Poly *mult = getCrossPoly(&a, &b);
    Poly *div = getDividePoly(&a, &b);

        //freeing memory if not NULL
    if(add) free(add); if(sub) free(sub); if(mult) free(mult); if(div) free(div);
}

void inputPoly(Poly* p){    //takes the polynomial
    int coeff, exp;
    Sll *last = p->head;
    for (int i = 0; i < p->n_terms; ++i){
        scanf("%d %d", &coeff, &exp);
        Sll* add = (Sll*)malloc(sizeof(Sll));
        add->coeff = coeff;
        add->exp = exp;
        add->next = NULL;

        if(p->head!=NULL){
            last->next = add;
            last = last->next;
        }
        else{
            p->head = add;
            last = p->head;
        }
            //adding in reverse order of input but not problematic, since addition is associative
        // pushBack(p, coeff, exp);  // more efficient, and later algos are neverthless O(N^2), so doesn't matter much start to end or end to start
    }

    printPoly(p);
}

void printPoly(Poly *p)
{
   int i;
   Sll *t;
   if(p->head==NULL)
     printf("\nPolynomial has no terms");
   else
   {
       printf("\n");
       t = p->head;
       while(t!=NULL)
       {
           printf("%dx^%d + ",t->coeff, t->exp);
           t = t->next;
           if(t->next == NULL) break;   //leaves the last element
       }
        if(t!=NULL){ //ie. reached here through break; statement
            printf("%d", t->coeff);
            if(t->exp) printf("x^%d", t->exp);
        }
       printf("\n");
   }

}

Sll* appendPoly(Poly* org, Poly* a, Sll* last);   //expecting `last` to be a pointer in `org`
Poly* getAddedPoly(Poly* a, Poly* b){
    Poly *p = (Poly*)malloc(sizeof(Poly));

    Sll* newHead = (Sll*)malloc(sizeof(Sll));
    newHead->coeff = a->head->coeff;    //`copying the old head data only`
    newHead->exp = a->head->exp;
    newHead->next = NULL;

    p->head = newHead;
    Sll *last = p->head;    //last is a pointer in p
    last = appendPoly(p, a, last);
    appendPoly(p, b, last);

    printPoly(p);

    return p;
}

Sll* appendPoly(Poly* org, Poly* a, Sll* last){   //expecting `last` to be a pointer in `org`
    Sll *t = a->head;   //t is pointer in a
    while(t!=NULL)
    {
        Sll* add = (Sll*)malloc(sizeof(Sll));
        add->coeff = t->coeff;
        add->exp = t->exp;
        add->next = NULL;

        if(org->head!=NULL){
            last->next = add;
            last = last->next;
        }
        else{   //ideally, this else should not run ever
            org->head = add;
            last = org->head;
        }

        t = t->next;
    }
    return last;
}

Poly* getSubPoly(Poly* a, Poly* b){}
Poly* getCrossPoly(Poly* a, Poly* b){}
Poly* getDividePoly(Poly* a, Poly* b){}
