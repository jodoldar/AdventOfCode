/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 14 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <cctype>
#include <iostream>
#include <fstream>
#include <list>
#include <numeric>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>

#include "../Common/utils.hpp"

using namespace std;

const string RED_COLOR = "\033[31m";
const string RESET_COLOR = "\033[0m";

short int siReadAndProcessInput(string sFileName, map<string, char> &mGrammar, vector<char> &vPolymer)
{
    ifstream fInputFile;
    string sLine, sParA, sParB;
    size_t zPos;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        /* Custom read first line to extract polymer */
        getline(fInputFile, sLine);
        for (auto &&elem : sLine)
        {
            vPolymer.push_back(elem);
        }

        /* Extract grammar */
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                continue;

            zPos = sLine.find("->");
            sParA = sLine.substr(0,zPos-1);
            sParB = sLine.erase(0, zPos+3);

            cout << "Extracted '" << sParA << "' -> '" << sParB << "'." << endl;
            mGrammar[sParA] = sParB[0];
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
    map<string, char> mGrammar;
    vector<char> vPolymer, vNewPolymer;
    string sTemp;

    if (!siReadAndProcessInput("input.txt", mGrammar, vPolymer))
    {
        cout << "Extracted grammar has " << mGrammar.size() << " rules." << endl;

        for (size_t iIter = 0; iIter < 10; iIter++)
        {
            vNewPolymer.clear();
            vNewPolymer.push_back(vPolymer[0]);
            for (size_t iPos = 0; iPos < vPolymer.size()-1; iPos++)
            {
                sTemp.erase();
                sTemp.push_back(vPolymer[iPos]);
                sTemp.push_back(vPolymer[iPos+1]);
                if (mGrammar.find(sTemp) != mGrammar.end())
                    vNewPolymer.push_back(mGrammar[sTemp]);

                vNewPolymer.push_back(vPolymer[iPos+1]);
            }
            vPolymer = vNewPolymer;

            cout << "At iteration " << iIter << ", Polymer status is: ";
            for (auto &&i : vPolymer)
            {
                cout << i;
            }
            cout << endl;
        }

        int iMax = 0, iMin = vPolymer.size(), iVal;
        set<char> sAlphabet(vPolymer.begin(), vPolymer.end());
        for (auto &&letter : sAlphabet)
        {
            iVal = count(vPolymer.begin(), vPolymer.end(), letter);

            if (iVal > iMax)
                iMax = iVal;
            if (iVal < iMin)
                iMin = iVal;
        }

        cout << "Computed value is " << iMax-iMin << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}