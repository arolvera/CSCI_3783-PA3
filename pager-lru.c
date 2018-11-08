/*
 * File: pager-lru.c
 * Author:       Andy Sayler
 *               http://www.andysayler.com
 * Adopted From: Dr. Alva Couch
 *               http://www.cs.tufts.edu/~couch/
 *
 * Project: CSCI 3753 Programming Assignment 3
 * Create Date: Unknown
 * Modify Date: 2012/04/03
 * Description:
 * 	This file contains an lru pageit
 *      implmentation.
 */

#include <stdio.h>
#include <stdlib.h>

#include "simulator.h"

void pageit(Pentry q[MAXPROCESSES]) { // page map passed in

  /* This file contains the stub for an LRU pager */
  /* You may need to add/remove/modify any part of this file */

  /* Static vars */
  static int initialized = 0;
  static int tick = 1; // artificial time
  static int timestamps[MAXPROCESSES][MAXPROCPAGES]; 

  /* Local vars */
  int proctmp;
  int pagetmp;
  int proc; // process
  int page; // page
  int smallest = __INT_MAX__; // initial timestamp
  int victim; // page to swap

  /* initialize static vars on first run */
  if(!initialized) {
	  for(proctmp=0; proctmp < MAXPROCESSES; proctmp++) {
	    for(pagetmp=0; pagetmp < MAXPROCPAGES; pagetmp++) {
		    timestamps[proctmp][pagetmp] = 0;
	    }
	  }
	  initialized = 1;
  }

  /* TODO: Implement LRU Paging */

  for(proc = 0; proc < MAXPROCESSES; proc++) { // loop over each process
    if(q[proc].active) { //ensure page is active
      page = q[proc].pc/PAGESIZE;
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
}
