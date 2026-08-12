#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int data;
    struct Node *next;
};

struct Node *insertNode(struct Node *head, int data)
{
    struct Node *newNode;
    struct Node *temp;

    newNode = (struct Node *)malloc(sizeof(struct Node));

    newNode->data = data;
    newNode->next = NULL;

    if (head == NULL)
        return newNode;

    temp = head;

    while (temp->next != NULL)
        temp = temp->next;

    temp->next = newNode;

    return head;
}

struct Node *createList(int n)
{
    struct Node *head = NULL;
    int data;

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &data);
        head = insertNode(head, data);
    }

    return head;
}

void displayList(struct Node *head)
{
    struct Node *temp = head;

    while (temp != NULL)
    {
        printf("%d", temp->data);

        if (temp->next != NULL)
            printf(" -> ");

        temp = temp->next;
    }

    printf("\n");
}

void splitList(struct Node *source,
               struct Node **front,
               struct Node **back)
{
    struct Node *slow;
    struct Node *fast;

    if (source == NULL || source->next == NULL)
    {
        *front = source;
        *back = NULL;
        return;
    }

    slow = source;
    fast = source->next;

    while (fast != NULL)
    {
        fast = fast->next;

        if (fast != NULL)
        {
            slow = slow->next;
            fast = fast->next;
        }
    }

    *front = source;
    *back = slow->next;

    slow->next = NULL;
}

struct Node *mergeLists(struct Node *a, struct Node *b)
{
    struct Node *result = NULL;

    if (a == NULL)
        return b;

    if (b == NULL)
        return a;

    if (a->data <= b->data)
    {
        result = a;
        result->next = mergeLists(a->next, b);
    }
    else
    {
        result = b;
        result->next = mergeLists(a, b->next);
    }

    return result;
}

void mergeSort(struct Node **headRef)
{
    struct Node *head = *headRef;
    struct Node *front;
    struct Node *back;

    if (head == NULL || head->next == NULL)
        return;

    splitList(head, &front, &back);

    mergeSort(&front);
    mergeSort(&back);

    *headRef = mergeLists(front, back);
}

int main()
{
    int n;
    struct Node *head;

    printf("Enter number of elements: ");
    scanf("%d", &n);

    printf("Enter elements:\n");

    head = createList(n);

    printf("\nOriginal List\n");
    displayList(head);

    mergeSort(&head);

    printf("\nSorted List\n");
    displayList(head);

    return 0;
}
