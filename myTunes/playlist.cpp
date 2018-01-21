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

#include <iostream>
#include <string>
using namespace std;
#include <vector>
#include "playlist.h"
#include "subject.h"
#include "observer.h"
#include <algorithm>

Playlist::Playlist(const string & aPlaylistName){
	cout << "Playlist(string&)" << endl;
	name = aPlaylistName;
}
Playlist::Playlist(const Playlist & aPlaylist){
	cout << "Playlist(const Playlist & aPlaylist)" << endl;
	cout << "ERROR: Playlist(const Playlist & aPlaylist) --should never run" << endl;
}

Playlist::~Playlist(){
	cout << "~Playlist(void)" << endl;
}
int Playlist::getID(){return -1;}

string Playlist::getName() {return name;}

vector<Track*> Playlist::getTracks(){return tracks;}

vector<Track*>::iterator Playlist::findPosition(Track & aTrack){
	for (vector<Track*>::iterator itr = tracks.begin() ; itr != tracks.end(); ++itr)
		if(*itr == &aTrack) return itr;
	return tracks.end();
}

void Playlist::addTrack(Track & aTrack){
	//add track if it does not already exist
	vector<Track*>::iterator itr = findPosition(aTrack);
	if(itr == tracks.end()) {
		tracks.push_back(&aTrack);
	}
	notify();
	return;
}

void Playlist::removeTrack(Track & aTrack){
	vector<Track*>::iterator itr = findPosition(aTrack);
	if(itr != tracks.end()) {
		tracks.erase(itr);
	}
	notify();
	return;
}

string Playlist::toString()const {
	string indent = "     ";
	string s;
	s.append(name);
	s.append("\n");
	s.append(indent + indent + "Playlist Tracks:\n");
	for (vector<Track*>::size_type i = 0 ; i < tracks.size(); i++){
		   s.append(indent + indent + to_string(i+1) + " " + (tracks[i])->toString() + "\n");
	}

	return s;
}

ostream & operator<<(ostream & out, const Playlist & aPlaylist){
	out << aPlaylist.toString() << endl;
	return out;
}

// observer method
void Playlist::update(Subject * mySubj) {
	if(following)
		tracks = following->tracks;
}

// method (for following) utilizing subject and observer methods
void Playlist::startFollowing(Playlist & aPlaylist) {
	if(!following)
	stopFollowing();
	following = &aPlaylist;
	following->attach(*this);
}

void Playlist::stopFollowing() {
	if(following)
		following->detach(*this);
}

Playlist* Playlist::getFollowing() {
	return following;
}
