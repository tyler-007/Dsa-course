#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int row;
    int column;
    int value;
    struct node *next;
} node;
void insert(struct node **head, int row, int col, int val)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->row = row;
    new_node->column = col;
    new_node->value = val;
    new_node->next = NULL;
    if ((*head) == NULL || row < (*head)->row || (row == (*head)->row && col < (*head)->column))
    {
        new_node->next = (*head);
        (*head) = new_node;
    }
    else
    {
        struct node *current = (*head);
        while (current->next && (row > current->next->row || (row == current->next->row && col >= current->next->column)))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
void printmatrix(node **head, int n, int m)
{
    printf("Sparse Matrix is:\n");
    node *current = *head;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (current && current->row == i && current->column == j)
            {
                printf("%d ", current->value);
                current = current->next;
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
void freeList(node *head)
{
    while (head)
    {
        node *temp = head;
        head = head->next;
        free(temp);
    }
}
int main()
{
    node *head = NULL;
    int n, m;
    printf("Enter the Dimension of Matrix N X M: ");
    scanf("%d %d", &n, &m);
    int x;
    printf("How many Non-zero elements to enter: ");
    scanf("%d", &x);
    if ((x % 2) == 0 && x < (n * m) / 2)
    {
        for (int i = 1; i <= x; i++)
        {
            printf("Enter the Row , Column and Value: ");
            int r, c, val;
            scanf("%d %d %d", &r, &c, &val);
            insert(&head, r, c, val);
        }
        printmatrix(&head, n, m);
    }
    else if ((x % 2) == 1 && x <= (n * m) / 2)
    {
        for (int i = 1; i <= x; i++)
        {
            printf("Enter the Row , Column and Value: ");
            int r, c, val;
            scanf("%d %d %d", &r, &c, &val);
            insert(&head, r, c, val);
        }
        printmatrix(&head, n, m);
    }
    else
    {
        printf("You cannot enter %d elements in %d x %d sparse matrix.", x, n, m);
    }
    freeList(head);
}

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int num;
    struct node *next;
} node;
void insert(node **head, int a)
{
    node *newele = (node *)malloc(sizeof(node));
    newele->num = a;
    newele->next = NULL;
    newele->next = *head;
    *head = newele;
}
void sum(node **new, node **head1, node **head2)
{
    node *temp1 = *head1, *temp2 = *head2;
    int carry = 0;
    while (temp1 != NULL || temp2 != NULL)
    {
        if (temp1 != NULL && temp2 != NULL)
        {
            insert(new, (temp1->num + temp2->num + carry) % 10);
            if (temp1->num + temp2->num + carry > 9)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1 != NULL)
        {
            insert(new, temp1->num + carry);
            if (temp1->num + carry > 9)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            temp1 = temp1->next;
        }
        else if (temp2 != NULL)
        {
            insert(new, temp2->num + carry);
            if (temp2->num + carry > 9)
            {
                carry = 1;
            }
            else
            {
                carry = 0;
            }
            temp2 = temp2->next;
        }
        if (carry == 1 && temp1 == NULL && temp2 == NULL)
        {
            insert(new, carry);
        }
    }
}
int ascii(char c)
{
    int x;
    x = c - '0';
    return x;
}
void printlist(node **head)
{
    node *temp = *head;
    while (temp != NULL)
    {
        printf("%d", temp->num);
        temp = temp->next;
    }
}
void input(node **head)
{
    char a[100];
    scanf("%[^\n]s", a);
    int i = 0;
    while (a[i] != '\0')
    {
        insert(head, ascii(a[i]));
        i = i + 1;
    }
}
int main()
{
    node *num1 = NULL;
    node *num2 = NULL;
    node *result = NULL;
    printf("Enter Number 1: ");
    fflush(stdin);
    input(&num1);
    printf("\n");
    printf("Enter Number 2: ");
    fflush(stdin);
    input(&num2);
    sum(&result, &num1, &num2);
    printf("\nSUM = ");
    printlist(&result);
}

#include <stdio.h>
#include <stdlib.h>
typedef struct node
{
    int row;
    int column;
    int value;
    struct node *next;
} node;
void insert(struct node **head, int row, int col, int val)
{
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->row = row;
    new_node->column = col;
    new_node->value = val;
    new_node->next = NULL;
    if ((*head) == NULL || row < (*head)->row || (row == (*head)->row && col < (*head)->column))
    {
        new_node->next = (*head);
        (*head) = new_node;
    }
    else
    {
        struct node *current = (*head);
        while (current->next && (row > current->next->row || (row == current->next->row && col >= current->next->column)))
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }
}
void printmatrix(node **head, int n, int m)
{
    printf("Matrix is:\n");
    node *current = *head;

    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= m; j++)
        {
            if (current && current->row == i && current->column == j)
            {
                printf("%d ", current->value);
                current = current->next;
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
}
void freeList(node *head)
{
    while (head)
    {
        node *temp = head;
        head = head->next;
        free(temp);
    }
}
void input(node **head,int n,int m){
    int x;
    printf("How many Non-zero elements to enter: ");
    scanf("%d", &x);
    if ((x % 2) == 0 && x < (n * m) / 2)
    {
        for (int i = 1; i <= x; i++)
        {
            printf("Enter the Row , Column and Value: ");
            int r, c, val;
            scanf("%d %d %d", &r, &c, &val);
            insert(head, r, c, val);
        }
    }
    else if ((x % 2) == 1 && x <= (n * m) / 2)
    {
        for (int i = 1; i <= x; i++)
        {
            printf("Enter the Row , Column and Value: ");
            int r, c, val;
            scanf("%d %d %d", &r, &c, &val);
            insert(head, r, c, val);
        }
    }
    else
    {
        printf("You cannot enter %d elements in %d x %d sparse matrix.", x, n, m);
        freeList(*head);
        exit(1);
    }
}
void add(node **result ,node **head1, node **head2,int n , int m){
    node *temp1 = *head1,*temp2 = *head2;
    while(temp1 || temp2){
            if(temp1 && temp1->row == temp2->row && temp1->column == temp2->column){
                insert(result,temp1->row,temp1->column,temp1->value + temp2->value);
                temp1=temp1->next;
                temp2=temp2->next;
            }
            else if(temp1){
                insert(result,temp1->row,temp1->column,temp1->value);
                temp1 = temp1->next;
            }
            else if(temp2){
                insert(result,temp2->row,temp2->column,temp2->value);
                temp2 = temp2->next;
            }
    }
}
int main()
{
    node *head1 = NULL,*head2 = NULL,*result=NULL;
    int n1, m1, n2, m2;
    printf("Enter the Dimension of Matrix 1 N X M: ");
    scanf("%d %d", &n1, &m1);
    input(&head1,n1,m1);
    printmatrix(&head1, n1, m1);    
    printf("Enter the Dimension of Matrix 2 N X M: ");
    scanf("%d %d", &n2, &m2);
    input(&head2,n2,m2);
    printmatrix(&head2, n2, m2); 
    if(n1 == n2 && m1 == m2){  
        add(&result,&head1,&head2,n1,m1);
        printf("\nAddition:\n");
        printmatrix(&result,n1,m1);
        freeList(result);
        freeList(head1);
        freeList(head2);
    }
    else{
        printf("Can't Add both the matrix should be of same dimension.");
        freeList(result);
        freeList(head1);
        freeList(head2);
    }
}  


#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node
{
    int r;
    int c;
    int data;
    struct node *next;
}*newn;

void create(struct node *head,int n)
{
    int i;
    int rm=INT_MIN;
    int cm=INT_MIN;
    struct node *t;
    for (i = 1; i <= n; i++)
    {
        newn = (struct node *)malloc(sizeof(struct node));
        newn->next = NULL;
        printf("Enter the row number of term \n");
        scanf("%d", &newn->r);
        printf("Enter the column number of term \n");
        scanf("%d", &newn->c);
        printf("Enter the data of term \n");
        scanf("%d", &newn->data);
        if(newn->r>rm)
        rm=newn->r;
        if(newn->c>cm)
        cm=newn->c;
        if (i == 1)
        {
            head = newn;
            t = newn;
        }
        else
        {
            t->next = newn;
            t = newn;
        }
    }
    display(head,cm,rm);
}

void display(struct node *head, int rm, int cm)
{
    struct node *tmp = head;
    printf("\n");
    printf("transpose matrix \n");
    for(int i=1;i<=rm;i++)
    {
        for(int j=1;j<=cm;j++)
        {
            if(i==tmp->r && j==tmp->c)
            {
                printf("%d ",tmp->data);
                if(tmp->next!=NULL)
                {
                    tmp=tmp->next;
                }
            }
            else
            {
                printf("0 ");
            }
        }
        printf("\n");
    }
    printf("\n\n");
}

int main()
{
    int n;
    struct node *head;
    printf("Enter number of non-zero terms in matrix \n");
    scanf("%d", &n);
    create(head,n);
}

