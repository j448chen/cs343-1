#include <iostream>
#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"
#include "q3utils.h"

using namespace std;

TallyVotes::Tour TallyVotes::vote(unsigned int id, TallyVotes::Ballot ballot) {

        // now now we can vote
        picture += ballot.picture;
        statue += ballot.statue;
        giftshop += ballot.giftshop;
        printer.print(id, Voter::States::Vote, ballot);

        if (waiting == group-1) {             // last guy
            // calculate voting result, clear acumulator and e.t.c
            result = get_result(picture, statue, giftshop);
            picture = 0;
            giftshop = 0;
            statue = 0;
            printer.print(id, Voter::States::Complete);
            round_complete = true;           // Setting this flag, and waituntil will check this condition 
        } else {
            WAITUNTIL(round_complete, waiting ++ ; printer.print(id, Voter::States::Block, waiting), waiting -- ; printer.print(id, Voter::States::Unblock, waiting));
        }

        if (waiting == 0) {                 // last one of this group
            round_complete = false;         // clear the flag for the next group
        }

        RETURN(TallyVotes::Tour(result));   // using this marco instead of normal one to wake up blocking tasks
}

TallyVotes::TallyVotes( unsigned int group, Printer & printer ): round_complete(false), group(group), picture(0), statue(0), giftshop(0), waiting(0), printer(printer) {}
