//-----------------------------------------
//
// REMARKS: The linked structure implementation for
//          the the regions.
//
//-----------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Table.h"


//-------------------------------------------------------------------------------------
// VARIABLES

static Node *topRegion = NULL;
static int numNodes = 0; //Number of items contained in the list

// used to keep track of significant nodes in the list
static Node *traverseNode = NULL;

static Node *activeNode=NULL;
//-------------------------------------------------------------------------------------


//-------------------------------------------------------------------------------------
// FUNCTIONS

int size( )
{   //
        return numNodes;
}

// add an element to the beginning of the linked list
Boolean insert( char const * const new_string, r_size_t region_size)
{
    Boolean rc = false;
    Node *newNode = NULL;

    assert(newNode == NULL);     //scaffold

    assert(new_string != NULL);  //scaffold

    newNode = (Node *)malloc( sizeof( Node ) );

    assert(newNode !=NULL);    //scaffold
    if ( newNode != NULL )     //scaffold
    {
        newNode->next = topRegion;

        assert(newNode->next==topRegion);     //scaffold

        topRegion = newNode;

        assert(topRegion!=NULL);             //scaffold

        if (topRegion!=NULL) {
            // malloc for all contents of the node
            newNode->string = (char *) malloc(strlen(new_string) + 1);

            assert(newNode->string); // scaffold

            strcpy(newNode->string, new_string);

            assert(strcmp(newNode->string, new_string) == 0);  //scaffold

            newNode->regionSize = region_size;

            assert(newNode->regionSize);    //scaffold

            newNode->buffer = malloc(region_size);

            assert(newNode->buffer);        //scaffold

            newNode->spaceList = NULL;


            rc=true;
            numNodes++;
        }
    }
    assert (rc!=NULL);     //scaffold
    return rc;
}


// remove an element with the given string
Boolean delete( char const * const target )
{
    Boolean deleted = false;
    Node *curr = topRegion;
    Node *prev = NULL;

    assert( target != NULL);
    assert( curr != NULL);

    if ( target!=NULL && curr!=NULL)
    {
        while ( curr != NULL && strcmp( target, curr->string ) != 0 )
        {
            prev = curr;
            curr = curr->next;
        }

        if ( curr != NULL )
        {
            if ( prev != NULL )
                prev->next = curr->next;
            else
                topRegion = curr->next;

            free( curr->string );
            spacenode *toDelete=curr->spaceList;
            spacenode *previousDelete=NULL;
            while (toDelete!=NULL){
                // delete the spaceList also.
                previousDelete=toDelete;
                toDelete=toDelete->next;
                free(previousDelete);
            }
            free( curr );
            deleted = true;
            numNodes--;
        }
    }
    return deleted;
}

// tells us whether or not the given string is in the list
Boolean search( char const * const target )
{
    Boolean found = false;
    Node *curr = topRegion;

    assert(strlen(target)>0);   //scaffold
    while ( curr != NULL && !found )
    {
        assert(curr!=NULL);    //scaffold
        assert(curr->string);  //scaffold
        if ( strcmp( target, curr->string ) == 0 )
        {
            found = true;
        }
        else
        {
            curr = curr->next;
        }
    }
    //assert(found==NULL);    //scaffold
    return found;
}


// starts a list traversal by getting the data at topRegion
char * firstItem()
{
    traverseNode = topRegion->next;

    assert(topRegion->string); // assert

    return topRegion->string;
}


// gets the data at the current traversal node and increments the traversal
char * nextItem()
{
    char *item = NULL;

    // no need to go past the end of the list...

    assert(traverseNode != NULL);// assert
    if ( traverseNode != NULL )
    {
        item = traverseNode->string;
        traverseNode = traverseNode->next;
    }

    assert( item != NULL );
    return item;
}

//This was added by me!!!
void clearAndExit(){
    if (numNodes>0) {
        delete(firstItem());
        int count = 0;
        while (count < numNodes) {
            delete(nextItem());
        }
    }
    else {
        printf("THE LIST IS ALREADY EMPTY");
    }
}


/// Added by me
Boolean selectNode(char const * const target){
    Node *current=topRegion;
    Boolean selected=false;

    assert(strlen(target)>0);    //scaffold

    while(current!=NULL && !selected){
        assert(current->string);     //scaffold
        if (strcmp(target, current->string)==0){
            activeNode=current;
            selected=true;
        }
        else {
            current=current->next;
        }
    }
    return selected;
}

Node *returnActiveNode(){
    //Pass The Active Node To The
    assert(activeNode!=NULL);
    return activeNode;
}

void showProperties(Node *thisNode){
    // print out all the properties of the given region.

    assert(thisNode!=NULL);
    if (thisNode!=NULL) {

        assert(thisNode->string);
        if (thisNode->string) {
            char *name = thisNode->string;

            assert(thisNode->regionSize);
            if (thisNode->regionSize) {
                r_size_t size = thisNode->regionSize;
                printf("\n \n  Name: %s , Size: %d ", name, size);

                assert(thisNode->spaceList);
                if (thisNode->spaceList) {
                    spacenode *traverser = thisNode->spaceList;
                    printf("\n  BLOCKS\n");
                    printf("  ------");
                    int count = 1;
                    while (traverser != NULL) {
                        printf("\n  %d.)", count);

                        assert(traverser->nodeLocation);
                        if (traverser->nodeLocation) {
                            printf("\n    Starts At: %p ", traverser->nodeLocation);

                            assert(traverser->spaceSize);
                            if(traverser->spaceSize) {
                                printf("\n    Size: %d", traverser->spaceSize);
                                spacenode *endLocation = (traverser->nodeLocation) + (traverser->spaceSize);
                                printf("\n    Ends At: %p ", endLocation);
                                traverser = traverser->next;
                                count++;
                            }
                        }
                    }
                }
            }
        }
    }
}

void printAll(){
    int count=0;

    Node *curr=topRegion;

    assert(topRegion!=NULL);
    while (count<numNodes && curr!=NULL){
        showProperties(curr);
        curr=curr->next;
        count++;
    }
}

Node *findNode(const char *name){
    Node *returnVal = NULL;
    Node *current = topRegion;
    Boolean found = false;

    assert(strlen(name)>0);    //scaffold
    if (strlen(name)>0) {
        assert(current != NULL);
        while (current != NULL && !found) {
            if (strcmp(name, current->string) == 0) {
                returnVal = current;
                found = true;
            } else {
                current = current->next;
            }
        }
    }
    assert(returnVal!=NULL);     //scaffold
    return returnVal;
}

//-------------------------------------------------------------------------------------