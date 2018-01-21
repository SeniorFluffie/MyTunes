MyTunes is a C++ implementation for a music listening app featuring various songs, tracks, artists, and playlists.
Utilizing various itemized requirements, agile development patterns, and an SQL database of "The Beatles" songs, the text-based CMD MyTunes prototype functions to an optimal degree. On top of the traditional add, remove, and show commands associated with a music library program, MyTunes has additional functionality with follow, compare, and reorder functions. 

There is a test script, "partOneScript.txt", to verify the corectness of basic adding, removing, playlist, and album functionality.
A second test script, "partTwoScript.txt", that verifies the additional follow, compare, and reorder functions that were added for additional user benefit.
---------------------------------------------INFO--------------------------------------------------
Michael Kazman 101037568
Tao Guo 100968344

--------------------------------------------UNZIP-------------------------------------------------
Type the command exactly as shown below:
unzip COMP2404A4.zip

--------------------------------------------PART1-------------------------------------------------
To compile type the command exactly as shown below:
make clean mytunes

To run type the command exactly as shown below:
./mytunes

When running the program type the command exactly as shown below to run the part 1 testing script:
.read partOneScript.txt

--------------------------------------------PART2-------------------------------------------------
Comparing Songs: (A function to compare songs users have in common with each other. Approved by Louis Nel)
  FR4.1.1) 1. Must be able to compare objects through the scope of a user’s playlists.
    a.	If the command ‘-compare -u1 ajones -u2 gjones’ is executed, all shared playlist tracks must be displayed from all of the user’s playlists.

  FR4.1.2) 2.	The code should withstand a user trying to compare to themselves. Withstand means you must either accommodate it or prevent it from happening. The code should not crash.

  FR4.1.3) 3.	The common/shared songs between users must be displayed in title case.

  FR4.1.4) 4.	Must not display duplicates of any songs between the users.
    a.	If users have the same song(s) in multiple playlists they will not be displayed more than once.

Reordering Songs:
  FR4.1.5) 1.	The code should withstand a user trying to reorder a playlist that does not exist. Withstand means you must either accommodate it or prevent it from happening. The code should not crash.

  FR4.1.6) 2.	The playlist must not change the TrackID values whatsoever. The TrackID values associate the Tracks with certain recordings and songs, and thus should not be changed under any circumstances.

  FR4.1.7) 3. The number of parameters provided (let us say n) re-orders the first n tracks in that playlist. It must accommodate the number of parameters being less than, equal to, or more than the number of tracks.

  FR4.1.8) 4.	Should have an alternate sorting method(s) (alphabetical) that can be used in addition to the manual sorting method.

  When running the program type the command exactly as shown below to run the testing script:
  .read partTwoScript.txt

----------------------------------------EXTRA DETAILS---------------------------------------------
The program reads the insert_beatles_tracks_rev1.txt script on startup.
To disable this behaviour comment out the lines:

  //initialize app with input script
  Command cmd = Command(".read insert_beatles_tracks_rev1.txt");
  executeCommand(cmd);

in the run() method at the start of the UI.cpp file.
