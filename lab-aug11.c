#include<stdio.h>
#include<stdlib.h>

struct node{
    int data;
    int exponent;
    struct node*next;
}*head;

void input(int degree){
    
    head=(struct node*)malloc(sizeof(struct node));
    int d,e;
    scanf("%d %d", &d,&e);
    head->data=d;
    head->exponent=e;
    head->next=NULL;
    struct node*temp=head;
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
void display(){
   
    struct node*p=head;
    while((p->next)!=NULL){
        printf("(%dx^%d)+", p->data,p->exponent);
        p=p->next;
    }
    printf("(%dx^%d)+", p->data,p->exponent);
    
}

void sort(){
    struct node*p=head,*q;
    while((p->next)!=NULL){
        q=p->next;
        while(q!=NULL){
            if((p->exponent)<(q->exponent)){
                int temp=p->data;
                p->data=q->data;
                q->data=temp;
                temp=p->exponent;
                p->exponent=q->exponent;
                q->exponent=temp;

            }
            q=q->next;
        }
    }
}

int main(){
    int degree;
    printf("Enter the degree of ")
    scanf("%d",&degree);
    input(degree);
    //display();
}

