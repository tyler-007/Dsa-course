#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    int exponent;
    struct node*next;
}*head1,*head2,*head3;

void input1(int degree){
    
    head1=(struct node*)malloc(sizeof(struct node));
    int d,e;
    scanf("%d %d", &d,&e);
    head1->data=d;
    head1->exponent=e;
    head1->next=NULL;
    struct node*temp=head1;
    for(int i=1;i<degree;i++){
        struct node*node;
        node=(struct node*)malloc(sizeof(struct node));
        scanf("%d %d", &d,&e);
        node->data=d;
        node->exponent=e;
        node->next=NULL;
        temp->next=node;
        temp=temp->next;

    }
}
void input2(int degree){
    
    head2=(struct node*)malloc(sizeof(struct node));
    int d,e;
    scanf("%d %d", &d,&e);
    head2->data=d;
    head2->exponent=e;
    head2->next=NULL;
    struct node*temp2=head2;
    for(int i=1;i<degree;i++){
        struct node*node2;
        node2=(struct node*)malloc(sizeof(struct node));
        scanf("%d %d", &d,&e);
        node2->data=d;
        node2->exponent=e;
        node2->next=NULL;
        temp2->next=node2;
        temp2=temp2->next;

    }
}

void display1(){
   
    struct node*p=head1;
    while((p->next)!=NULL){
        printf("(%dx^%d)+", p->data,p->exponent);
        p=p->next;
    }
    printf("(%dx^%d)", p->data,p->exponent);
    printf("\n");
    
}
void display2(){
   
    struct node*q=head2;
    while((q->next)!=NULL){
        printf("(%dx^%d)+", q->data,q->exponent);
        q=q->next;
    }
    printf("(%dx^%d)", q->data,q->exponent);
    printf("\n");
    
}

/*void push(int d , int e)
{
    
    
}*/
void multiplication() {
    struct node* ptr1 = head1;
    while (ptr1 != NULL) {
        struct node* ptr2 = head2;
        while (ptr2 != NULL) {
            int temp_coeff = ptr1->data * ptr2->data;
            int temp_deg = ptr1->exponent + ptr2->exponent;

            struct node* result_node = (struct node*)malloc(sizeof(struct node));
            result_node->data = temp_coeff;
            result_node->exponent = temp_deg;
            result_node->next = NULL;

            if (head3 == NULL) {
                head3 = result_node;
            } else {
                struct node* temp = head3;
                while (temp->next != NULL) {
                    temp = temp->next;
                }
                temp->next = result_node;
            }

            ptr2 = ptr2->next;
        }
        ptr1 = ptr1->next;
    }
}

void pop() {
    struct node* o = head3;
    while (o != NULL) {
        printf("(%dx^%d)+", o->data, o->exponent);
        o = o->next;
    }
    printf("\n");
}

void reduce(struct node* head3) {
    struct node* current = head3;
    while (current != NULL) {
        struct node* runner = current->next;
        while (runner != NULL) {
            if (runner->exponent == current->exponent) {
                current->data += runner->data; 
                struct node* temp = runner;
                runner = runner->next;
                free(temp);
            } else {
                runner = runner->next;
            }
        }
        current = current->next;
    }
}

int main()
{
    int deg1, deg2;
    printf("Enter the highest degree of the first polynomial\n");
    scanf("%d",&deg1);
    printf("Enter the highest degree of the second polynomial\n");
    scanf("%d",&deg2);
    printf("enter the 1st polynomial: \n");
    input1(deg1);
    printf("enter the 2nd polynomial: \n");
    input2(deg2);
    display1();
    display2();
    printf("values inputed successfully, now mupltiplying the polynomials\n");
    multiplication();
    printf("multiplication carried out successfully now printing the result\n");
    pop();
    printf("after reduction :- \n");
    reduce(head3);
    pop();



}
