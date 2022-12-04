/**
 * @file part2.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 2 - Part 2 of the Advent of Code 2022
 * @version 0.1
 * @date 2022-12-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include <algorithm>
#include <cctype>
#include <climits>
#include <iostream>
#include <fstream>
#include <list>
#include <numeric>
#include <map>
#include <queue>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/* Combinations matrix
Rock     - A    4      8      3
Paper    - B    1      5      9
Scissors - C    7      2      6
Response        X      Y      Z
              Rock   Paper  Scissors
*/
int combinations[3][3] = {{4,8,3},{1,5,9},{7,2,6}};
map<char, int> letter_to_pos = {
    {'A', 0},
    {'B', 1},
    {'C', 2},
    {'X', 0},
    {'Y', 1},
    {'Z', 2}
};

map<char, char> letter_to_lose = {
    {'A', 'Z'},
    {'B', 'X'},
    {'C', 'Y'}
};
map<char, char> letter_to_draw = {
    {'A', 'X'},
    {'B', 'Y'},
    {'C', 'Z'}
};
map<char, char> letter_to_win = {
    {'A', 'Y'},
    {'B', 'Z'},
    {'C', 'X'}
};

short int siReadAndProcessInput(string sFileName, vector<int> &lList)
{
    ifstream fInputFile;
    string sLine;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        lList.clear();

        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                continue;

            switch (sLine.substr(2,1)[0])
            {
            case 'X': /* I need to lose */
                lList.push_back(combinations[letter_to_pos[sLine.substr(0,1)[0]]][letter_to_pos[letter_to_lose[sLine.substr(0,1)[0]]]]);
                break;
            case 'Y': /* I need to draw */
                lList.push_back(combinations[letter_to_pos[sLine.substr(0,1)[0]]][letter_to_pos[letter_to_draw[sLine.substr(0,1)[0]]]]);
                break;
            case 'Z': /* I need to win */
                lList.push_back(combinations[letter_to_pos[sLine.substr(0,1)[0]]][letter_to_pos[letter_to_win[sLine.substr(0,1)[0]]]]);
                break;
            default:
                break;
            }

            cout << sLine.substr(0,1) << " vs. " << sLine.substr(2,1) << " -> " << lList.back() << endl;
        }

        fInputFile.close();
    }
    else
    {
        cout << "Error opening " << sFileName << " file." << endl;
        return 1;
    }

    return 0;
}

int main(int argc, char const *argv[])
{
    vector<int> lPuntuations;
    int iTotalScore = 0;

    if (!siReadAndProcessInput("input.txt", lPuntuations))
    {
        iTotalScore = accumulate(lPuntuations.begin(), lPuntuations.end(), 0);

        cout << "Total score obtained is " << iTotalScore << endl;

        return 0;
    }
    else
    {
        return 1;
    }
}
