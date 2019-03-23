//----------------------------------------------
//
// REMARKS: The Implementation for the memory regions
//          program with the functions required
//-----------------------------------------------

#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "regions.h"
#include "Table.h"



//-------------------------------------------------------------------------------------
// VARIABLES
static Node *chosenRegion =NULL;
static char *chosenRegionName=NULL;
//-------------------------------------------------------------------------------------




//-------------------------------------------------------------------------------------
// FUNCTIONS
Boolean rinit(const char *region_name, r_size_t region_size){
    Boolean returnValue = false;

    Boolean uniqueName= !search(region_name);



    assert(floor(region_size==region_size));
    if (floor(region_size)==region_size) {

        assert(region_size > 0);     //scaffold

        assert(uniqueName);     //scaffold

        if (region_size > 0 && uniqueName) {

            if (region_size%8!=0){
                region_size=roundUp(region_size);
            }

            returnValue = insert(region_name, region_size);
            rchoose(region_name);
        }
        assert(returnValue != NULL);     //scaffold
    }
    return returnValue;
}


Boolean rchoose(const char *region_name){
    Boolean returnVal=false;
    Boolean canBeChosen;

    assert(strlen(region_name)>0);     //scaffold
    if (strlen(region_name)>0) {
        canBeChosen=search(region_name);

        if (canBeChosen) {
            returnVal=selectNode(region_name);

            chosenRegion=returnActiveNode();

            assert(chosenRegion!=NULL);           //scaffold
            assert(chosenRegion->string);         //scaffold

            chosenRegionName = chosenRegion->string;
            returnVal=true;            // might remove this!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
        }
        else {
            printf("\nThat Region does Not exist");        // scaffold
        }
    }
    else {
        printf("\nINVALID NAME\n");                //scaffold
    }

        return returnVal;
}

const char *rchosen(){
    // Returns the name of the currently chosen region

    assert(strlen(chosenRegionName)!=0);        //scaffold
    if (chosenRegionName==NULL ){
        printf("There Is No Chosen Region Currently");
    }
    return chosenRegionName;
}

void *ralloc(r_size_t block_size){
    //allocate space the given space parameter to an available space in the block.

    //Utilize for traversal
    spacenode *topOfTheList=chosenRegion->spaceList;
    spacenode *currentBlock=chosenRegion->spaceList;


    void *presentLocation=NULL;
    void *endLocation=NULL;
    void *returnVal=NULL;
    Boolean inserted = false;

    assert(block_size>0);            //scaffold

    assert(chosenRegion!=NULL);      //scaffold

    if (block_size>0 && chosenRegion!=NULL) {
        assert(chosenRegion->buffer);          //scaffold
        presentLocation=chosenRegion->buffer;        // the current position to be checked

        assert(chosenRegion->regionSize);      //scaffold
        endLocation=presentLocation+chosenRegion->regionSize;     // the last location in the buffer

        assert(floor(block_size)==block_size);
        if (floor(block_size)==block_size) {
            if (block_size % 8 != 0) {
                block_size = roundUp(block_size); // make sure the size is a multiple of 8
            }
            assert(block_size % 8 == 0);           //scaffold

            r_size_t nodeSize = 0;           // used to check if the space is free or not
            Boolean locationUsed;
            r_size_t availableSpace;

            while (presentLocation < endLocation && !inserted) {
                // Traverse through the buffer, find usable space and allocate it.

                spacenode *nodeToAdd = NULL; // the node to be added

                assert(presentLocation != NULL);      //scaffold

                if (topOfTheList == NULL) {
                    // if the list is empty
                    nodeToAdd = makeSpaceNode(block_size, presentLocation);
                    assert(nodeToAdd != NULL);
                    chosenRegion->spaceList = nodeToAdd;

                    assert(chosenRegion->spaceList == nodeToAdd);
                    inserted = chosenRegion->spaceList == nodeToAdd;


                } else {
                    nodeSize = searchspaceList(currentBlock, presentLocation);
                    locationUsed = nodeSize > 0;

                    if (locationUsed) {
                        presentLocation += nodeSize;
                    } else {

                        availableSpace = getSpace(currentBlock, presentLocation, endLocation, block_size);
                        if (availableSpace >= block_size) {
                            // check to see if the space is enough and add it.
                            nodeToAdd = makeSpaceNode(block_size, presentLocation);

                            assert(nodeToAdd != NULL);
                            nodeToAdd->next = chosenRegion->spaceList;
                            chosenRegion->spaceList = nodeToAdd;

                            assert(chosenRegion->spaceList == nodeToAdd);
                            inserted = chosenRegion->spaceList == nodeToAdd;
                        } else {
                            presentLocation += availableSpace; // go the next possible address
                        }
                    }
                }
            }
        }
        if (inserted){
            // clear the bytes.
            memset(chosenRegion->spaceList->nodeLocation,0, chosenRegion->spaceList->spaceSize);
            returnVal=chosenRegion->spaceList->nodeLocation;
        }
    }
    return returnVal;
}

r_size_t rsize(void *block_ptr) {
    r_size_t returnVal=0;

    assert(block_ptr != NULL);
    if (block_ptr!=NULL) {
        spacenode *top = returnActiveNode()->spaceList;
        returnVal = searchForSize(top, block_ptr);
    }
    assert(returnVal!=NULL);
    return returnVal;
}

Boolean rfree(void *block_ptr){
    Boolean returnVal= false;

    assert(block_ptr!=NULL);
    if (block_ptr!=NULL) {
        spacenode *top = returnActiveNode()->spaceList;
        returnVal = searchAndDelete(top, block_ptr);
    }
    return returnVal;
}

void rdestroy(const char *region_name){

    assert(strlen(region_name)>0);
    if (strlen(region_name)>0) {
        delete(region_name);
        rchoose(firstItem()); //delete and choose the topRegion item
    }
}

void rdump() {

    if (size() > 0) {
        printAll();
    } else {
        printf("No Regions have been allocated");
    }
}

r_size_t roundUp(r_size_t currentSize){

    // round up the given number to be a multiple of 8

    r_size_t returnVal=0;
    while (currentSize%8 != 0){
        currentSize+=1;
    }
    returnVal=currentSize;
    assert(returnVal%8==0);
    return returnVal;
}


//-------------------------------------------------------------------------------------
