struct node {
    int data;
    struct node *next;
};

// array of linked list
struct node *radix[10];

// initializing all list head with null
void init() {
    int i;
    for (i = 0; i < 10; i++) {
        radix[i] = NULL;
    }
}

// fucntion for making a node
struct node *make_new_node(int data) {
    struct node *new_node = (struct node *)malloc(sizeof(struct node));
    new_node->next = NULL;
    new_node->data = data;
    return new_node;
}

// function for getting the maximum digit
int get_max_digit(int *arr, int n) {
    int i, max = arr[0], count = 0;
    // This loop is for finding the maximum number
    for (i = 0; i < n; i++) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    // This loop is for getting the total number digits of the maximum number
    while (max != 0) {
        max /= 10;
        count++;
    }
    return count;
}

// function for inserting the digit in the last node
void insert_into_bin(int data, int rad) {
    struct node *new_node = make_new_node(data);
    struct node *temp = radix[rad];
    if (temp == NULL) {
        temp = new_node;
    } else {
        while (temp->next!=NULL) {
            temp = temp->next;
        }
        temp->next = new_node;
    }
}

// function for radix sort
void radix_sort(int *arr, int n) {
    int i, j = 0, k, pass, digit, div = 1;
    pass = get_max_digit(arr, n);
    
    for (i = 1; i <= pass; i++) {
        printf("\ndiv = %d\n\n", div);
        for (j = 0; j < n; j++) {
            // getting the corresponding digit
            digit = (arr[j] / div) % 10;
            
            // inserting into the bin
            insert_into_bin(arr[j], digit);
        }
        // now multiplying div with 10 and storing it in div
        div *= 10;
        // Now the list is sorted in the array of linked list
        // Time to retrieve them
        j = 0;
        for (k = 0; k < 10; k++) {
            struct node *temp = radix[i];
            while (temp != NULL) {
                arr[j++] = temp->data;
            }
        }
        init();
    }
}

// function for printing the array
void display(int *arr, int n) {
    int i;
    for (i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

// driver function
int main() {
    // calling the init function
    init();
    int arr[6] = { 655, 12, 7845, 2, 45, 45122 };
    radix_sort(arr, 6);
    display(arr, 6);
    return 0;
}