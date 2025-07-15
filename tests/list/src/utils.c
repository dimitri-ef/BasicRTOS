#include "utils.h"

bool vListIsSorted(List_t * const pxList)
{
    List_t * const pxTmpList = pxList;
    while (listGET_END_MARKER(pxTmpList))
    {
        pxTmpList = listGET_NEXT(pxListItem);
    }
    
}