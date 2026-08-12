#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int disk;
    struct Node *next;
} Node;

typedef struct Stack
{
    Node *top;
} Stack;

Stack *createStack()
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));

    if (stack == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    stack->top = NULL;
    return stack;
}

void push(Stack *stack, int disk)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("Memory allocation failed\n");
        exit(1);
    }

    newNode->disk = disk;
    newNode->next = stack->top;
    stack->top = newNode;
}

int pop(Stack *stack)
{
    if (stack->top == NULL)
        return -1;

    Node *temp = stack->top;
    int disk = temp->disk;

    stack->top = stack->top->next;
    free(temp);

    return disk;
}

int peek(Stack *stack)
{
    if (stack->top == NULL)
        return -1;

    return stack->top->disk;
}

void displayStack(Stack *stack)
{
    Node *temp = stack->top;

    while (temp != NULL)
    {
        printf("%d ", temp->disk);
        temp = temp->next;
    }

    printf("\n");
}

void displayAll(Stack *A, Stack *B, Stack *C)
{
    printf("A : ");
    displayStack(A);

    printf("B : ");
    displayStack(B);

    printf("C : ");
    displayStack(C);

    printf("\n");
}

void moveDisk(Stack *source, Stack *destination,
              char sourceName, char destinationName,
              Stack *A, Stack *B, Stack *C)
{
    int disk = pop(source);

    push(destination, disk);

    printf("Move Disk %d from %c to %c\n\n",
           disk, sourceName, destinationName);

    displayAll(A, B, C);
}

void towerOfHanoi(int n,
                  Stack *source, Stack *auxiliary, Stack *destination,
                  char sourceName, char auxiliaryName, char destinationName,
                  Stack *A, Stack *B, Stack *C)
{
    if (n == 1)
    {
        moveDisk(source, destination,
                 sourceName, destinationName,
                 A, B, C);
        return;
    }

    towerOfHanoi(n - 1,
                 source, destination, auxiliary,
                 sourceName, destinationName, auxiliaryName,
                 A, B, C);

    moveDisk(source, destination,
             sourceName, destinationName,
             A, B, C);

    towerOfHanoi(n - 1,
                 auxiliary, source, destination,
                 auxiliaryName, sourceName, destinationName,
                 A, B, C);
}

int main()
{
    int n;

    printf("Enter number of disks: ");
    scanf("%d", &n);

    if (n <= 0)
    {
        printf("Invalid number of disks\n");
        return 0;
    }

    Stack *A = createStack();
    Stack *B = createStack();
    Stack *C = createStack();

    for (int i = n; i >= 1; i--)
    {
        push(A, i);
    }

    printf("\nInitial\n\n");
    displayAll(A, B, C);

    towerOfHanoi(n,
                 A, B, C,
                 'A', 'B', 'C',
                 A, B, C);

    return 0;
}
