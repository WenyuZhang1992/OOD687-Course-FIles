//***************************************************************
// set2.cpp -- Modified from dir2.cpp
// From the book "Win32 System Services: The Heart of Windows 95
// and Windows NT"
// by Marshall Brain
// Published by Prentice Hall
//
// Copyright 1995, by Prentice Hall.
//
// This code recursively traverses all directories below the 
// current directory
//
// Jim Fawcett, 2/5/98 - added sorted lists of files, built in 
//                       PrintFindData(...) and displayed in main()
//			     - uses sets of strings from std library
//***************************************************************

// dir2.cpp

// disable truncation warnings
#pragma warning( disable : 4786 ) 

#include <iostream> 
#include <set>
#include <iterator>
#include <string>
#include <windows.h>

using namespace std;


// prints information about a file
void PrintFindData(WIN32_FIND_DATA *findData, set<string> &sos)
{	
	cout << "\t";
	cout << findData->cFileName;
	cout << "\t(" << findData->nFileSizeLow << ")";
	cout << endl;
  sos.insert(findData->cFileName);
}

// Recursively lists directories
void ListDirectoryContents(char *dirName, 
	char *fileMask, set<string> &sos)
{
	char *fileName;
	char curDir[ 256 ];
	char fullName[ 256 ];
	HANDLE fileHandle;
	WIN32_FIND_DATA findData;

	// save current dir so it can restore it
	if( !GetCurrentDirectory( 256, curDir) ) 
		return;
	
	// if the directory name is neither . or .. then
	// change to it, otherwise ignore it
	if( strcmp( dirName, "." ) && 
		strcmp( dirName, ".." ) )
	{
		if( !SetCurrentDirectory( dirName ) ) 
			return;
	}
	else 
		return;

	// print out the current directory name
	if( !GetFullPathName( fileMask, 256, fullName,
		&fileName ) ) 
		return;
	cout << endl << "Directory - " << fullName 
		<< endl;

	// Loop through all files in the directory
	fileHandle = FindFirstFile( fileMask, 
		&findData );
	while ( fileHandle != INVALID_HANDLE_VALUE )
	{
		// If the name is a directory,
		// recursively walk it. Otherwise print
		// print the file's data
		if( findData.dwFileAttributes &
			FILE_ATTRIBUTE_DIRECTORY )
		{
			ListDirectoryContents( findData.cFileName,
				fileMask, sos );
		}
		else
			PrintFindData( &findData, sos );

  		// loop thru remaining entries in the dir
		if (!FindNextFile( fileHandle, &findData ))
			break;
 	}
	
	// clean up and restore directory
	FindClose( fileHandle );
	SetCurrentDirectory( curDir );

  // print out the current directory name
	if( !GetFullPathName( fileMask, 256, fullName,
		&fileName ) ) 
		return;
	cout << endl << "Directory - " << fullName 
		<< endl;

}

int main(int argc, char *argv[])
{
	char	curDir[ 256 ];

	if( !GetCurrentDirectory( 256, curDir ) )
	{
		cerr << "Couldn't get the current directory." 
			<< endl;
		return( 1 );
	}

	// List all files, starting with the 
	// current directory

  set<string> sos;
  ListDirectoryContents( curDir, "*.*" , sos);

  cout << "\n  sorted list of all files:\n";
  set<string>::iterator si;
  for(si = sos.begin(); si != sos.end(); si++)
    cout << "    " << *si << endl;

  return( 0 );
}
