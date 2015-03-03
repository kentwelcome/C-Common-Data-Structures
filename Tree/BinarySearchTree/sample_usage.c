#include "bin_search_tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>
#include <assert.h>


#define COUNT_CASE          (1000)
#define SIZE_PRINT_BUF      (256)

#if __x86_64__
    typedef uint64_t IntData;
#else
    typedef uint32_t IntData;
#endif


void wrap_printf(char*, IntData);

/* The item comparator for integer type. */
int32_t func_compare_primitive(Item, Item);

/* The item deallocator for integer type. */
void func_destroy_primitive(Item);

/* The testing suit which inserts integer into the tree. */
void test_primitive();

/* The testing suit which inserts pointers to structures into the tree. */
void test_non_primitive();


int main()
{
    /* Initialize the random seed. */
    srand(time(NULL));

    test_primitive();

    return 0;
}

void test_primitive()
{
    /* Initialize the tree. */
    BinSearchTree *pTree;
    int32_t iStat = BSTreeInit(&pTree);
    if (iStat != SUCCESS)
        return;

    /* Set the comparison and deallocation functions. */
    pTree->set_compare(pTree, func_compare_primitive);
    pTree->set_destroy(pTree, func_destroy_primitive);

    /* Insert integers into the tree. */
    uint32_t i;
    #if __x86_64__
        int64_t nCase;
    #else
        int32_t nCase;
    #endif
    for (i = 0 ; i < COUNT_CASE ; i++) {
        nCase = rand() % COUNT_CASE;
        iStat = pTree->insert(pTree, (Item)nCase);
        wrap_printf("Insert Element: ", nCase);
        if (iStat != SUCCESS)
            wrap_printf("[Insertion Conflict] ", nCase);
    }

    /* Iteratively request the element with maximum order and delete it. */
    uint32_t uiSize = pTree->size(pTree);
    uint32_t uiHalf = uiSize / 2;
    for (i = 0 ; i < uiHalf ; i++) {
        iStat = pTree->maximum(pTree, (Item*)&nCase);
        wrap_printf("Max Order Element: ", nCase);
        iStat = pTree->delete(pTree, (Item)nCase);
    }

    /* Iteratively request the element with minimum order and delete it. */
    /*
    uiHalf = uiSize - uiHalf;
    for (i = 0 ; i < uiHalf ; i++) {
        iStat = pTree->minimum(pTree, (Item*)&nCase);
        wrap_printf("Min Order Element: ", nCase);
        iStat = pTree->delete(pTree, (Item)nCase);
    }
    */

    /* Deinitialize the tree. */
    BSTreeDeinit(&pTree);

    return;
}

int32_t func_compare_primitive(Item itemSrc, Item itemTge)
{
    int32_t iSrc, iTge;

#if __x86_64__
    int64_t lTmp;
    lTmp = (int64_t)itemSrc;
    iSrc = (int32_t)lTmp;
    lTmp = (int64_t)itemTge;
    iTge = (int32_t)lTmp;
#else
    iSrc = (int32_t)itemSrc;
    iTge = (int32_t)itemTge;
#endif

    return iSrc - iTge;
}

void func_destroy_primitive(Item item)
{ return; }

void wrap_printf(char *szMsg, IntData num)
{
    char szBuf[SIZE_PRINT_BUF];

#if __x86_64__
    snprintf(szBuf, SIZE_PRINT_BUF, "%s %ld\n", szMsg, num);
#else
    snprintf(szBuf, SIZE_PRINT_BUF, "%s %d\n", szMsg, num);
#endif
    printf("%s", szBuf);

    return;
}
