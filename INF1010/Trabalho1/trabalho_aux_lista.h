//structed data

// Definition of the structure of a list nO
typedef struct NO {
    int value;
    struct NO *next;
} NO;

//function prototypes
void insertSorted(NO **head, int value);
NO *interleaveLists(NO *list1, NO *list2);
void printList(NO *head);