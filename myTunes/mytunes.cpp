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
#include <cstdlib>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include <list>

using namespace std;
#include "str_util.h"
#include "mytunes.h"
#include "UI.h"
#include "command.h"

MyTunes::MyTunes():view(this)
{
	nextAvailableSongID = 1;
	nextAvailableRecordingID = 1;
	nextAvailableTrackID = 1;
}

void MyTunes::run()
{
	//start user interface
	view.run();

}
void MyTunes::executeCommand(Command cmd){
	//execute application (non UI shell) commands
	//These are the commands that affect the data model
	//or retrieve contents from the data model
	if(cmd.isCommand(CMD_ADD)) executeCMDADD(cmd);
	else if(cmd.isCommand(CMD_DELETE)) executeCMDDELETE(cmd);
	else if(cmd.isCommand(CMD_SHOW)) executeCMDSHOW(cmd);
	else if(cmd.isCommand(CMD_COMPARE)) executeCMDCOMPARE(cmd);
	else if(cmd.isCommand(CMD_REORDER)) executeCMDREORDER(cmd);
	else if(cmd.isCommand(CMD_FOLLOW)) executeCMDFOLLOW(cmd);
}

//CMD SHOW COMMANDS
void MyTunes::executeCMDSHOW(Command cmd){
	//show recordings
	//show recordings -r recording_id
	//show songs
	//show songs -s song_id
	//show tracks
	//show tracks -t track_id
	//show users
	//show users -u user_id

	enum arguments {SHOW, COLLECTION, FLAG, MEMBER_ID};
	if(cmd.isTokenAt(COLLECTION, "songs") && !cmd.hasToken("-s"))
	songs.showOn(view);
	else if(cmd.isTokenAt(COLLECTION, "songs") && cmd.hasToken("-s"))
	songs.showOn(view, stoi(cmd.getToken(MEMBER_ID)));
	else if(cmd.isTokenAt(COLLECTION, "recordings") && !cmd.hasToken("-r"))
	recordings.showOn(view);
	else if(cmd.isTokenAt(COLLECTION, "recordings") && cmd.hasToken("-r"))
	recordings.showOn(view, stoi(cmd.getToken(MEMBER_ID)));
	else if(cmd.isTokenAt(COLLECTION, "tracks") && !cmd.hasToken("-t"))
	tracks.showOn(view);
	else if(cmd.isTokenAt(COLLECTION, "tracks") && cmd.hasToken("-t"))
	tracks.showOn(view, stoi(cmd.getToken(MEMBER_ID)));
	else if(cmd.isTokenAt(COLLECTION, "users") && !cmd.hasToken("-u"))
	users.showOn(view);
	else if(cmd.isTokenAt(COLLECTION, "users") && cmd.hasToken("-u"))
	users.showOn(view, cmd.getToken(MEMBER_ID));
	else view.printOutput("EXECUTING: " + cmd.getCommandString());
}

//CMD ADD COMMANDS
void MyTunes::executeCMDADD(Command cmd){
	//add recording
	//add -r id title artist producer year
	//add -r 103 "Beatles For Sale" "Beatles" "George Martin" 1964
	//add -r ? "Beatles For Sale" "Beatles" "George Martin" 1964
	//add song
	//add -s sid title composer //add song
	//add -s 1001 "Misery" "Paul McCartney, John Lennon"
	//add -s ? "Misery" "Paul McCartney, John Lennon"
	//add track
	//add -t trackID albumID songID track_number
	//add -t 12 100 1000 1
	//add -t 12 null 1000 1 //add track not on recording
	//add -t ? 100 1000 1
	//add -t ? null 1000 1  //add track not on recording
	//add user
	//add -u user_id name
	//add -u ajones "Anne Jones"
	//add playlist
	//add -p user_id, playlist_name
	//add -p ajones "Driving Songs"
	//add playlist track
	//add -l user_id playlist_name track_id
	//add -l gjones "mysongs" 6

	if(cmd.hasToken("-s")) executeAddSong(cmd);
	else if(cmd.hasToken("-r")) executeAddRecording(cmd);
	else if(cmd.hasToken("-t")) executeAddTrack(cmd);
	else if(cmd.hasToken("-u")) executeAddUser(cmd);
	else if(cmd.hasToken("-p")) executeAddPlaylist(cmd);
	else if(cmd.hasToken("-l")) executeAddPlaylistTrack(cmd);
	else view.printOutput("EXECUTING: " + cmd.getCommandString());
}

//Individual Add Commands
void MyTunes::executeAddSong(Command cmd){
    //add song
    //add -s sid title composer //add song
    //add -s 1001 "Misery" "Paul McCartney, John Lennon"
    //add -s ? "Misery" "Paul McCartney, John Lennon"
	enum arguments {ADD, _S, ID, TITLE, COMPOSER};

	if(!cmd.isValidIndex(cmd.getToken(ID))) return;
	int id = -1;
	if(cmd.isTokenAt(ID,"?")) id = nextAvailableSongID++;
    else id = stoi(cmd.getToken(ID));

	if(nextAvailableSongID <= id) nextAvailableSongID = id + 1;

	Song* song = new Song(
	  cmd.getToken(TITLE),
	  cmd.getToken(COMPOSER),
	  id
	);
	if(song == NULL) return;
	songs.add(*song);
	view.printOutput("EXECUTING: ADD SONG " + cmd.getCommandString());
}

void MyTunes::executeAddRecording(Command cmd){
    //add recording
    //add -r id title artist producer year
    //add -r 103 "Beatles For Sale" "Beatles" "George Martin" 1964
    //add -r ? "Beatles For Sale" "Beatles" "George Martin" 1964
	enum arguments {ADD, _R, ID, TITLE, ARTIST, PRODUCER, YEAR};

	if(!cmd.isValidIndex(cmd.getToken(ID))) return;

	int id = -1;
	if(cmd.isTokenAt(ID,"?")) id = nextAvailableRecordingID++;
    else id = stoi(cmd.getToken(ID));
	if(nextAvailableRecordingID <= id) nextAvailableRecordingID = id + 1;

	Recording* recording = new Recording(
	  cmd.getToken(TITLE),
	  cmd.getToken(ARTIST),
	  cmd.getToken(PRODUCER),
	  cmd.getToken(YEAR),
	  id
	);
	if(recording == NULL) return;
	recordings.add(*recording);
	view.printOutput("EXECUTING: ADD RECORDING " + cmd.getCommandString());
}
void MyTunes::executeAddTrack(Command cmd){
    //add track
    //add -t trackID albumID songID track_number
    //add -t 12 100 1000 1
	//add -t 12 null 1000 1 //add track not on recording
    //add -t ? 100 1000 1
	//add -t ? null 1000 1  //add track not on recording

	enum arguments {ADD, _T, ID, RECORDING_ID, SONG_ID, TRACK_NUMBER};

	if(!cmd.isValidIndex(cmd.getToken(ID))) return;
	if(!cmd.isValidIndex(cmd.getToken(SONG_ID))) return;
	if(!cmd.isValidIndex(cmd.getToken(TRACK_NUMBER))) return;

	int id = -1;
	if(cmd.isTokenAt(ID,"?")) id = nextAvailableTrackID++;
    else id = stoi(cmd.getToken(ID));
	if(nextAvailableTrackID <= id) nextAvailableTrackID = id + 1;

	Recording * recording;
	//tracks don't have to be associated with recordings
	if(cmd.getToken(RECORDING_ID).compare("null") == 0) recording = NULL;
	else {
		if(!cmd.isValidIndex(cmd.getToken(RECORDING_ID))) return;
		recording = recordings.findByID(stoi(cmd.getToken(RECORDING_ID)));
	}

	int track_number = stoi(cmd.getToken(TRACK_NUMBER));
	Track* track = new Track(
	  id, songs.findByID(stoi(cmd.getToken(SONG_ID)))
	);
	if(track == NULL) return;
	tracks.add(*track);
	if(recording != NULL) recording->addTrack(*track, track_number);
	view.printOutput("EXECUTING: ADD TRACK " + cmd.getCommandString());
}
void MyTunes::executeAddUser(Command cmd){
    //add user
    //add -u user_id name
    //add -u ajones "Anne Jones"
	enum arguments {ADD, _U, USERID, NAME};

	User* user = new User(
	  cmd.getToken(USERID),
	  cmd.getToken(NAME)
	  );

	if(user == NULL) return;
	users.add(*user);
	view.printOutput("EXECUTING: ADD USER " + cmd.getCommandString());
}
void MyTunes::executeAddPlaylist(Command cmd){
    //add playlist
    //add -p user_id, playlist_name
    //add -p ajones "Driving Songs"

	enum arguments {ADD, _P, USERID, PLAYLIST_NAME};

	User* user = users.findByID(cmd.getToken(USERID));
	if(user == NULL) return;
	Playlist * playlist = new Playlist(cmd.getToken(PLAYLIST_NAME));
	if(playlist == NULL) return;
	user->addPlaylist(*playlist);
	view.printOutput("EXECUTING: ADD PLAYLIST " + cmd.getCommandString());
}
void MyTunes::executeAddPlaylistTrack(Command cmd){
    //add playlist track
    //add -l user_id playlist_name track_id
    //add -l gjones "mysongs" 6

	enum arguments {ADD, _L, USERID, PLAYLIST_NAME, TRACK_ID};

	if(!cmd.isValidIndex(cmd.getToken(TRACK_ID))) return;

	User * user = users.findByID(cmd.getToken(USERID));
	if(user == NULL) return;
	Playlist * playlist = user->findPlaylist(cmd.getToken(PLAYLIST_NAME));
	if(playlist == NULL) return;
	Track * track = tracks.findByID(stoi(cmd.getToken(TRACK_ID)));
	if(track == NULL) return;
	playlist->addTrack(*track);

}

//CMD DELETE COMMANDS
void MyTunes::executeCMDDELETE(Command cmd){
	if(cmd.hasToken("-u") && cmd.hasToken("-p") && cmd.hasToken("-t") && cmd.hasToken("-GLOBAL")){
	    //Cascaded GLOBAL Delete
	    string newCommandString = "delete -t " + cmd.getToken("-t");
	    Command c = Command(newCommandString);
		executeDeleteTrack(c);
	}
	else if(cmd.hasToken("-u") && cmd.hasToken("-p") && cmd.hasToken("-t"))
		executeDeleteUserPlaylistTrack(cmd);
	else if(cmd.hasToken("-u") && cmd.hasToken("-p"))
		executeDeleteUserPlaylist(cmd);
	else if(cmd.hasToken("-u"))
		executeDeleteUser(cmd);
	else if(cmd.hasToken("-r"))
		executeDeleteRecording(cmd);
	else if(cmd.hasToken("-t"))
		executeDeleteTrack(cmd);
    else if(cmd.hasToken("-s"))
		executeDeleteSong(cmd);
	else view.printOutput("EXECUTING: " + cmd.getCommandString());
}
void MyTunes::executeDeleteRecording(Command cmd){
	//delete -r 1000
	enum arguments {DELETE, _R, ID};

	if(!cmd.isValidIndex(cmd.getToken(ID))) return;

	Recording* recording = recordings.findByID(stoi(cmd.getToken(ID)));
	if(recording == NULL) return;
	recordings.remove(*recording);
	view.printOutput("EXECUTING: DELETE RECORDING " + cmd.getCommandString());
}
void MyTunes::executeDeleteUser(Command cmd){
	//delete -u ajones
	enum arguments {DELETE, _U, USER_ID};

	User* user = users.findByID(cmd.getToken(USER_ID));
	if(user == NULL) return;
	users.remove(*user);
	view.printOutput("EXECUTING: DELETE USER " + cmd.getCommandString());
}
void MyTunes::executeDeleteUserPlaylist(Command cmd){
	//delete -u ajones -p favourites
	enum arguments {DELETE, _U, USER_ID, _P, PLAYLIST_NAME};
	User* user = users.findByID(cmd.getToken(USER_ID));
	if(user == NULL) return;
	Playlist * playlist = users.findByID(cmd.getToken(USER_ID))->findPlaylist(cmd.getToken(PLAYLIST_NAME));
	if(playlist == NULL) return;
	// detach so that the host cannot refer to the playlist (so it can be deleted from memory)
	playlist->stopFollowing();
	// make sure all the playlists observers stop refering to the playlist (so it can be deleted from memory)
	for (set<Observer*>::iterator it = playlist->getObservers().begin(); it != playlist->getObservers().end(); ++it)
			 ((Playlist*) (*it))->stopFollowing();
	user->removePlaylist(*playlist);
	view.printOutput("EXECUTING: DELETE USER PLAYLIST " + cmd.getCommandString());
}
void MyTunes::executeDeleteUserPlaylistTrack(Command cmd){
	//delete -u ajones -p favourites -t 70
	//delete -u ajones -p favourites -t 70 -GLOBAL
	enum arguments {DELETE, _U, USER_ID, _P, PLAYLIST_NAME, _T, TRACK_ID};
	string user_id = cmd.getToken("-u");
	string playlistName = cmd.getToken("-p");
	string trackIDstring = cmd.getToken("-t");
    if(!cmd.isValidIndex(trackIDstring)) return;
    int trackIndex = stoi(trackIDstring);
	User* user = users.findByID(cmd.getToken(USER_ID));
	if(user == NULL) return;
	Playlist * playlist = user->findPlaylist(cmd.getToken(PLAYLIST_NAME));
	if(playlist == NULL) return;
	Track * track = tracks.findByID(trackIndex);
	if(track == NULL) return;
	playlist->removeTrack(*track);
	view.printOutput("EXECUTING: DELETE USER PLAYLIST TRACK " + cmd.getCommandString());
}
void MyTunes::executeDeleteTrack(Command cmd){
	//delete -t track_id
	enum arguments {DELETE, _T, TRACK_ID};
	string trackIDstring = cmd.getToken("-t");
    if(!cmd.isValidIndex(trackIDstring)) return;
	int trackIndex = stoi(trackIDstring);
	Track * track = tracks.findByID(trackIndex);
	if(track == NULL) return;

	//PERFORM A CASCADED DELETE
	vector<User*> theUsers = users.getCollection();
	for(vector<User*>::iterator itr = theUsers.begin(); itr != theUsers.end(); itr++){
		User* user = *itr;
		user->removeTrack(*track);
	}
	vector<Recording*> theRecordings = recordings.getCollection();
	for(vector<Recording*>::iterator itr = theRecordings.begin(); itr != theRecordings.end(); itr++){
		Recording* recording = *itr;
		recording->removeTrack(*track);
	}

	tracks.remove(*track);

}

void MyTunes::executeDeleteSong(Command cmd){
	//delete -s 1000
	enum arguments {DELETE, _S, ID};

	if(!cmd.isValidIndex(cmd.getToken(ID))) return;

	Song* song = songs.findByID(stoi(cmd.getToken(ID)));
	if(song == NULL) return;

	//Perform Cascaded Delete
	vector<Track*> theTracks = tracks.getCollection();
	for(vector<Track*>::iterator itr = theTracks.begin(); itr != theTracks.end(); itr++){
		Track* track = *itr;
		Song* trackSong = track->getSong();
		if(song == trackSong){
	       //Cascaded GLOBAL Delete
	       string newCommandString = "delete -t " + to_string(track->getID());
	       Command c = Command(newCommandString);
		   executeDeleteTrack(c);
		}
	}
	songs.remove(*song);
	view.printOutput("EXECUTING: DELETE SONG " + cmd.getCommandString());
}

void MyTunes::executeCMDCOMPARE(Command cmd) {
	enum arguments {COMPARE, _U1, USERID_1, _U2, USERID_2};

	const string U_1 = "-u1";
	const string U_2 = "-u2";

	// setup the base case where the users exist
	if(users.findByID(cmd.getToken(U_1)) == NULL || users.findByID(cmd.getToken(U_2)) == NULL) {
		cout << "INVALID USER(S) ENTERED" << endl << endl;
		return;
	}

	// setup the base case where the users are the same
	if(users.findByID(cmd.getToken(U_1)) == users.findByID(cmd.getToken(U_2))) {
		cout << "THE SAME USER IS BEING COMPARED" << endl << endl;
		return;
	}

	// intialize the set of tracks
	set<Track*> firstUserTracks;
	set<Track*> secondUserTracks;
	vector<Track*> sharedTracks;

	// intialize the users
	User * firstUser = users.findByID(cmd.getToken(U_1));
	User * secondUser = users.findByID(cmd.getToken(U_2));

	// iterator to go through all of the first users playlists and each of those playlists tracks
	for (Playlist * tempPlaylist : firstUser->getPlaylists())
	for (Track * tempTrack : tempPlaylist->getTracks())
	firstUserTracks.insert(tempTrack);

	// iterator to go through all of the second users playlists and each of those playlists tracks
	for (Playlist * tempPlaylist : secondUser->getPlaylists())
	for (Track * tempTrack : tempPlaylist->getTracks())
	secondUserTracks.insert(tempTrack);

	// intersect the two shared song sets
	set_intersection(firstUserTracks.begin(), firstUserTracks.end(), secondUserTracks.begin(), secondUserTracks.end(), back_inserter(sharedTracks));

	// if they share no common songs, print out a message
	if(sharedTracks.size() == 0)
	cout << endl << "USERS " << firstUser->getUserID() << " AND " << secondUser->getUserID() << " SHARE NO COMMON SONGS" << endl << endl;
	// otherwise print out the shared tracks
	else {
		cout << endl << "SHARED TRACKS:" << endl;
		for(Track * t : sharedTracks)
		cout << "\t" << *t;
		cout << endl;
	}
	return;
}

void MyTunes::executeCMDREORDER(Command cmd) {
	enum arguments {REORDER, _U, USERID, _P, PLAYLIST_ID};

	// base case where the user or playlist or input is invalid
	if(users.findByID(cmd.getToken(USERID)) == NULL || users.findByID(cmd.getToken(USERID))->findPlaylist(cmd.getToken(PLAYLIST_ID)) == NULL) {
		cout << "INVALID USER OR PLAYLIST ENTERED" << endl << endl;
		return;
	}

	// local variable for the user and playlist
	User * user = users.findByID(cmd.getToken(USERID));
	Playlist * playlist = user->findPlaylist(cmd.getToken(PLAYLIST_ID));

	// display before
	cout << "BEFORE REORDER:" << endl;
	for(Track * t : playlist->getTracks())
	cout << "\t" << t->toString() << endl;
	cout << endl;

	// alphabetically sort
	if(cmd.getNumTokens() == 5) {
		// intialize a sorted playlist
		list<Track*> sortedPlaylist;

		// add the tracks to that list
		for(Track * t : playlist->getTracks())
		sortedPlaylist.push_back(t);

		// sort the list
		sortedPlaylist.sort([](Track * f, Track *s) { return f->getSong()->getTitle() < s->getSong()->getTitle(); });

		// empty the playlist
		for(Track * t : playlist->getTracks())
		playlist->removeTrack(*t);

		// add the tracks to the original playlist (in sorted order)
		for(Track * t : sortedPlaylist)
		playlist->addTrack(*t);
	}

	// manual ordering
	else if(cmd.getNumTokens() > 5) {
		// set the temp playlist to be playlist
		Track * tempPlaylist[playlist->getTracks().size()];
		int tempSize = sizeof(tempPlaylist)/sizeof(*tempPlaylist);

		for(int i = 0; i < tempSize; i++)
		tempPlaylist[i] = playlist->getTracks().at(i);

		// empty the playlist
		for(Track * t : playlist->getTracks())
		playlist->removeTrack(*t);

		// declare variables
		const int baseParam = 5;
		int i = baseParam;

		// All the tokens that were entered through the command
		while(i < cmd.getNumTokens()) {
			// if there are more parameters than elements
			if(i >= 5 + tempSize)
				break;
			// if the element is within the range of the array, then add it
			if(stoi(cmd.getTokens().at(i)) <= tempSize && stoi(cmd.getTokens().at(i)) > 0)
				playlist->addTrack(*tempPlaylist[stoi(cmd.getTokens().at(i++))-1]);
			else // otherwise skip to the next value
				i++;
		}

		// Any leftover parameters that will automatically be added to the end
		for(int j = 0; j < tempSize; j++)
				playlist->addTrack(*tempPlaylist[j]);
	}

	// display after
	cout << "AFTER REORDER:" << endl;
	for(Track * t : playlist->getTracks())
	cout << "\t" << t->toString() << endl;
	cout << endl;
	return;
}

void MyTunes::executeCMDFOLLOW(Command cmd) {
	enum arguments {FOLLOW, _U, FOLLOWER_ID, _P, PLAYLIST_ID, _F, HOST_ID};

	// stop following (FR4.1.2)
	if(cmd.getToken(HOST_ID).compare("stop") == 0 && users.findByID(cmd.getToken(FOLLOWER_ID)) != NULL) {
		users.findByID(cmd.getToken(FOLLOWER_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID))->stopFollowing();
		return;
	}

	// base case
	if(users.findByID(cmd.getToken(HOST_ID)) == NULL || users.findByID(cmd.getToken(FOLLOWER_ID)) == NULL) {
		cout << "INVALID USER(S) ENTERED" << endl << endl;
		return;
	}

	// base case (FR4.1.6)
	if(users.findByID(cmd.getToken(HOST_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID)) == NULL || users.findByID(cmd.getToken(FOLLOWER_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID)) == NULL) {
		cout << "USER(S) DO NOT HAVE A PLAYLIST WITH THE CORRESPONDING TITLE " << "\'" << cmd.getToken(PLAYLIST_ID) << "\'" << endl << endl;
		return;
	}

	// base case (FR4.1.5)
	if(cmd.getToken(HOST_ID).compare(cmd.getToken(FOLLOWER_ID)) == 0) {
		cout << "YOU CAN NOT FOLLOW YOUR OWN PLAYLIST" << endl << endl;
		return;
	}

	// base case (FR4.1.4)
	if(users.findByID(cmd.getToken(HOST_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID))->getFollowing() == users.findByID(cmd.getToken(FOLLOWER_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID))) {
		Playlist * follower = users.findByID(cmd.getToken(HOST_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID));
		Playlist * host = users.findByID(cmd.getToken(FOLLOWER_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID));
		cout << "FOLLOWING HIERARCHY IS BEING REVERSED:"<< endl;
		cout << "\t BEFORE: " << cmd.getToken(HOST_ID) << "-->" << cmd.getToken(FOLLOWER_ID) << endl;
		cout << "\t AFTER: " << cmd.getToken(FOLLOWER_ID) << "-->" << cmd.getToken(HOST_ID) << endl;

		follower->stopFollowing();
		host->startFollowing(*follower);
		return;
	}

	// begin following
	if(users.findByID(cmd.getToken(HOST_ID)) != NULL && users.findByID(cmd.getToken(FOLLOWER_ID)) != NULL &&
	users.findByID(cmd.getToken(HOST_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID)) != NULL && users.findByID(cmd.getToken(FOLLOWER_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID)) != NULL) {
		Playlist * host = users.findByID(cmd.getToken(HOST_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID));
		Playlist * follower = users.findByID(cmd.getToken(FOLLOWER_ID))->findPlaylist(cmd.getToken(PLAYLIST_ID));
		follower->startFollowing(*host);
	}
}
