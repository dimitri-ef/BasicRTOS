#include "heap.h"

uint8_t ucHeap[ HEAP_SIZE ];

/**
 * @brief Create a couple of list links to mark the start and end of the list.
 */
BlockLink_t xStart;
BlockLink_t * pxEnd = NULL;

size_t xFreeBytesRemaining;

void prvHeapInit(void)
{
    uint8_t *pucAlignedHeap;
    BlockLink_t *pxFirstFreeBlock;

    size_t alignedAddress = ( ( ( size_t ) ucHeap + ALIGN_MASK ) & ~( ( size_t ) ALIGN_MASK ) );
    pucAlignedHeap = ( uint8_t * ) alignedAddress;

    size_t totalHeapAligned = HEAP_SIZE - ( alignedAddress - ( size_t ) ucHeap );
    pxEnd = ( BlockLink_t * ) ( pucAlignedHeap + totalHeapAligned - sizeof( BlockLink_t ) );
    pxEnd->xBlockSize = 0;
    pxEnd->pxNextFreeBlock = NULL;

    xStart.xBlockSize = 0;
    xStart.pxNextFreeBlock = ( BlockLink_t * ) pucAlignedHeap;

    pxFirstFreeBlock = ( BlockLink_t * ) pucAlignedHeap;
    pxFirstFreeBlock->xBlockSize = totalHeapAligned - sizeof( BlockLink_t );
    pxFirstFreeBlock->pxNextFreeBlock = pxEnd;

    xFreeBytesRemaining = pxFirstFreeBlock->xBlockSize;
}

void *pvPortMalloc(size_t xWantedSize)
{
    BlockLink_t *pxPrevBlock, *pxCurrBlock, *pxNewBlock;
    void *pvReturn = NULL;

    if (pxEnd == NULL)
    {
        prvHeapInit();
    }

    if (xWantedSize > 0)
    {
        xWantedSize += sizeof(BlockLink_t);

        if ((xWantedSize & ALIGN_MASK) != 0)
        {
            xWantedSize += (ALIGN_BYTES - (xWantedSize & ALIGN_MASK));
        }
    }

    if (xWantedSize > 0 && xWantedSize < xFreeBytesRemaining)
    {
        pxPrevBlock = &xStart;
        pxCurrBlock = xStart.pxNextFreeBlock;

        while (pxCurrBlock != pxEnd)
        {
            if (pxCurrBlock->xBlockSize >= xWantedSize)
            {
                size_t remainingSize = pxCurrBlock->xBlockSize - xWantedSize;

                if (remainingSize > sizeof(BlockLink_t))
                {
                    pxNewBlock = (BlockLink_t *)((uint8_t *)pxCurrBlock + xWantedSize);
                    pxNewBlock->xBlockSize = remainingSize;
                    pxNewBlock->pxNextFreeBlock = pxCurrBlock->pxNextFreeBlock;

                    pxCurrBlock->xBlockSize = xWantedSize;
                    pxCurrBlock->pxNextFreeBlock = NULL;

                    pxPrevBlock->pxNextFreeBlock = pxNewBlock;
                }
                else
                {
                    pxPrevBlock->pxNextFreeBlock = pxCurrBlock->pxNextFreeBlock;
                }

                xFreeBytesRemaining -= pxCurrBlock->xBlockSize;
                pvReturn = (void *)((uint8_t *)pxCurrBlock + sizeof(BlockLink_t));
                break;
            }

            pxPrevBlock = pxCurrBlock;
            pxCurrBlock = pxCurrBlock->pxNextFreeBlock;
        }
    }

    return pvReturn;
}

void vPortFree(void *pv)
{
    if (pv == NULL)
        return;

    BlockLink_t *pxBlock = (BlockLink_t *)((uint8_t *)pv - sizeof(BlockLink_t));

    BlockLink_t *pxIterator = &xStart;

    while (pxIterator->pxNextFreeBlock < pxBlock && pxIterator->pxNextFreeBlock != pxEnd)
    {
        pxIterator = pxIterator->pxNextFreeBlock;
    }

    pxBlock->pxNextFreeBlock = pxIterator->pxNextFreeBlock;
    pxIterator->pxNextFreeBlock = pxBlock;

    xFreeBytesRemaining += pxBlock->xBlockSize;
}
