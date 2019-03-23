//-----------------------------------------
//
// REMARKS: The header file for the regions implementation.
//
//-----------------------------------------


#ifndef _REGIONS_H
#define _REGIONS_H

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES

typedef enum { false, true } Boolean;

typedef unsigned short r_size_t;
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
// PROTOTYPES
Boolean rinit(const char *region_name, r_size_t region_size);

Boolean rchoose(const char *region_name);

const char *rchosen();

void *ralloc(r_size_t block_size);

r_size_t rsize(void *block_ptr);

Boolean rfree(void *block_ptr);

void rdestroy(const char *region_name);

void rdump();

r_size_t roundUp(r_size_t currentSize);
//-------------------------------------------------------------------------------------

#endif
