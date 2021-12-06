/**
 * @file part2.cpp
 * @author Josep Dols (jododlar@gmail.com)
 * @brief Day 6 - Part 2 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-06
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <cstdint>
#include <cstring>

#include <algorithm>
#include <chrono>
#include <execution>
#include <iostream>
#include <fstream>
#include <numeric>
#include <string>
#include <utility>
#include <deque>

#include "../Common/utils.hpp"

using namespace std;

short int siReadAndProcessInput(string sFileName, deque<int> &vPopulation)
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
    deque<int> vPopulation;
    uint64_t iNewCandidates = 0;
    uint64_t iCurrentSize = 0;

    uint64_t states[9] = {};
    uint64_t new_states[9] = {};

    if (!siReadAndProcessInput("input.txt", vPopulation))
    {
        cout << "Initial population is " << vPopulation.size() << "." << endl;

        for (size_t iState = 0; iState < 9; iState++)
        {
            states[iState] = reduce(execution::par, vPopulation.begin(), vPopulation.end(), 0, [iState](int carr, int num){return num==iState ? carr+1 : carr;});
        }
        cout << "Initial states are: ";
        for (size_t i = 0; i < 9; i++)
        {
            cout << states[i] << " ";
        }
        cout << endl;

        for (size_t iCycle = 0; iCycle < 256; iCycle++)
        {
            cout << "Iteration " << iCycle << ", ";

            iNewCandidates = states[0];
            for (size_t iState = 1; iState < 9; iState++)
            {
                new_states[iState-1] = states[iState];
            }
            new_states[6] += iNewCandidates;
            new_states[8] = iNewCandidates;
            cout << "New candidates: " << iNewCandidates;

            memcpy(states, new_states, sizeof(states));

            /*iNewCandidates = reduce(execution::par, vPopulation.begin(), vPopulation.end(), 0, [](int carr, int num){return num==0 ? carr+1 : carr;});
            transform(vPopulation.begin(), vPopulation.end(), vPopulation.begin(), [](int num){return num==0 ? 6 : num-1;});
            vPopulation.insert(vPopulation.end(), iNewCandidates, 8);*/
            iCurrentSize = 0;
            for (size_t i = 0; i < 9; i++)
            {
                iCurrentSize += states[i];
            }

            cout << " Current size: " << iCurrentSize << endl;
        }

        cout << "After 256 days, there are " << vPopulation.size() << " lanternfishes." << endl;

    }
    else
    {
        return 1;
    }

    return 0;
}
