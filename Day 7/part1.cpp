/**
 * @file part1.cpp
 * @author Josep Dols (jododlar@gmail.com)
 * @brief Day 7 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "../Common/utils.hpp"

using namespace std;

short int siReadAndProcessInput(string sFileName, vector<int> &vPopulation)
{
    ifstream fInputFile;
    string sLine;
    size_t zPos;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        getline(fInputFile, sLine);

        if (sLine.empty())
            return 1;

        while ((zPos = sLine.find(',')) != string::npos)
        {
            vPopulation.push_back(stoi(sLine.substr(0,zPos)));
            sLine.erase(0, zPos+1);
        }
        vPopulation.push_back(stoi(sLine.substr(0,zPos)));

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
    vector<int> vPositions;
    int iNumOfElems = 0;
    int iMidPosition = 0;
    int iBestPosition = 0;

    if (!siReadAndProcessInput("input.txt", vPositions))
    {
        cout << "After processing, there are " << vPositions.size() << " positions." << endl;
        cout << "Range is <" << *min_element(vPositions.begin(),vPositions.end()) << " - " << *max_element(vPositions.begin(),vPositions.end()) << ">" << endl;

        iNumOfElems = vPositions.size();
        iMidPosition = iNumOfElems / 2;

        /* Get best position */
        if (iNumOfElems % 2 == 0)
        {
            vector<int> vPositionsA = vPositions;
            vector<int> vPositionsB = vPositions;

            auto median_it1 = vPositionsA.begin() + vPositionsA.size() / 2 - 1;
            auto median_it2 = vPositionsB.begin() + vPositionsB.size() / 2;

            nth_element(vPositionsA.begin(), median_it1, vPositionsA.end());
            nth_element(vPositionsB.begin(), median_it2, vPositionsB.end());

            cout << "Best positions are: [" << vPositionsA[iMidPosition] << "," << vPositionsB[iMidPosition-1] << "] -> " << (*median_it1 + *median_it2)/2 << endl;
            iBestPosition = (*median_it1 + *median_it2)/2;
        }
        else
        {
            vector<int> vPositionsA = vPositions;
            auto median_it = vPositionsA.begin() + vPositionsA.size() / 2;
            nth_element(vPositionsA.begin(), median_it, vPositionsA.end());
            cout << "Best position is " << *median_it << endl;
            iBestPosition = *median_it;
        }

        /* Calculate distances from each point */
        int iAccumulated = 0;
        for (auto &&pos : vPositions)
        {
            iAccumulated += abs(pos-iBestPosition);
        }

        cout << "Accumulated distance is " << iAccumulated << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}
