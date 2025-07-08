#include <stdio.h>
#include "heap.h"

int execDot() {
    int ret = system("dot ");
    if (ret == -1) {
        printf("ERROR !");
    } else {
        
    }
    return 0;
}

void dumpHeapToDot(const char *filename)
{
    FILE *f = fopen(filename, "w");
    if (!f) return;

    fprintf(f, "digraph Heap {\n");
    fprintf(f, "  node [shape=record, fontname=\"Courier\"];\n");

    BlockLink_t *node = &xStart;
    int id = 0;

    while (node != NULL && node != pxEnd)
    {
        fprintf(f,
            "  node%d [label=\"{{Block_t: %p}|{size: %zu}|{next: %p}}\"];\n",
            id, (void *)node, node->xBlockSize, (void *)node->pxNextFreeBlock
        );

        if (node->pxNextFreeBlock && node->pxNextFreeBlock != pxEnd)
        {
            fprintf(f, "  node%d -> node%d;\n", id, id + 1);
        }

        node = node->pxNextFreeBlock;
        id++;
    }

    fprintf(f,
        "  freebytes [shape=note, label=\"xFreeBytesRemaining = %zu bytes\"];\n",
        xFreeBytesRemaining
    );

    fprintf(f, "}\n");
    fclose(f);
}

int main(void)
{
    void *ptr1 = pvPortMalloc(100);
    void *ptr2 = pvPortMalloc(200);

    printf("Allocated ptr1: %p\n", ptr1);
    printf("Allocated ptr2: %p\n", ptr2);

    dumpHeapToDot("a.dot");

    vPortFree(ptr1);
    vPortFree(ptr2);

    void *ptr3 = pvPortMalloc(150);
    printf("Reused ptr3: %p\n", ptr3);

    return 0;
}