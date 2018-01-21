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

#ifndef _Playlist_H
#define _Playlist_H

#include <ostream>
#include <string>
#include <vector>
#include "track.h"
#include "subject.h"
#include "observer.h"


class Playlist : public Subject, public Observer {
	/*
	Playlist represents an user playlist of tracks.
	*/
public:
	// default playlist methods
	Playlist(const string & aPlaylistName);
	~Playlist(void);
	int getID();
	string getName();
	void removeTrack(Track & aTrack);
	void addTrack(Track & aTrack);
	vector<Track*> getTracks();
	string toString() const;

	// following methods
	void startFollowing(Playlist & aPlaylist);
	void stopFollowing();
	Playlist * getFollowing();

	// observer methods
	void update(Subject * mySubj);

private:
	string name;
	vector<Track*> tracks;
	vector<Track*>::iterator findPosition(Track & aTrack);
	Playlist * following;
	Playlist(const Playlist & aPlaylist); //hide copy constructor in private section
};

ostream & operator<<(ostream & out, const Playlist & aPlaylist);

#endif
