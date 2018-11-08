/*
 * File: pager-predict.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 3
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains a predictive pageit
 *      implmentation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"


void pageit(Pentry q[MAXPROCESSES]) {

  /* This file contains the stub for a predictive pager */
  /* You may need to add/remove/modify any part of this file */

  /* Static vars */
  static int initialized = 0;
  static int tick = 1; // artificial time

  /* Local vars */
  int buff_size = 10;
  int proc; //process
  int pc; // program counter
  int page;
  int smallest = __INT_MAX__; // smallest timestamp
  int victim; // page selected to be swapped out
  int working_set[buff_size]; // working set

  /* initialize static vars on first run */
  if(!initialized) {
	  /* Init complex static vars here */
	  initialized = 1;
  }

  /* TODO: Implement Predictive Paging */
    

  for(proc = 0; proc < MAXPROCESSES; proc++) { // loop over each process
    if(q[proc].active) { //ensure page is active
      pc  = q[proc].pc; // program counter
      page = q[proc].pc/PAGESIZE; // current page
      
      //determine future page, need to predict based on pc behavior

      if(!q[proc].pages[page]) { // is page not swapped in?   
        if(!pagein(proc,page)) { //pagein() failed
          // select page to evict
          // page with smallest time stamp will be the LRU
          for(int i = 0; i < q[proc].npages; i++) {
            // page is swapped in and timestamp is smaller than last
            if(q[proc].pages[i] && timestamps[proc][i] < smallest) { 
              smallest = timestamps[proc][i]; // update smallest
              victim = i; // set the victim
            }
          }
          // call pageout on the victim
          pageout(proc, victim);
          timestamps[proc][page] = tick; // update time stamp
          /* advance time for next pageit iteration */
          tick++; 
        }
      } //check for remaining processes (keep looping)
    } 
  }

  //fprintf(stderr, "pager-predict not yet implemented. Exiting...\n");
  //exit(EXIT_FAILURE);

  /* advance time for next pageit iteration */
  tick++;
}  