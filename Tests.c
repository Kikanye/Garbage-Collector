//----------------------------------------------
//
// REMARKS: The Tests
//-----------------------------------------------

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "Tests.h"
#include <math.h>


int main(){

    testRinit("", 700, false);
    testRinit("", 0, false);
    testRinit("\n", -200, false);
    testRinit("thisBuffer", 5000,true);
    testRinit("a", 0.02, false);
    testRinit("properBuffer", 15, true);
    testRinit("properBuffer", 14, false);


    testRchoose("", false);
    testRchoose("thisBuffer", true);
    testRchoose("a", false);
    testRchoose("\n", false);
    testRchoose("properBuffer", true);

    testRchosen("properBuffer");

    rchoose("thisBuffer");
    rchoose("");
    testRchosen("thisBuffer");

    void *ooa=ralloc(0.02);
    if (ooa==NULL){
        printf("\nSUCCESS ralloc works\n");

    }else
    {
        printf("\nFAILURE ralloc doesn't work");
    }

    void *oob=ralloc(3);
    if (oob!=NULL){
        printf("\nSUCCESS ralloc works\n");

    }else
    {
        printf("\nFAILURE ralloc doesn't work\n");
    }

    testRsize(oob, 4);

    void *ooc=ralloc(-2);
    if (ooc==NULL){
        printf("\nSUCCESS ralloc works\n");

    }else
    {
        printf("\nFAILURE ralloc doesn't work\n");
    }
    testRsize(ooc, 0);

    testRfree(ooc, false);
    testRfree(oob, true);
    testRfree(ooa, false);


    rdestroy("thisBuffer");
    if (rchoose("thisBuffer")==false){
        printf("\nSUCCESS  rdestroy() works\n");

    }else
    {
        printf("\nFAILURE rdestroy() does not work\n");
    }

}

void testRinit(const char *region_name, r_size_t region_size,Boolean expected){

    Boolean returnVal=rinit(region_name, region_size);
    if (returnVal==expected){
        printf("\nSUCCESS rinit works\n");

    } else{
        printf("\nFAILURE rinit doesn't work\n");
    }

}

void testRchoose(const char *region_name,Boolean expected){

    Boolean returnVal=rchoose(region_name);
    if (returnVal==expected){
        printf("\nSUCCESS rchoose() works.\n");

    } else{
        printf("\nFAILURE rchoose doesn't work\n");
    }

}

void testRchosen(const char *expected){
    if (strcmp(expected, rchosen())==0){
        printf("\nSUCCESS rchosen() works\n ");
    } else{
        printf("\nFAILURE rchosen() doesn't work\n");
    }
}

void testRsize(void *blk_ptr, r_size_t expected){
    if (rsize(blk_ptr)==expected){
        printf("\nSUCCESS rsize() works\n");
    }else {
        printf("\nFAILURE rsize() doesn't work\n");
    }
}

void testRfree(void *blk_ptr, Boolean expected){
    if (rfree(blk_ptr)==expected){
        printf("\nSUCCESS rfree() works\n");
    }else {
        printf("\nFAILURE rfree() doesn't work\n");
    }
}

void testRdump(){
    printf("SUCCESS ;) rdump() works\n");
}