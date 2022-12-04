/**
 * @file part2.cpp
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
#include <cmath>
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
    map<string, long> mGramarOccur, mGramarOccurPrev;
    vector<char> vPolymer, vNewPolymer;
    string sTemp1 = "  ", sTemp2 = "  ";
    long iCount;

    if (!siReadAndProcessInput("input.txt", mGrammar, vPolymer))
    {
        cout << "Extracted grammar has " << mGrammar.size() << " rules." << endl;

        /* Create a full set of alphabet at start from initial polymer and grammar */
        set<char> sAlphabet(vPolymer.begin(), vPolymer.end());

        for (auto &&rule : mGrammar) {
            sAlphabet.insert(rule.second);
            mGramarOccur[rule.first] = 0;
        }

        for (size_t iPos = 0; iPos < vPolymer.size()-1; iPos++)
        {
            sTemp1[0] = vPolymer[iPos];
            sTemp1[1] = vPolymer[iPos+1];
            mGramarOccur[sTemp1]++;
        }

        for (size_t iIter = 0; iIter <= 40; iIter++)
        {
            map<string, long> mGramarOccurNew;
            mGramarOccurPrev = mGramarOccur;

            for (auto &&elem : mGramarOccur)
            {
                sTemp1[0] = elem.first[0]; sTemp1[1] = mGrammar[elem.first];
                sTemp2[0] = mGrammar[elem.first]; sTemp2[1] = elem.first[1];

                mGramarOccurNew[sTemp1] += elem.second;
                mGramarOccurNew[sTemp2] += elem.second;
            }

            mGramarOccur = mGramarOccurNew;

            iCount = 0;
            for (auto &&elem : mGramarOccur)
                iCount += elem.second;

            cout << "At iteration " << iIter << ", Polymer size is: " << (iCount/2)+1 << endl;
        }

        long iMax = 0, iMin = __LONG_MAX__, iVal, iLetCount;
        for (auto &&letter : sAlphabet)
        {
            iLetCount = 0;
            for (auto &&elem : mGramarOccurPrev)
            {
                if (elem.first[0] == letter)
                    iLetCount += elem.second;
                if (elem.first[1] == letter)
                    iLetCount += elem.second;
            }

            iVal = ceil((double)iLetCount/2);

            if (iVal > iMax)
                iMax = iVal;
            if (iVal < iMin)
                iMin = iVal;

            cout << letter << " occurs " << iVal << " times." << endl;
        }

        cout << "Computed value is " << iMax-iMin << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}
