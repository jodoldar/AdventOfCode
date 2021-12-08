/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 7 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-07
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <algorithm>
#include <iostream>
#include <fstream>
#include <numeric>
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

int getAcumulator(int difference)
{
    int iAcumulated = 0;

    for (size_t i = 1; i <= difference; i++)
    {
        iAcumulated += i;
    }

    return iAcumulated;
}
int main(int argc, char const *argv[])
{
    vector<int> vPositions;
    int iNumOfElems = 0;
    int iMidPosition = 0;
    float iBestPosition = 0;

    if (!siReadAndProcessInput("input.txt", vPositions))
    {
        cout << "After processing, there are " << vPositions.size() << " positions." << endl;
        cout << "Range is <" << *min_element(vPositions.begin(),vPositions.end()) << " - " << *max_element(vPositions.begin(),vPositions.end()) << ">" << endl;

        iNumOfElems = vPositions.size();
        iMidPosition = iNumOfElems / 2;

        /* Get best position */
        iBestPosition = accumulate(vPositions.begin(), vPositions.end(), 0, [](int a, int b){return a + b;}) / vPositions.size();
        cout << "Best position is " << iBestPosition << endl;

        /* Calculate distances from each point */
        int iAccumulated = 0;
        for (auto &&pos : vPositions)
        {
            iAccumulated += getAcumulator(abs(pos-iBestPosition));
        }

        cout << "Accumulated distance is " << iAccumulated << endl;
    }
    else
    {
        return 1;
    }

    return 0;
}
