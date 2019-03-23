
#include "Table.h"

void testRinit(const char *region_name, r_size_t region_size,Boolean expected);

void testRchoose(const char *region_name,Boolean expected);

void testRchosen(const char *expected);

void testRsize(void *blk_ptr, r_size_t expected);

void testRfree(void *blk_ptr, Boolean expected);

void testRdump();

