/* * * * * * * * * * * * * * * * * * * * * * * * * * */
/*                                                   */
/*  Program:  MyTunes Music Player                   */
/*  Contributors:  Michael Kazman 101037568          */
/*                 Tao Guo 100968344                 */
/*                 Louis Nel                         */
/*  Date:  NOV-2017                                  */
/*                                                   */
/*  (c) Nov 2017                                     */
/*                                                   */
/*  All rights reserved.  Distribution and           */
/*  reposting, in part or in whole, requires         */
/*  written consent of the author.                   */
/*                                                   */
/*  COMP 2404 students may reuse this content for    */
/*  their course assignments without seeking consent */
/* * * * * * * * * * * * * * * * * * * * * * * * * * */

#include "subject.h"
using namespace std;

void Subject::attach(Observer & myObs) {
	observers.insert(&myObs);
	myObs.update(this);
	return;
}

void Subject::detach(Observer & myObs) {
	observers.erase(&myObs);
	myObs.update(this);
	return;
}

void Subject::notify() {
	set<Observer*> observerTemp = observers;
	for (set<Observer*>::iterator it=observerTemp.begin(); it != observerTemp.end(); ++it)
			 (*it)->update(this);
	return;
}

set<Observer*> Subject::getObservers() {
	return observers;
}
