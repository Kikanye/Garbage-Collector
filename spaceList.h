//-----------------------------------------
//
// REMARKS: The header file for spaceList.c
//
//-----------------------------------------
#include "regions.h"

//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES
typedef struct SPACENODE spacenode;

struct SPACENODE
{
    void *nodeLocation;
    r_size_t spaceSize;
    spacenode *next;
};
//-------------------------------------------------------------------------------------

//-------------------------------------------------------------------------------------
// PROTOTYPES
spacenode *makeSpaceNode( r_size_t blockSize, void *address);
r_size_t searchspaceList (spacenode *statringPoint, void *address);
r_size_t searchForSize(spacenode *theTop, void *address);
Boolean searchAndDelete(spacenode *theTop, void *address);
r_size_t getSpace(spacenode *theTop, void *address,void *endLocation, r_size_t sizeTreshold);
//-------------------------------------------------------------------------------------