/**
 * @file part1.cpp
 * @author Josep Dols (jodoldar@gmail.com)
 * @brief Day 9 - Part 1 of the Advent of Code 2021
 * @version 0.1
 * @date 2021-12-11
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

const string RED_COLOR = "\033[31m";
const string RESET_COLOR = "\033[0m";

short int siReadAndProcessInput(string sFileName, vector<vector<int>> &vGroundMap)
{
    ifstream fInputFile;
    string sLine;

    fInputFile.open(sFileName, ios::in);

    if (fInputFile.is_open())
    {
        while (getline(fInputFile, sLine))
        {
            if (sLine.empty())
                continue;

            vGroundMap.push_back(vector<int>());

            for (auto &&letter : sLine)
            {
                vGroundMap.back().push_back(letter - '0');
            }
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
    vector<vector<int>> vGroundMap;
    int iRiskLevel = 0;

    if (!siReadAndProcessInput("input.txt", vGroundMap))
    {
        int iMaxRow = vGroundMap.size()-1;
        int iMaxCol = vGroundMap[0].size()-1;


        /* Check corners */
        if ((vGroundMap[0][0] < vGroundMap[0][1]) && (vGroundMap[0][0] < vGroundMap[1][0]))
            iRiskLevel += (1+vGroundMap[0][0]);

        if ((vGroundMap[iMaxRow][0] < vGroundMap[iMaxRow][1]) && (vGroundMap[iMaxRow][0] < vGroundMap[iMaxRow-1][0]))
            iRiskLevel += (1+vGroundMap[iMaxRow][0]);

        if ((vGroundMap[0][iMaxCol] < vGroundMap[0][iMaxCol-1]) && (vGroundMap[0][iMaxCol] < vGroundMap[1][iMaxCol]))
            iRiskLevel += (1+vGroundMap[0][iMaxCol]);

        if ((vGroundMap[iMaxRow][iMaxCol] < vGroundMap[iMaxRow-1][iMaxCol]) && (vGroundMap[iMaxRow][iMaxCol] < vGroundMap[iMaxRow][iMaxCol-1]))
            iRiskLevel += (1+vGroundMap[iMaxRow][iMaxCol]);

        /* Check edges */
        for (size_t iCol = 1; iCol <= iMaxCol-1; iCol++)
            if ((vGroundMap[0][iCol] < vGroundMap[0][iCol-1]) && (vGroundMap[0][iCol] < vGroundMap[0][iCol+1]) && (vGroundMap[0][iCol] < vGroundMap[1][iCol]))
                iRiskLevel += (1+vGroundMap[0][iCol]);

        for (size_t iCol = 1; iCol <= iMaxCol-1; iCol++)
            if ((vGroundMap[iMaxRow][iCol] < vGroundMap[iMaxRow][iCol-1]) && (vGroundMap[iMaxRow][iCol] < vGroundMap[iMaxRow][iCol+1]) && (vGroundMap[iMaxRow][iCol] < vGroundMap[iMaxRow-1][iCol]))
                iRiskLevel += (1+vGroundMap[iMaxRow][iCol]);


        for (size_t iRow = 1; iRow <= iMaxRow-1; iRow++)
        {
            if ((vGroundMap[iRow][0] < vGroundMap[iRow-1][0]) && (vGroundMap[iRow][0] < vGroundMap[iRow+1][0]) && (vGroundMap[iRow][0] < vGroundMap[iRow][1]))
                iRiskLevel += (1+vGroundMap[iRow][0]);

            if ((vGroundMap[iRow][iMaxCol] < vGroundMap[iRow-1][iMaxCol]) && (vGroundMap[iRow][iMaxCol] < vGroundMap[iRow+1][iMaxCol]) && (vGroundMap[iRow][iMaxCol] < vGroundMap[iRow][iMaxCol-1]))
                iRiskLevel += (1+vGroundMap[iRow][iMaxCol]);
        }
        
        /* Check all */
        for (size_t iRow = 1; iRow <= iMaxRow-1; iRow++)
            for (size_t iCol = 1; iCol <= iMaxCol-1; iCol++)
                if ((vGroundMap[iRow][iCol] < vGroundMap[iRow-1][iCol]) && (vGroundMap[iRow][iCol] < vGroundMap[iRow+1][iCol]) && (vGroundMap[iRow][iCol] < vGroundMap[iRow][iCol-1]) && (vGroundMap[iRow][iCol] < vGroundMap[iRow][iCol+1]))
                   iRiskLevel += (1+vGroundMap[iRow][iCol]);

        cout << "Total risk is " << iRiskLevel << endl;
    }
    else
    {
        return 1;
    }
    return 0;
}
