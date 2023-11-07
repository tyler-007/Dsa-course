/*
 Design and build a linked list allocation system to represent and manipulate polynomials. Use circular linked list with header nodes. Eachterm of the polynomial will be represented in a linked list node structure as shown:
Write and test the following funstions:
(a) Pread(): Read a polynomial and convert it to its circular representaion. Return a pointer to the header node of this polynomial.
(b) Pwrite(): Output the polynomial in its mathematical form.
(c) Padd(): Compute c=a+b. Do not change polynomials a and b.
(d) Psub(): Compute c=a-b. Do not change polynomials a and b.
(e) Pmult(): Compute c=a*b. Do not change polynomials a and b.
(f) Peval(): Evaluate the polynomials at some point a, where a is a floating point constant.
(g) Pearse(): Earse a certain term of the polynomial. (circular linked list helps in this operatio
*/

#include<stdio.h>
#include<stdlib.h>

struct node
{
    int data;
    int exponent;
    struct node * next;

}*head1,*head2,*head3;

void insert(struct node** poly, int data, int exponent) {
    struct node* temp = (struct node*) malloc(sizeof(struct node));
    temp->data = data;
    temp->exponent = exponent;
    temp->next = NULL;
    
    if (*poly == NULL) {
        *poly = temp;
        return;
    }
    
    struct node* current = *poly;
    
    while (current->next != NULL) {
        current = current->next;
    }
    
    current->next = temp;
}

void Pwrite(struct node *h)
{
 do
 {
 printf("%dx^%d + \t",h->data,h->exponent);
 h=h->next;
 }while(h!=head1);
 printf("\n");
}

void displayPolynomial(struct node* head) {
    struct node* current = head;
    while (current != NULL) {
        printf("(%dx^%d) ", current->data, current->exponent);
        current = current->next;
        if (current != NULL) {
            printf("+ ");
        }
    }
    printf("\n");
}


void padd(struct node* head1, struct node* head2, struct node** head3) {
    struct node* poly1 = head1;
    struct node* poly2 = head2;
    struct node* result = NULL;
    
    while (poly1 != NULL && poly2 != NULL) {
        if (poly1->exponent == poly2->exponent) {
            insert(&result, poly1->data + poly2->data, poly1->exponent);
            poly1 = poly1->next;
            poly2 = poly2->next;
        } else if (poly1->exponent > poly2->exponent) {
            insert(&result, poly1->data, poly1->exponent);
            poly1 = poly1->next;
        } else {
            insert(&result, poly2->data, poly2->exponent);
            poly2 = poly2->next;
        }
    }
    
    while (poly1 != NULL) {
        insert(&result, poly1->data, poly1->exponent);
        poly1 = poly1->next;
    }
    
    while (poly2 != NULL) {
        insert(&result, poly2->data, poly2->exponent);
        poly2 = poly2->next;
    }
    Pwrite(result);
}



void Pread2(int deg)
{
    head2=(struct node*)malloc(sizeof(struct node));
    int d,e;
    struct node * last2;
    scanf("%d %d", &d,&e);
    head2->data=d;
    head2->exponent=e;
    head2->next=head2;
    last2=head1;
    for(int i=1;i<deg;i++){
        struct node*node2;
        node2=(struct node*)malloc(sizeof(struct node));
        scanf("%d %d", &d,&e);
        node2->data=d;
        node2->exponent=e;
        node2->next=last2->next;
        last2->next=node2;
        last2=node2;
    }
    Pwrite(head2);
    
}

void Pread(int deg)
{
    head1=(struct node*)malloc(sizeof(struct node));
    int d,e;
    struct node * last;
    scanf("%d %d", &d,&e);
    head1->data=d;
    head1->exponent=e;
    head1->next=head1;
    last=head1;
    for(int i=1;i<deg;i++){
        struct node*node;
        node=(struct node*)malloc(sizeof(struct node));
        scanf("%d %d", &d,&e);
        node->data=d;
        node->exponent=e;
        node->next=last->next;
        last->next=node;
        last=node;
    }
    Pwrite(head1);
    
}


int main()
{
    int degree, degree2;
    int expo,coeff;
    int choice;
    scanf("%d",&degree);
    Pread(degree);
    printf("1. Read 3. add  4. sub  5. mul 6. eval 7. Erase");
    scanf("%d",&choice);
    switch (choice) {
        case 1:
            
            printf("You chose Read. enter degree \n");
            break;
        case 3:
            printf("You chose Add.\n");
            printf("Enter another degreee");
            scanf("%d",&degree2);
            Pread2(degree2);
            padd(head1,head2,&head3);

            break;
        case 4:
            printf("You chose Subtract.\n");
            printf("Enter another degreee");
            scanf("%d",&degree2);
            break;
        case 5:
            printf("You chose Multiply.\n");
            printf("Enter another degreee");
            scanf("%d",&degree2);
            break;
        case 6:
            printf("You chose Evaluate.\n");
            printf("couldn't be solved");
            break;
        case 7:
            printf("You chose Erase.\n");
            printf("enter polynomial term to be removed");
            scanf("%d%d",&coeff, &expo);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }
    
}

/*
Polynomial* Padd(Polynomial* jig, Polynomial* shree) {
    Polynomial* ant = (Polynomial*)malloc(sizeof(Polynomial));
    ant->head = (Term*)malloc(sizeof(Term));
    ant->head->next = ant->head;
    ant->max_exp = 0;


    Term* sim = jig->head->next;
    Term* ash = shree->head->next;
    Term* tashu = ant->head;


    while (sim != jig->head || ash != shree->head) {
        Term* term = (Term*)malloc(sizeof(Term));
        term->next = ant->head;


        if (sim->b > ash->b) {
            term->a = sim->a;
            term->b = sim->b;
            sim = sim->next;
        } else if (ash->b > sim->b) {
            term->a = ash->a;
            term->b = ash->b;
            ash = ash->next;
        } else {
            term->a = sim->a + ash->a;
            term->b = sim->b;
            sim = sim->next;
            ash = ash->next;
        }


        tashu->next = term;
        tashu = term;


        if (term->b > ant->max_exp) {
            ant->max_exp = term->b;
        }
    }


    return ant;
}


Polynomial* Psub(Polynomial* jig, Polynomial* shree) {
    Polynomial* ant = (Polynomial*)malloc(sizeof(Polynomial));
    ant->head = (Term*)malloc(sizeof(Term));
    ant->head->next = ant->head;
    ant->max_exp = 0;


    Term* sim = jig->head->next;
    Term* ash = shree->head->next;
    Term* tashu = ant->head;


    while (sim != jig->head || ash != shree->head) {
        Term* term = (Term*)malloc(sizeof(Term));
        term->next = ant->head;


        if (sim->b > ash->b) {
            term->a = sim->a;
            term->b = sim->b;
            sim = sim->next;
        } else if (ash->b > sim->b) {
            term->a = -ash->a;
            term->b = ash->b;
            ash = ash->next;
        } else {
            term->a = sim->a - ash->a;
            term->b = sim->b;
            sim = sim->next;
            ash = ash->next;
        }


        tashu->next = term;
        tashu = term;


        if (term->b > ant->max_exp) {
            ant->max_exp = term->b;
        }
    }


    return ant;
}
*/