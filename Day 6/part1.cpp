/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 6 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

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
    vector<int> vPopulation;
    int iNewCandidates = 0;

    if (!siReadAndProcessInput("input.txt", vPopulation))
    {
        cout << "Initial population is " << vPopulation.size() << "." << endl;

        for (size_t iCycle = 0; iCycle < 80; iCycle++)
        {
            iNewCandidates = 0;
            for (auto &&elem : vPopulation)
            {
                if (elem == 0)
                {
                    elem = 6;
                    iNewCandidates++;
                }
                else
                {
                    elem--;
                }
            }

            for (size_t i = 0; i < iNewCandidates; i++)
            {
                vPopulation.push_back(8);
            }
        }

        cout << "After 80 days, there are " << vPopulation.size() << " lanternfishes." << endl;

    }
    else
    {
        return 1;
    }

    return 0;
}
