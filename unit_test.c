//
//  unit_test.c
//  
//
//  Created by Jordan Eizenga on 3/9/16.
//
//

#include <stdio.h>
#include <stdlib.h>
#include "CuTest.h"
#include "utils.h"

char maximum_quality = MAX_QUAL;

void test_levenshtein_distance(CuTest* ct) {
    CuAssert(ct, "failed: same string\n",
             substr_is_within_levenshtein_dist("ACGGTGTCGAA", "ACGGTGTCGAA", 11, 11, 0));
    CuAssert(ct, "failed: exact substring\n",
             substr_is_within_levenshtein_dist("ACGGTGTCGAA", "GTGTCG", 11, 6, 0));
    CuAssert(ct, "failed: 1 mismatch substring dist 0\n",
             !substr_is_within_levenshtein_dist("ACGGTGTCGAA", "GTGACG", 11, 6, 0));
    CuAssert(ct, "failed: 1 mismatch substring dist 1\n",
             substr_is_within_levenshtein_dist("ACGGTGTCGAA", "GTGACG", 11, 6, 1));
    CuAssert(ct, "failed: 1 insert substring dist 0\n",
             !substr_is_within_levenshtein_dist("ACGGTGTCGAA", "GTGTACG", 11, 7, 0));
    CuAssert(ct, "failed: 1 insert substring dist 1\n",
             substr_is_within_levenshtein_dist("ACGGTGTCGAA", "GTGTACG", 11, 7, 1));
    CuAssert(ct, "failed: 1 delete substring dist 0\n",
             !substr_is_within_levenshtein_dist("ACGGTGTCGAA", "GTGCG", 11, 5, 0));
    CuAssert(ct, "failed: 1 delete substring dist 1\n",
             substr_is_within_levenshtein_dist("ACGGTGTCGAA", "GTGCG", 11, 5, 1));
    CuAssert(ct, "failed: 2 insert substring dist 1\n",
             !substr_is_within_levenshtein_dist("ACGGTGTCGAA", "GTGTACCG", 11, 8, 1));
    CuAssert(ct, "failed: complete mismatch dist 2\n",
             !substr_is_within_levenshtein_dist("ACGGTGTCGAA", "CGATGGAC", 11, 8, 2));
    CuAssert(ct, "failed: 2 longer substring dist 2\n",
             substr_is_within_levenshtein_dist("ACGGTGTCGAA", "ACGGTGTCGAATT", 11, 13, 2));
    CuAssert(ct, "failed: 2 longer substring dist 1\n",
             !substr_is_within_levenshtein_dist("ACGGTGTCGAA", "ACGGTGTCGAATT", 11, 13, 1));
    CuAssert(ct, "failed: 3 longer substring dist 2\n",
             !substr_is_within_levenshtein_dist("ACGGTGTCGAA", "ACGGTGTCGAATTT", 11, 14, 2));
    CuAssert(ct, "failed: 3 longer substring dist 3\n",
             substr_is_within_levenshtein_dist("ACGGTGTCGAA", "ACGGTGTCGAATTT", 11, 14, 3));
    CuAssert(ct, "failed: 3 longer substring dist 4\n",
             substr_is_within_levenshtein_dist("ACGGTGTCGAA", "ACGGTGTCGAATTT", 11, 14, 4));
    CuAssert(ct, "failed: 7 longer substring dist 1\n",
             !substr_is_within_levenshtein_dist("ACGGTGTCGAA", "ACGGTGTCGAATTTTTTT", 11, 18, 1));

}

CuSuite* get_suite() {
    
    CuSuite* suite = CuSuiteNew();
    
    SUITE_ADD_TEST(suite, test_levenshtein_distance);
    
    return suite;
}


int main(void) {
    CuSuite* suite = get_suite();
    
    CuString* output = CuStringNew();
    CuSuiteRun(suite);
    CuSuiteSummary(suite, output);
    CuSuiteDetails(suite, output);
    printf("%s\n", output->buffer);
    
    return 0;
}

