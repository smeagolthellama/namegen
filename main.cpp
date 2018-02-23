/**
    Copyright (C) 2016 Mark Gardner

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.(called license.txt)  If not, see <http://www.gnu.org/licenses/>.
*/
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;
const int NUMOFLETTERS = 56;
const char myletters[NUMOFLETTERS] = {"!abcdefghijklmnopqrstuvwxyz ABCDEFGHIJKLMNOPQRSTUVWXYZ#"};
int prob[NUMOFLETTERS][NUMOFLETTERS];
int letternumber ( char c );
char numberletter ( int last = ( rand() % NUMOFLETTERS ), int NUMOFLETTERS = ( rand() % NUMOFLETTERS ) );
int main()
{
	cout << "welcome to theHalfBloodStranger's random name generator!\n This program comes with ABSOLUTELY NO WARRANTY!\nSee license.txt for lots more details.";
	string filename;
	cout << "\n\n\tPlease type the name of the file that contains the names that you want to generate the names based on.\nI do not recomend giving this thing files that contain more than two of the same letter after each other. It would mean a higher probability of an infinite loop.\n\t";
	cin >> filename;
	ifstream f ( filename.c_str() );
	ofstream g ( "names.out.txt", ios::app );
	for ( int i = 0; i < NUMOFLETTERS; i++ ) {
		for ( int j = 0; j < NUMOFLETTERS; j++ ) {
			prob[i][j] = 0;
			//cout<<prob[i][j]<<' ';
		}
		//cout<<'\n';
	}
	char c;
	f.get ( c );
	int lastletter = letternumber ( c ), currentletter;
	///get probability.
	int i = 0;
	while ( !f.eof() ) {
		f.get ( c );
		i++;
		if ( c == '\n' ) {
			c = '!';
			continue;
		}
		if ( c == 0x00 ) {
			continue;
		}
		currentletter = letternumber ( c );
		prob[lastletter][currentletter]++;
		lastletter = letternumber ( c );
	}
	//cout << '\n' << i << '\n' << myletters << "\n\n\n\n";
	/*for ( int i = 0; i < NUMOFLETTERS; i++ ) {
		for ( int j = 0; j < NUMOFLETTERS; j++ ) {
			cout << prob[i][j] << ' ';
		}
		cout << '\n';
	}*/
	///now use probability to generate names.
	srand ( time ( 0 ) );
	for ( int i = 0; i < 20; i++ ) {
		lastletter = letternumber ( '!' );
		g << '!';
		c = 'a';
		for ( int j = 0; c != '#'; j++ ) {
			c = numberletter ( lastletter, rand() % NUMOFLETTERS );
			lastletter = letternumber ( c );
			g << c;
			cout << c;
		}
		cout << '\n';
		g << '\n';
	}
	f.close();
	g.close();
	return 0;
};
char numberletter ( int last, int n )
{
	/// use the probability to get a letter based on the previous letter.
	int myN = n, i;
	for ( i = 0; n >= 0; i++ ) {
		n -= prob[last][i];
		if ( n < 0 ) {
			return myletters[i];
		}
		if ( n == myN && i >= NUMOFLETTERS ) {
			return '#';
		}
		if ( i >= NUMOFLETTERS ) {
			i = 0;
		}
	}
	cout << "\n\nHOW DID I GET HERE???\n" << last << "\n" << myN << '\n';
	exit ( 11 ); ///Get REALY SCARED if you get this happening. It should be imossible.
};

int letternumber ( char c )
{
	/*if ( c == 0 ) {
		return '#';
	}*/
	for ( int i = 0; i < NUMOFLETTERS; i++ ) {
		if ( myletters[i] == c ) {
			return i;
		}
	}
	cout << "ERROR: unsuported character: \'" << c << "\' :" << ( int ) c;
	exit ( 10 );
};
