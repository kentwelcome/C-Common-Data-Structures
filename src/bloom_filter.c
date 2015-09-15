#include "container/bloom_filter.h"


/*===========================================================================*
 *                        The container private data                         *
 *===========================================================================*/

struct _BloomFilterData {
    int32_t iSize_;
    char *aBit_;
};


/*===========================================================================*
 *                  Definition for internal operations                       *
 *===========================================================================*/
#define CHECK_INIT(self)                                                        \
            do {                                                                \
                if (!self)                                                      \
                    return ERR_NOINIT;                                          \
                if (!(self->pData))                                             \
                    return ERR_NOINIT;                                          \
                if (!(self->pData->aBit_))                                      \
                    return ERR_NOINIT;                                          \
            } while (0);


/*===========================================================================*
 *               Implementation for the exported operations                  *
 *===========================================================================*/
int32_t BloomFilterInit(BloomFilter **ppObj)
{
    /* Hopefully, we should let user specify:
       1. The number of expected elements for insertion.
       2. The acceptable FA rate.

       Based on this information, we create the internal bit array and prepare
       the relevant abount of hash functions. */

    const int   TEMP_SIZE_BIT_ARRAY = 1;
    int32_t     rc = SUCC;
    BloomFilter *pNewObj = NULL;

    if (ppObj == NULL) {
        rc = ERR_NOINIT;
        goto FAIL;
    }

    pNewObj = (BloomFilter*)malloc(sizeof(BloomFilter));
    if (pNewObj == NULL) {
        rc = ERR_NOMEM;
        goto FAIL;
    }
    memset(pNewObj, 0, sizeof(BloomFilter));

    pNewObj->pData = (BloomFilterData*)malloc(sizeof(BloomFilterData));
    if (!(pNewObj->pData)) {
        rc = ERR_NOMEM;
        goto FAIL;
    }
    memset(pNewObj->pData, 0, sizeof(BloomFilterData));

    pNewObj->pData->aBit_ = (char*)malloc(sizeof(char) * TEMP_SIZE_BIT_ARRAY);
    if (!(pNewObj->pData->aBit_)) {
        rc = ERR_NOMEM;
        goto FAIL;
    }
    memset(pNewObj->pData->aBit_, 0, sizeof(char) * TEMP_SIZE_BIT_ARRAY);

    pNewObj->insert = BloomFilterInsert;
    pNewObj->query  = BloomFilterQuery;
    pNewObj->size   = BloomFilterSize;

    *ppObj = pNewObj;

    return SUCC;

FAIL:
    if (pNewObj) {
        if (pNewObj->pData) {
            free(pNewObj->pData);
        }
        free(pNewObj);
    }

    if (ppObj) {
        *ppObj = NULL;
    }
    return rc;
}

void BloomFilterDeinit(BloomFilter **ppObj)
{

    if ( ppObj == NULL || *ppObj == NULL)
        goto EXIT;

    BloomFilter *pObj = *ppObj;
    if (!(pObj->pData))
        goto FREE_FILTER;

    BloomFilterData *pData = pObj->pData;
    if (!(pData->aBit_))
        goto FREE_DATA;

    free(pData->aBit_);

FREE_DATA:
    free(pObj->pData);
FREE_FILTER:
    free(*ppObj);
    *ppObj = NULL;
EXIT:
    return;
}

int32_t BloomFilterInsert(BloomFilter *self, Key key, size_t size)
{
    CHECK_INIT(self);
    return SUCC;
}

int32_t BloomFilterQuery(BloomFilter *self, Key key, size_t size)
{
    CHECK_INIT(self);
    return SUCC;
}

int32_t BloomFilterSize(BloomFilter *self)
{
    CHECK_INIT(self);
    return self->pData->iSize_;
}
