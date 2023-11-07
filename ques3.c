#include <stdio.h>
#include <stdlib.h>
#include <math.h>


typedef struct Term {
    float a;
    int b[3];
    struct Term* next;
} Term;


typedef struct Polynomial {
    int max_exp[3];
    Term* head;
} Polynomial;


Polynomial* Aread() {
    Polynomial* A = (Polynomial*)malloc(sizeof(Polynomial));
    A->head = (Term*)malloc(sizeof(Term));
    A->head->next = A->head;
    for (int i = 0; i < 3; ++i) {
        A->max_exp[i] = 0;
    }


    int n_terms;
    scanf("%d", &n_terms);


    Term* ptr1 = A->head;
    for (int i = 0; i < n_terms; ++i) {
        Term* ptr2 = (Term*)malloc(sizeof(Term));
        scanf("%f %d %d %d", &ptr2->a, &ptr2->b[0], &ptr2->b[1], &ptr2->b[2]);


        ptr1->next = ptr2;
        ptr2->next = A->head;
        ptr1 = ptr2;


        for (int j = 0; j < 3; ++j) {
            if (ptr2->b[j] > A->max_exp[j]) {
                A->max_exp[j] = ptr2->b[j];
            }
        }
    }


    return A;
}


Polynomial* Padd(Polynomial* ptry, Polynomial* ptrW) {
    Polynomial* ptr3 = (Polynomial*)malloc(sizeof(Polynomial));
    ptr3->head = (Term*)malloc(sizeof(Term));
    ptr3->head->next = ptr3->head;
    for (int i = 0; i < 3; ++i) {
        ptr3->max_exp[i] = 0;
    }


    Term* ptrz = ptry->head->next;
    Term* ptr2 = ptrW->head->next;
    Term* ptr1 = ptr3->head;


    while (ptrz != ptry->head || ptr2 != ptrW->head) {
        Term* term = (Term*)malloc(sizeof(Term));
        term->next = ptr3->head;


        int comparison = 0;
        for (int i = 0; i < 3; ++i) {
            if (ptrz->b[i] > ptr2->b[i]) {
                comparison = 1;
                break;
            } else if (ptrz->b[i] < ptr2->b[i]) {
                comparison = -1;
                break;
            }
        }


        if (comparison == 1) {
            term->a = ptrz->a;
            for (int i = 0; i < 3; ++i) {
                term->b[i] = ptrz->b[i];
            }
            ptrz = ptrz->next;
        } else if (comparison == -1) {
            term->a = ptr2->a;
            for (int i = 0; i < 3; ++i) {
                term->b[i] = ptr2->b[i];
            }
            ptr2 = ptr2->next;
        } else {
            term->a = ptrz->a + ptr2->a;
            for (int i = 0; i < 3; ++i) {
                term->b[i] = ptrz->b[i];
            }
            ptrz = ptrz->next;
            ptr2 = ptr2->next;
        }


        ptr1->next = term;
        ptr1 = term;


        for (int i = 0; i < 3; ++i) {
            if (term->b[i] > ptr3->max_exp[i]) {
                ptr3->max_exp[i] = term->b[i];
            }
        }
    }


    return ptr3;
}


Polynomial* Psub(Polynomial* ptry, Polynomial* ptrW) {
    Polynomial* ptr3 = (Polynomial*)malloc(sizeof(Polynomial));
    ptr3->head = (Term*)malloc(sizeof(Term));
    ptr3->head->next = ptr3->head;
    for (int i = 0; i < 3; ++i) {
        ptr3->max_exp[i] = 0;
    }


    Term* ptrz = ptry->head->next;
    Term* ptr2 = ptrW->head->next;
    Term* ptr1 = ptr3->head;


    while (ptrz != ptry->head || ptr2 != ptrW->head) {
        Term* term = (Term*)malloc(sizeof(Term));
        term->next = ptr3->head;


        int comparison = 0;
        for (int i = 0; i < 3; ++i) {
            if (ptrz->b[i] > ptr2->b[i]) {
                comparison = 1;
                break;
            } else if (ptrz->b[i] < ptr2->b[i]) {
                comparison = -1;
                break;
            }
        }


        if (comparison == 1) {
            term->a = ptrz->a;
            for (int i = 0; i < 3; ++i) {
                term->b[i] = ptrz->b[i];
            }
            ptrz = ptrz->next;
        } else if (comparison == -1) {
            term->a = -ptr2->a;
            for (int i = 0; i < 3; ++i) {
                term->b[i] = ptr2->b[i];
            }
            ptr2 = ptr2->next;
        } else {
            term->a = ptrz->a - ptr2->a;
            for (int i = 0; i < 3; ++i) {
                term->b[i] = ptrz->b[i];
            }
            ptrz = ptrz->next;
            ptr2 = ptr2->next;
        }


        ptr1->next = term;
        ptr1 = term;


        for (int i = 0; i < 3; ++i) {
            if (term->b[i] > ptr3->max_exp[i]) {
                ptr3->max_exp[i] = term->b[i];
            }
        }
    }


    return ptr3;
}


Polynomial* Pmult(Polynomial* ptry, Polynomial* ptrW) {
    Polynomial* ptr3 = (Polynomial*)malloc(sizeof(Polynomial));
    ptr3->head = (Term*)malloc(sizeof(Term));
    ptr3->head->next = ptr3->head;
    for (int i = 0; i < 3; ++i) {
        ptr3->max_exp[i] = 0;
    }


    Term* ptrz = ptry->head->next;


    while (ptrz != ptry->head) {
        Term* ptr2 = ptrW->head->next;
        while (ptr2 != ptrW->head) {
            Term* term = (Term*)malloc(sizeof(Term));
            term->next = ptr3->head;
            term->a = ptrz->a * ptr2->a;


            for (int i = 0; i < 3; ++i) {
                term->b[i] = ptrz->b[i] + ptr2->b[i];
            }


            Term* ptr1 = ptr3->head;
            while (ptr1->next != ptr3->head && compare_exponents(ptr1->next->b, term->b) > 0) {
                ptr1 = ptr1->next;
            }


            term->next = ptr1->next;
            ptr1->next = term;


            for (int i = 0; i < 3; ++i) {
                if (term->b[i] > ptr3->max_exp[i]) {
                    ptr3->max_exp[i] = term->b[i];
                }
            }


            ptr2 = ptr2->next;
        }
        ptrz = ptrz->next;
    }


    return ptr3;
}


int compare_exponents(int* exp1, int* exp2) {
    for (int i = 2; i >= 0; --i) {
        if (exp1[i] > exp2[i]) {
            return 1;
        } else if (exp1[i] < exp2[i]) {
            return -1;
        }
    }
    return 0;
}


void Pwrite(Polynomial* A) {
    Term* ptrz = A->head->next;
    if (ptrz == A->head) {
        printf("0");
    } else {
        while (ptrz != A->head) {
            printf("%.2f", ptrz->a);
            for (int i = 0; i < 3; ++i) {
                if (ptrz->b[i] != 0) {
                    printf("x%d^%d", i + 1, ptrz->b[i]);
                }
            }
            ptrz = ptrz->next;
            if (ptrz != A->head) {
                printf(" + ");
            }
        }
    }
    printf("\n");
}


float Zeval(Polynomial* A, float x, float y, float z) {
    float result = 0.0;
    Term* ptr2 = A->head->next;


    while (ptr2 != A->head) {
        result += ptr2->a * pow(x, ptr2->b[0]) * pow(y, ptr2->b[1]) * pow(z, ptr2->b[2]);
        ptr2 = ptr2->next;
    }


    return result;
}


void Perase(Polynomial* A, int b[3]) {
    Term* ptrz = A->head->next;
    Term* ptr2 = A->head;


    while (ptrz != A->head) {
        int compare = compare_exponents(ptrz->b, b);


        if (compare == 0) {
            ptr2->next = ptrz->next;
            free(ptrz);
            ptrz = ptr2->next;
        } else {
            ptr2 = ptrz;
            ptrz = ptrz->next;
        }
    }
}


int main() {
    Polynomial* ptry = Aread();
    Polynomial* ptrW = Aread();


    Polynomial* tot = Padd(ptry, ptrW);
    Polynomial* diff = Psub(ptry, ptrW);
    Polynomial* prod = Pmult(ptry, ptrW);


    float x, y, z;
    scanf("%f %f %f", &x, &y, &z);


    int b[3];
    Perase(ptry, b);
    Perase(ptrW, b);


    free_polynomial(ptry);
    free_polynomial(ptrW);
    free_polynomial(tot);
    free_polynomial(diff);
    free_polynomial(prod);


    return 0;
}


void free_polynomial(Polynomial* p) {
    Term* ptr1 = p->head->next;
    while (ptr1 != p->head) {
        Term* ptr2 = ptr1;
        ptr1 = ptr1->next;
        free(ptr2);
    }
    free(p->head);
    free(p);
}
