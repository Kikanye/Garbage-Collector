//--------------------------------------------------
//
// REMARKS: The header file for the linked structure
//          implementation of the buffers.
//
//---------------------------------------------------

#include "regions.h"
#include "spaceList.h"


//-------------------------------------------------------------------------------------
// CONSTANTS and TYPES

// Linked list node definition
typedef struct NODE Node; // node type containing information about the region.

 struct NODE
{
    char *string;
    r_size_t regionSize;
    void *buffer;
    Node *next;
    spacenode *spaceList;
};
//-------------------------------------------------------------------------------------
//static Node *topRegion = NULL;

//-------------------------------------------------------------------------------------
// PROTOTYPES

//Returns the size metadata
int size( );

//Return Boolean
Boolean insert( char const * const new_string, r_size_t region_size );

Boolean delete( char const * const target );

Boolean search( char const * const target );

//Traverse
char * firstItem();

char * nextItem();

//added by me.
void clearAndExit();

Boolean selectNode(char const * const target);

Node *returnActiveNode();

void showProperties(Node *thisNode);

void printAll();

Node *findNode(const char *name);

//-------------------------------------------------------------------------------------
