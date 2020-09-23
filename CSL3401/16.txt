/*
PLEASE NOTE - 
    main()  function starts at line 33
    Poly is just a cover over Sll*, for easy sharing between functions

    printPoly(), optimisePoly(), are lenghty so as to get better printing on console
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

void inputPoly(Poly*);    //takes the polynomial

Poly* getAddedPoly(Poly*, Poly*);
Poly* getSubPoly(Poly*, Poly*);
Poly* getCrossPoly(Poly*, Poly*);

void printPoly(Poly*);
void optimisePoly(Poly*);

int main(){
    Poly a, b;
    a.head = b.head = NULL; //just to ensure, its NULL, and not a reachable garbage location
    printf("Number of terms in 1st and 2nd polynomial: ");
    scanf("%d %d", &a.n_terms, &b.n_terms);
    printf("\nNow please proceed to enter the polynomials \n{in [(coeff,exp),(coeff,exp),...} form)\n");

    inputPoly(&a);
    inputPoly(&b);

    Poly* add = getAddedPoly(&a, &b);   //sum and subtract are similar, with only sign being different for 2nd append
    Poly* sub = getSubPoly(&a, &b);
    Poly* mult = getCrossPoly(&a, &b);

    //freeing memory if not NULL
        //MAY LEAD TO DOUBLE FREE or CORRUPTION if memory couldn't be alloted
    free(add); free(sub); free(mult);
    return 0;
}

void inputPoly(Poly* p){    //takes the polynomial
    int coeff, exp;
    Sll* last = p->head;
    for( int i = 0; i < p->n_terms; ++i ){
        scanf("%d %d", &coeff, &exp);
        Sll* add = (Sll*) malloc(sizeof(Sll));
        add->coeff = coeff;
        add->exp = exp;
        add->next = NULL;

        if( p->head != NULL ){
            last->next = add;
            last = last->next;
        } else{
            p->head = add;
            last = p->head;
        }
    }

    printf("You entered ->");
    printPoly(p);
}

void printPoly(Poly* p){
    Sll* t;
    if( p->head == NULL )
        printf("\nPolynomial has no terms");
    else{
        printf("\n\t");
        t = p->head;
        while( t != NULL ){
            if( t->next == NULL ) break;   //leaves the last element

            if( t->exp != 0 ){
                if( t->coeff != 1 )
                    printf("%d", t->coeff);
                printf("x");
                if( t->exp > 1 ) printf("^%d", t->exp);
            } else{
                printf("%d", t->coeff);
            }
            printf(" + ");

            t = t->next;
        }
        if( t != NULL ){ //ie. reached here through break; statement
            if( t->exp != 0 ){
                if( t->coeff != 1 ) //all these ifs are just for better printing
                    printf("%d", t->coeff);
                printf("x");
                if( t->exp > 1 ) printf("^%d", t->exp);
            } else{
                printf("%d", t->coeff);
            }
        }
        printf("\n");
    }

}

Sll* appendPoly(Poly* org, Poly* a);   //calls overload with last=NULL, and sign=+1
Sll* appendPoly_signed(Poly* org, Poly* a, Sll* last, short sign);   //expecting `last` to be a pointer in `org`

Poly* getAddedPoly(Poly* a, Poly* b){
    Poly* p = (Poly*) malloc(sizeof(Poly));

    p->head = NULL;  //last is pointer in p
    Sll* last = p->head;
    last = appendPoly(p, a);  // append a to p
    appendPoly_signed(p, b, last, +1);

    optimisePoly(p);  // +1 shows sign
    printf("The summed polynomial is:");
    printPoly(p);

    return p;
}

Poly* getSubPoly(Poly* a, Poly* b){
    Poly* p = (Poly*) malloc(sizeof(Poly));

    p->head = NULL;
    Sll* last = p->head;
    last = appendPoly(p, a);  // append a to p
    appendPoly_signed(p, b, last, -1); //-1 shows sign

    optimisePoly(p);  // -1 shows sign

    printf("The subtracted polynomial is:");
    printPoly(p);
    return p;
}

    Poly* getCrossPoly(Poly* a, Poly* b){
        Poly* p = (Poly*) malloc(sizeof(Poly));

        p->head = NULL;
        Sll* last = p->head;

        Sll* t1 = a->head, * t2 = b->head;
        while( t1 != NULL ){
            t2 = b->head;
            while( t2 != NULL ){
                Sll* add = (Sll*) malloc(sizeof(Sll));
                add->coeff = t1->coeff * t2->coeff;
                add->exp = t1->exp + t2->exp;
                add->next = NULL;

                if( p->head != NULL ){
                    last->next = add;
                    last = last->next;
                } else{
                    p->head = add;
                    last = p->head;
                }

                if( t2 ) t2 = t2->next;
            }
            if( t1 ) t1 = t1->next;
        }

        optimisePoly(p);  // -1 shows sign

        printf("The multiplied polynomial is:");
        printPoly(p);
        return p;
    }

Sll* appendPoly(Poly* org, Poly* a){
    return appendPoly_signed(org, a, NULL, +1);
}
Sll* appendPoly_signed(Poly* org, Poly* a, Sll* last, short sign){   //expecting `last` to be a pointer in `org`
    Sll* t = a->head;   //t is pointer in a
    while( t != NULL ){
        Sll* add = (Sll*) malloc(sizeof(Sll));
        add->coeff = (sign) * (t->coeff);     //-----------------SIGN USED HERE---------//
        add->exp = t->exp;
        add->next = NULL;

        if( org->head != NULL ){
            last->next = add;
            last = last->next;
        } else{
            org->head = add;
            last = org->head;
        }

        t = t->next;
    }
    return last;
}

void optimisePoly(Poly* p){ //slighlty better than O(N^2)

    Sll* t = p->head, * prev, * prev2 = NULL;
    Sll* old;   //will store node to be deleted

    if( !p->head )    return;
    //SORTING, similar to Bubble sort
    prev = t;
    t = t->next;
    while( t != NULL ){
        if( t->coeff == 0 ){
            old = t;
            t = t->next;
            prev->next = t;

            free(old);  //removing 0 coefficient terms
            continue;
        } else if( t->exp > prev->exp ){
            //exchanging the data (exchanging the nodes required another tmp node)
            t->exp += prev->exp;
            prev->exp = t->exp - prev->exp;
            t->exp -= prev->exp;
            t->coeff += prev->coeff;
            prev->coeff = t->coeff - prev->coeff;
            t->coeff -= prev->coeff;

            if( prev2 != NULL ){
                prev = prev2;
                t = prev;
                continue;
            }
        }
        prev2 = prev;
        prev = t;
        t = t->next;
    }

    t = p->head;
    while( t != NULL ){
        prev = t;
        Sll* t2 = t->next;
        while( t2 != NULL ){
            if( t2->exp == t->exp ){
                t->coeff += t2->coeff;

                //Remove t2 now
                old = t2;
                t2 = t2->next;
                prev->next = t2;
                free(old);
            }
            prev = t2;
            if( t2 ) t2 = t2->next;
        }
        if( t ) t = t->next;
    }
}


