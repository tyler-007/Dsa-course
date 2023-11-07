#include <stdio.h>
#include <stdlib.h>
// 4 functions for lr rr ll rl 
// ek balance ka function
struct node 
{
    int data;
    int color; // red-1 black-0
    struct node* p;
    struct node* lc;
    struct node * rc;
}
// 7 6 5 4 3 2 1 
struct node* root = NULL;

struct node* bst(struct node* trav, struct node* temp)
{
    if (trav == NULL)
    {
        return temp;
    }// checking if empty
    if (temp->data < trav->data)
    {
        trav->lc = bst(trav->lc, temp);
        trav->lc->p =trav;
    }
    else if (temp->data> trav->data)

}

void fixup(struct node* root, struct node* pt)
{
    struct node* parent_pt = NULL;
    struct node* grand_parent_pt = NULL;
    while((pt!= root) && (pt->color!=0) && (pt->p->color==1))
    {
        parent_pt=pt->p;
        grand_parent_pt= pt->p->p;
        if(parent_pt==grand_parent_pt->lc)
        {
            struct node * uncle_pt = grand_parent_pt->r;
            if(uncle_pt!=NULL && uncle_pt->color==1)
            {
                grand_parent_pt->color=1;
                parent_pt->color=0;
                uncle_pt=0;
                pt= grand_parent_pt;
            }
            else
            {
                if(pt== parent_pt->r)
                {
                    leftrotate(parent_pt);
                    pt=parent_pt;
                    parent_pt=pt->p;

                }

                rightrotate(grand_parent_pt);
                int t= parent_pt->color;
                parent_pt->color=grand_parent_pt->color;
                grand_parent_pt->color=t;
                pt=parent_pt;
            }
        }

        else 
        {
            struct node* uncle_pt=grand_parent_pt->lc;
            if((uncle_pt!=NULL)&& uncle_pt->color==1)
            {
                grand_parent_pt->color=1;
                parent_pt->color=0;
                uncle_pt->color=0;
                pt=grand_parent_pt;
            }
            else {
                if(pt== parent_pt->lc)
                {
                    rightrotate(parent_pt);
                    pt=parent_pt;
                    parent_pt=pt->p;
                }
                leftrotate(grand_parent_pt);
                int t = parent_pt->color;
                parent_pt->c= grand_parent_pt->color;
                grand_parent_pt->color=t;
                pt = parent_pt;

            }

        }
        
        
    }
}


void inorder(stuct node* trav)
{
    if(trav=NULL)
    {
        return;
    }
    inorder(trav->lc);
    printf("%d", trav->data);
    inorder(trav->rc);
}

int main()
{
    int n=7;
    int a[7]={ 7,6,5,4,3,2,1};
    for(int i=0;i<n;i++)
    {
        struct node *temp = (struct node*)malloc(sizeof(struct node));
        temp->rc= NULL;
        temp->lc= NULL;
        temp->p=NULL;
        temp->data= a[i];
        temp->color=1;

        root = bst(root, temp);
        fixup(root,temp);
        root->c=0;
    }
    printf("Inforder traversal fo created tree is\n");
    inorder(root);

    return 0;
}

