//-----------------------------------------
//
// REMARKS: This file implements the second linked structure
// which points to the used locations in memory.
//
//-----------------------------------------

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "regions.h"
#include "spaceList.h"

//-------------------------------------------------------------------------------------
// FUNCTIONS
spacenode *makeSpaceNode( r_size_t blockSize, void *address) {
    // create a space node with the given parameters.
    spacenode *newSpaceNode = NULL;

    assert(address != NULL);        //scaffold
    if (address != NULL) {          //scaffold
        newSpaceNode = (spacenode *) malloc(sizeof(spacenode));

        assert(newSpaceNode!=NULL);     //scaffold
        if (newSpaceNode != NULL) {

            newSpaceNode->spaceSize = blockSize;
            newSpaceNode->nodeLocation = address;
            newSpaceNode->next=NULL;

            assert(newSpaceNode->spaceSize==blockSize);     //scaffold
            assert(newSpaceNode->nodeLocation==address);     //scaffold

        }
    }
    assert(newSpaceNode!=NULL);
    return newSpaceNode;
}

r_size_t searchspaceList (spacenode *statringPoint, void *address){
    spacenode *traverser=statringPoint;
    r_size_t nodeSize=0;

    assert(address!=NULL);             //scaffold
    while (nodeSize==0 && traverser!=NULL){

        assert(traverser->nodeLocation);           //scaffold
        assert(traverser->spaceSize);              //scaffold

        if (traverser->nodeLocation==address){
            nodeSize=traverser->spaceSize;
        }
        else{
            traverser=traverser->next;
        }
    }
    assert(nodeSize>=0);
    return nodeSize;
}

r_size_t searchForSize(spacenode *theTop, void *address){
    // search to see if a node points to that location in a region.

    r_size_t returnVal=0;
    spacenode *traverser = theTop;
    Boolean found=false;

    assert(traverser!=NULL);
    while (traverser!=NULL && !found){
        if (traverser->nodeLocation==address){
            found=true;
            returnVal=traverser->spaceSize;
        } else{

            assert(traverser->next);
            traverser=traverser->next;
        }
    }
    assert(returnVal!=NULL);
    return returnVal;
}

Boolean searchAndDelete(spacenode *theTop, void *address){
    // search and delete the node at the address given a starting point of traversal.

    Boolean deleted=false;
    spacenode *currentTraverser = theTop;
    spacenode *prevoiusTraverser =NULL;

    //assert(currentTraverser!=NULL);
    //assert(currentTraverser->nodeLocation);

    while (currentTraverser!=NULL && currentTraverser->nodeLocation!=address){
        prevoiusTraverser=currentTraverser;

        assert(currentTraverser!=NULL);
        currentTraverser=currentTraverser->next;

    }
    if (currentTraverser!=NULL){
        if (prevoiusTraverser!=NULL){
            prevoiusTraverser->next=currentTraverser->next;
        } else{
            theTop=currentTraverser->next;
        }
        free(currentTraverser);

        deleted=true;
    }
    //assert(deleted);
    return deleted;
}

r_size_t getSpace(spacenode *theTop, void *address, void *endLocation, r_size_t sizeTreshold){
    // get the space from a given address in comparison with the required size,

    r_size_t returnSize=0;
    r_size_t size=searchspaceList(theTop, address);

    assert(returnSize<sizeTreshold+1);     // scaffold
    while (size==0 && returnSize<sizeTreshold+1 && address<endLocation){
        // using treshold +1 to be safe.
        // calculate the size until it is clearly enough or stop.
        returnSize++;
        address++;
        size=searchspaceList(theTop, address);
    }
    return returnSize;
}
//-------------------------------------------------------------------------------------





