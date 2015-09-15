#include "container/bloom_filter.h"
#include <CUnit/Util.h>
#include <CUnit/Basic.h>


#define SIZE_SMALL_TEST     (32)
#define MASK_YEAR           (100)
#define MASK_LEVEL          (200)

typedef struct Employ_ {
    int8_t cYear;
    int8_t cLevel;
    int32_t iId;
} Employ;


int32_t AddSuite();
void TestManipulate();
void TestBloomFilterInit();

int32_t main()
{
    int32_t rc = SUCC;

    if (CU_initialize_registry() != CUE_SUCCESS) {
        rc = CU_get_error();
        goto EXIT;
    }

    /* Register the test suite for queue structure verification. */
    if (AddSuite() != SUCC) {
        rc = CU_get_error();
        goto CLEAN;
    }

    /* Launch all the tests. */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();

CLEAN:
    CU_cleanup_registry();
EXIT:
    return rc;
}

int32_t AddSuite()
{
    int32_t rc = SUCC;

    CU_pSuite pSuite = CU_add_suite("Structure Verification", NULL, NULL);
    if (!pSuite) {
        rc = ERR_REG;
        goto EXIT;
    }

    char *szMsg = "Combination with insertion, deletion, and order checking.";
    CU_pTest pTest = CU_add_test(pSuite, szMsg, TestManipulate);
    if (!pTest)
        rc = ERR_REG;

    pTest = CU_add_test(pSuite, szMsg, TestBloomFilterInit);
    if (!pTest)
        rc = ERR_REG;

EXIT:
    return rc;
}

void TestBloomFilterInit()
{
    int rc = SUCC;
    BloomFilter *pBloomFilter = NULL;

    rc = BloomFilterInit(NULL);
    CU_ASSERT(rc == ERR_NOINIT);

    rc = BloomFilterInit(&pBloomFilter);
    CU_ASSERT(rc == SUCC);

    BloomFilterDeinit(&pBloomFilter);
    CU_ASSERT(pBloomFilter == NULL);

    BloomFilterDeinit(&pBloomFilter);
    BloomFilterDeinit(NULL);
}

void TestManipulate()
{
}
