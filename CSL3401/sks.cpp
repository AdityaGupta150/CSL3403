#include<stdio.h>
#include<conio.h>
#include<malloc.h>

// node containing two data coefficient and exponent
typedef struct sllp sllp;
struct sllp
{
    int cf;
    int dg;
    sllp* next;
};

sllp* pl1 = NULL;
sllp* pl2 = NULL;
sllp* plm = NULL;

sllp* makePl(int n){
    char c;
    sllp* head = NULL, * node;
    while( n-- ){
        if( head == NULL ){
            head = (sllp*) malloc(sizeof(sllp));
            node = head;
        } else{
            node->next = (sllp*) malloc(sizeof(sllp));
            node = node->next;
        }
        printf("\n\n Enter the coefficient of term...:");
        scanf("%d", &node->cf);
        printf("\n Enter the exponent of term...:");
        scanf("%d", &node->dg);
        node->next = NULL;
    }
    return head;
}

void showPoly(sllp* node){
    while( node != NULL ){
        printf("%dx^%d", node->cf, node->dg);
        if( node->next != NULL ){
            printf(" + ");
        }
        node = node->next;
    }
    printf("\n");
}

sllp* addpol(sllp* pl1, sllp* pl2){
    sllp* head = NULL, * node = head, * prev;

    sllp* n1 = pl1;
    sllp* n2 = pl2;
    while( n1 != NULL ){
        if( head == NULL ){
            head = (sllp*) malloc(sizeof(sllp));
            node = head;
            prev = head;
            node->next = NULL;
        } else{
            prev->next = (sllp*) malloc(sizeof(sllp));
            node = prev->next;
            node->next = NULL;
        }
        node->cf = n1->cf;
        node->dg = n1->dg;
        prev = node;
        node = node->next;
        n1 = n1->next;
    }
    while( n2 != NULL ){
        prev->next = (sllp*) malloc(sizeof(sllp));
        node = prev->next;
        node->next = NULL;
        node->cf = n2->cf;
        node->dg = n2->dg;
        prev = node;
        n2 = n2->next;
    }
    node = head;
    while( node != NULL ){
        sllp* node2 = node->next, * prev = node;
        while( node2 != NULL ){
            if( node->dg == node2->dg ){
                node->cf += node2->cf;
                prev->next = node2->next;
            }
            prev = node2;
            node2 = node2->next;
        }
        node = node->next;
    }

    return head;
}

sllp* subpol(sllp* pl1, sllp* pl2){
    sllp* head = NULL, * node = head, * prev;

    sllp* n1 = pl1;
    sllp* n2 = pl2;
    while( n1 != NULL ){
        if( head == NULL ){
            head = (sllp*) malloc(sizeof(sllp));
            node = head;
            prev = head;
            node->next = NULL;
        } else{
            prev->next = (sllp*) malloc(sizeof(sllp));
            node = prev->next;
            node->next = NULL;
        }
        node->cf = n1->cf;
        node->dg = n1->dg;
        prev = node;
        node = node->next;
        n1 = n1->next;
    }
    while( n2 != NULL ){
        prev->next = (sllp*) malloc(sizeof(sllp));
        node = prev->next;
        node->next = NULL;
        node->cf = -(n2->cf);
        node->dg = n2->dg;
        prev = node;
        n2 = n2->next;
    }
    node = head;
    while( node != NULL ){
        sllp* node2 = node->next, * prev = node;
        while( node2 != NULL ){
            if( node->dg == node2->dg ){
                node->cf += node2->cf;
                prev->next = node2->next;
            }
            prev = node2;
            node2 = node2->next;
        }
        node = node->next;
    }

    return head;
}

sllp* mulpol(sllp* pl1, sllp* pl2){
    sllp* head = NULL, * node = head;

    // Logic here, add to head

    return head;
}

int main(){
    unsigned select;
    char c; int n;

    printf("\n\nEnter number of terms in first polynomial, then polynomial -> ");
    scanf("%d", &n);
    pl1 = makePl(n);
    printf("\n\nEnter number of terms in second polynomial, then polynomial -> ");
    scanf("%d", &n);
    pl2 = makePl(n);
    printf("\nFirst Polynomial: \t");
    showPoly(pl1);
    printf("\nSecond Polynomial: \t");
    showPoly(pl2);
    plm = addpol(pl1, pl2);
    printf("\n Result of Addition: \t");
    showPoly(plm);
    plm = subpol(pl1, pl2);
    printf("\n Result of Subtraction:\t");
    showPoly(plm);
    plm = mulpol(pl1, pl2);
    printf("\n Result of Multiplication:\t");
    showPoly(plm);

    return 0;
}
