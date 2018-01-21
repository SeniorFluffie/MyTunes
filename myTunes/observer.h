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

#ifndef OBSERVER_H
#define OBSERVER_H

#include <iostream>
using namespace std;

class Subject;

class Observer {
public:
  virtual void update(Subject * mySubj)= 0;
  bool operator==(const Observer & obs) const;
};

#endif
