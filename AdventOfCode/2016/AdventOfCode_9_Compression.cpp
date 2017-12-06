/*
  Description:  Wandering around a secure area, you come across a datalink port
                to a new part of the network. After briefly scanning it for
                interesting files, you find one file in particular that catches
                your attention. It's compressed with an experimental format, but
                fortunately, the documentation for the format is nearby.

                The format compresses a sequence of characters. Whitespace is
                ignored. To indicate that some sequence should be repeated, a
                marker is added to the file, like (10x2). To decompress this
                marker, take the subsequent 10 characters and repeat them 2
                times. Then, continue reading the file after the repeated data.
                The marker itself is not included in the decompressed output.

                If parentheses or other characters appear within the data
                referenced by a marker, that's okay - treat it like normal data,
                not a marker, and then resume looking for markers after the
                decompressed section.

  Example:      - ADVENT contains no markers and decompresses to itself with no
                changes, resulting in a decompressed length of 6.
                - A(1x5)BC repeats only the B a total of 5 times, becoming
                ABBBBBC for a decompressed length of 7.
                - (3x3)XYZ becomes XYZXYZXYZ for a decompressed length of 9.
                - A(2x2)BCD(2x2)EFG doubles the BC and EF, becoming ABCBCDEFEFG
                for a decompressed length of 11.
                - (6x1)(1x3)A simply becomes (1x3)A - the (1x3) looks like a
                marker, but because it's within a data section of another
                marker, it is not treated any differently from the A that comes
                after it. It has a decompressed length of 6.
                - X(8x2)(3x3)ABCY becomes X(3x3)ABC(3x3)ABCY (for a decompressed
                length of 18), because the decompressed data from the (8x2)
                marker (the (3x3)ABC) is skipped and not processed further.
                What is the decompressed length of the file (your puzzle input)?

                Don't count whitespace.

  Programmer:   Michael Duarte.

  Date:         12/10/2016
*/

#include <iostream>
#include <cmath>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>
#include <cctype>

using namespace std;

int getUncompressedLength(const string &input) {
  int result = input.length();
  int letters = 0;
  int times = 0;
  int startIndex = 0;
  for (int i = 0 ; i < input.length(); ++i ) {
    switch(input[i]){
      case '(':
        letters = atoi(input.c_str()+i+1);
        startIndex = i;
        break;

      case 'x':
        if (letters) {
          times = atoi(input.c_str()+i+1);
        }
        break;

      case ')':
        if (letters && times){
          cout << "\t" << letters << "x" << times;
          int lettersLeft = input.length() - i;
          if (letters > lettersLeft) {
            letters = lettersLeft;
            cout << ". Max letters: " << letters;
          }
          int expressionLen = i - startIndex + 1;
          result += letters * (times - 1);
          result -= expressionLen;
          cout << ". Expression is " << expressionLen << " chars long." << endl; 
          i += letters;
        }
        break;

      case ' ':
      case '\n':
      case '\t':
        --result;
        cout << "\tSpace found." << endl;
        break;

      default:
        if (!isdigit(input[i])) {
          letters = 0;
          times = 0;
          startIndex = 0;
        }
        break;
    }
  }
  return result;
}

void solve() {
  string input;
  while(!cin.eof()){
    // cin >> input;
    getline (cin,input);
    cout << getUncompressedLength(input) << endl;
  }
}