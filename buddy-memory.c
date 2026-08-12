#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TOTAL_MEMORY 1024
#define MIN_BLOCK 1
#define MAX_BLOCKS 1024

typedef struct
{
    int start;
    int size;
    int free;
    char process[20];
} Block;

Block blocks[MAX_BLOCKS];
int blockCount;

void initializeMemory()
{
    blockCount = 1;

    blocks[0].start = 0;
    blocks[0].size = TOTAL_MEMORY;
    blocks[0].free = 1;
    blocks[0].process[0] = '\0';
}

int nextPowerOfTwo(int size)
{
    int power = 1;

    while (power < size)
        power *= 2;

    return power;
}

void splitBlock(int index)
{
    int half = blocks[index].size / 2;
    int start = blocks[index].start;

    for (int i = blockCount; i > index + 1; i--)
        blocks[i] = blocks[i - 1];

    blocks[index].size = half;
    blocks[index].free = 1;
    blocks[index].process[0] = '\0';

    blocks[index + 1].start = start + half;
    blocks[index + 1].size = half;
    blocks[index + 1].free = 1;
    blocks[index + 1].process[0] = '\0';

    blockCount += 1;
}

void allocateMemory()
{
    char process[20];
    int requestedSize;
    int requiredSize;

    printf("Enter Process ID: ");
    scanf("%19s", process);

    printf("Enter Size (KB): ");
    scanf("%d", &requestedSize);

    requiredSize = nextPowerOfTwo(requestedSize);

    if (requiredSize > TOTAL_MEMORY)
    {
        printf("Allocation failed\n");
        return;
    }

    int index = -1;

    while (1)
    {
        index = -1;

        for (int i = 0; i < blockCount; i++)
        {
            if (blocks[i].free &&
                blocks[i].size >= requiredSize)
            {
                if (index == -1 ||
                    blocks[i].size < blocks[index].size)
                {
                    index = i;
                }
            }
        }

        if (index == -1)
        {
            printf("Allocation failed\n");
            return;
        }

        if (blocks[index].size == requiredSize)
            break;

        splitBlock(index);
    }

    blocks[index].free = 0;

    int i = 0;

    while (process[i] != '\0' && i < 19)
    {
        blocks[index].process[i] = process[i];
        i++;
    }

    blocks[index].process[i] = '\0';

    printf("Allocated %d KB for %s\n",
           blocks[index].size,
           blocks[index].process);

    if (requiredSize > requestedSize)
    {
        printf("Internal Fragmentation = %d KB\n",
               requiredSize - requestedSize);
    }
}

void mergeBuddy()
{
    int merged;

    do
    {
        merged = 0;

        for (int i = 0; i < blockCount - 1; i++)
        {
            if (blocks[i].free &&
                blocks[i + 1].free &&
                blocks[i].size == blocks[i + 1].size &&
                blocks[i].start + blocks[i].size ==
                blocks[i + 1].start)
            {
                blocks[i].size *= 2;

                for (int j = i + 1; j < blockCount - 1; j++)
                    blocks[j] = blocks[j + 1];

                blockCount--;
                merged = 1;

                break;
            }
        }

    } while (merged);
}

void freeMemory()
{
    char process[20];

    printf("Enter Process ID to free: ");
    scanf("%19s", process);

    for (int i = 0; i < blockCount; i++)
    {
        if (!blocks[i].free &&
            strcmp(blocks[i].process, process) == 0)
        {
            blocks[i].free = 1;
            blocks[i].process[0] = '\0';

            printf("%s memory freed successfully\n", process);

            mergeBuddy();
            return;
        }
    }

    printf("Process not found\n");
}

void displayMemory()
{
    printf("\n---------\n");
    printf("%-10s %-15s %-15s %-12s %-10s\n",
           "Size", "Start", "End", "Status", "Process");
    printf("-----------\n");

    for (int i = 0; i < blockCount; i++)
    {
        printf("%-10d %-15d %-15d %-12s %-10s\n",
               blocks[i].size,
               blocks[i].start,
               blocks[i].start + blocks[i].size - 1,
               blocks[i].free ? "Free" : "Allocated",
               blocks[i].free ? "-" : blocks[i].process);
    }

    printf("\n------\n");
}

int main()
{
    int choice;

    initializeMemory();

    while (1)
    {
        printf("\nMemory = 1024 KB\n");
        printf("1. Allocate Memory\n");
        printf("2. Free Memory\n");
        printf("3. Display Memory Blocks\n");
        printf("4. Exit\n");

        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                allocateMemory();
                break;

            case 2:
                freeMemory();
                break;

            case 3:
                displayMemory();
                break;

            case 4:
                printf("Exiting...\n");
                return 0;

            default:
                printf("Invalid choice\n");
        }
    }

    return 0;
}
