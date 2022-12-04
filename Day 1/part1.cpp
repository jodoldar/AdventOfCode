/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 1 - Part 1 of the Advent of Code 2022
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

short int siReadAndProcessInput(string sFileName, vector<vector<int>> &llCalList)
{
    ifstream fInputFile;
    string sLine;
    int iNumOfElem = 0;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        llCalList.clear();
        llCalList.push_back(vector<int>()); /* Create initial element as empty. */

        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
            {
                llCalList.push_back(vector<int>());
                iNumOfElem++;

                continue;
            }

            llCalList[iNumOfElem].push_back(atoi(sLine.c_str()));
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
    vector<vector<int>> llElfCalories;
    int iMaxCalories = 0;
    int iAuxSumOfCalories = 0;

    if (!siReadAndProcessInput("input.txt", llElfCalories))
    {
        for (auto &&elem : llElfCalories)
        {
            iAuxSumOfCalories = accumulate(elem.begin(), elem.end(), 0);
            if (iAuxSumOfCalories > iMaxCalories)
                iMaxCalories = iAuxSumOfCalories;
        }

        cout << "Maximum amount of calories is " << iMaxCalories << endl;

        return 0;
    }
    else
    {
        return 1;
    }
}
